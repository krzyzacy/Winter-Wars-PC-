#include "Player.h"

#include "Game_Model.h"
#include "Snowball.h"
#include "Team.h"
#include "World.h"
#include "Tile.h"
#include "Object_factory.h"
#include "PlayerAnimator.h"
#include "PlayerAnimators.h"
#include "Event.h"

#include <zenilib.h>

using namespace std;
using namespace Zeni;

const int Player::player_ID_c = 1;
const float standard_speed = 200;
const float turn_speed = 40;
const float up_look_speed = 20;

const float Max_Snow_Amount = 100;		// most you can scoop/reload
const float Max_Player_Health = 100;	
const float max_snowball_size = 50;		// most you can pack/charge	
const float packing_rate = 50;			// Packing to snowball
const float snow_depletion_rate = 25;	// Packing from pack
const float snow_absorbtion_rate = 100;  // Scooping

const float Max_Stick_Input	= 32768;
const float Building_Recharge_Time = 1;
const float Respawn_Time = 6;


const Vector3f jump_vec(0,0,500);
const float  Stick_Accel = 1200;

const int num_tips = 13;
String tips[num_tips] = {
	"Show the next tip by pressing (Y).",
	"Point at a tile in front of you and build with (X).",
	"You can only build structures next to your existing structures",
	"Building on soft snow will generate the most resource.",
	"Need health? Go to a pool - but only your pool!",
	"Destroy structures with snowballs.",
	"Forts are difficult to destroy.",
	"Ice tiles make you slip and don't give you resources when owned.",
	"Snowmen can protect your territory.",
	"Factories changes adjacent tiles to soft snow tiles.",
	"Structures become inactive if they aren't connected to your base.",
	"After a structure is inactive, you need to reconnect it, or it will be destroyed!",
	"Winter Wars >>> Halo" //funny
};


Player::Player(const Zeni::Point3f &center_) 
	: Moveable(center_ , Vector3f(1,1,1)*35), cur_tip(0),
	m_camera(center_, Quaternion(), 5.0f, 3000.0f),
	current_radius(0.0f), Snow_in_Pack(Max_Snow_Amount), health(Max_Player_Health), 
	gender(""),
	myTeam(0), backup(center_), Jumping(ON_GROUND), Builder(REST), Selection(HEALING_POOL), stick_theta(0.0f),
	mini_open(false), build_open(false),dead_mode(false),hit_timer(0.0f),throw_timer(0.0f),packing_timer(0.0f),
	animation_state(new Standing()), player_boy_hit(new Zeni::Sound_Source(Zeni::get_Sounds()["boy_hit"])),
	player_girl_hit(new Zeni::Sound_Source(Zeni::get_Sounds()["girl_hit"])), player_dead(new Zeni::Sound_Source(Zeni::get_Sounds()["Dead"])),
	snowball_hit1(new Zeni::Sound_Source(Zeni::get_Sounds()["HitBySnow1"])), snowball_hit2(new Zeni::Sound_Source(Zeni::get_Sounds()["HitBySnow2"])),
	sound_choice(0), allowed_to_calculate_movement(true)
{
	//field of view in y
	m_camera.fov_rad = Zeni::Global::pi / 3.0f;
	rotation = m_camera.orientation + Quaternion(Global::pi_over_two + Global::pi_over_two/2, 0,0);

	//player_sound_test = new Zeni::Sound_Source(Zeni::get_Sounds()["meow"]);
	//rotation = m_camera.orientation + Quaternion(Global::pi_over_two, 0, 0);
	//rotation += Quaternion(Global::pi_over_two, 0,0);

	Player_Movement_Message_Ticker.reset();
	Player_Movement_Message_Ticker.start();
}


Player::~Player(void)
{
	//Delete sounds
	delete player_boy_hit;
	delete player_girl_hit;
	delete player_dead;
	delete snowball_hit1;
	delete snowball_hit2;
}

void Player::adjust_pitch(float phi) {
    const Quaternion backup = m_camera.orientation;
    const Vector3f backup_up = m_camera.get_up();

    m_camera.adjust_pitch(phi * up_look_speed * Game_Model::get().get_time_step());

    if(m_camera.get_up().k < 0.0f && backup_up.k >= 0.0f)
      m_camera.orientation = backup;
}

void Player::turn_left(float theta) {	
	//Vector3f Old = m_camera.get_forward().get_ij();
	float angle = theta * turn_speed * Game_Model::get().get_time_step();

	m_camera.turn_left_xy(angle);
	//rotation *= m_camera.orientation.Vector3f_to_Vector3f(m_camera.get_forward().get_ij(), Old);
	rotation *= rotation.Axis_Angle(Vector3f(0,0,10) , angle);
}

void Player::update(const float &time)	{
	backup = center;
	
	if(Deathklok.seconds() > Respawn_Time)
		respawn();

	if(is_player_KO())
		return;

	Moveable::update(time);
	m_camera.position = center;

	if(hit_timer >= 1.0f){
		hit_timer += time;
		if(hit_timer > 2.0f)
			hit_timer = 0.0f;
	}

	if(throw_timer >= 1.0f){
		throw_timer += time;
		if(throw_timer > 2.0f)
			throw_timer = 0.0f;
	}

	if(packing_timer >= 1.0f && packing_timer < 2.1f){
		packing_timer += time;
	}
	

	if(Player_Movement_Message_Ticker.seconds() > 0.5)
	{
		Player_Movement_Event(this);
		
		Player_Movement_Message_Ticker.reset();
		Player_Movement_Message_Ticker.start();
	}

}

void Player::player_death()	{

	if(!player_dead->is_playing())
	{
		player_dead->set_gain(0.2);
		player_dead->play();
	}

	if(gender == "girl")
	{
		player_girl_hit->set_gain(0.8);
		player_boy_hit->set_pitch(2);
		player_girl_hit->play();
	}

	if(gender == "boy")
	{
		player_boy_hit->set_gain(0.8);
		player_boy_hit->set_pitch(3.5);
		player_boy_hit->play();
	}

	Deathklok.start();
	stats.deaths++;
	dead_mode = true;
}
void Player::respawn()	{
	Deathklok.stop();
	Deathklok.reset();
	dead_mode = false;
	health = Max_Player_Health;
	Snow_in_Pack = Max_Snow_Amount;

	current_radius = 0;
	packing_timer = 0.0f;

	center = myTeam->get_spawn_point();
	switch_state(RESPAWN);
}


void Player::off_map()
{
	center.x = backup.x;
	center.y = backup.y;
}

void Player::hit_tile()
{
	//Use math, get the family, determine which one you are closest too., 
	//Make a vector from that and push
	center.x = backup.x;
	center.y = backup.y;

	Vector3f push_dir;
	Tile* OnT = Game_Model::get().get_World()->get_tile(center);
	list<Tile*> fam = Game_Model::get().get_World()->Get_Family(OnT);
	Tile* Closest = fam.front();
	Vector3f close_dist = Closest->get_structure_base() - OnT->get_structure_base();
	for(list<Tile*>::iterator it = fam.begin(); it != fam.end(); ++it)	{
		Vector3f dist((*it)->get_structure_base() - OnT->get_structure_base());
		if(dist.magnitude() < close_dist.magnitude())	{
			close_dist = dist;
			Closest = (*it);
		}
	}
	push_away_from(Closest->get_structure_base(), -7.5);

	//center.x = backup.x;
	//center.y = backup.y;
	
}

void Player::on_ground()
{
	if(velocity.z < 0)
		velocity.z = 0;

	// set them on the ground
	center.z = Game_Model::get().get_World()->get_ground_height(center) + size.z/2 + 10.0f;
}

void Player::get_damaged(float damage)
{
	health -= damage;
	stats.damage_taken += damage;

	if (health < 0)	{
		health = 0;
		switch_state(DIE);
		player_death();
	}
	else{
		hit_timer = 1.0f;

		if(gender == "girl" && !player_girl_hit->is_playing())
			{
			player_girl_hit->set_gain(0.8);
			player_boy_hit->set_pitch(2);
			player_girl_hit->play();
			}

		if(gender == "boy" && !player_boy_hit->is_playing())
			{
			player_boy_hit->set_gain(0.8);
			player_boy_hit->set_pitch(3.5);
			player_boy_hit->play();
			}
		switch_state(FLINCH);
	}
	
	if(health > 0)
		ShakeTime.start();
}

void Player::throw_ball() {
	if(is_player_KO())
		return;
	
	if(current_radius <= 0)	{
		//if radius is 0, means out of snow, and therefore don't throw
		return;
	}

	Game_Model::get().play_snowballthrow();

	Snowball *sb = new Snowball(this, center+m_camera.get_forward(), 
									Vector3f(current_radius, current_radius,current_radius));
	sb->get_thrown(m_camera.get_forward());
	
	if (current_radius > stats.biggest_snowball)
		stats.biggest_snowball = current_radius;

	if (current_radius > max_snowball_size/2)
		stats.num_large_snowballs++;
	else
		stats.num_small_snowballs--;

	Game_Model::get().add_moveable(sb);

	Throw_Snowball_Event(this, center+m_camera.get_forward()
		, m_camera.get_forward(), current_radius);

	current_radius = 0;
	switch_state(THROW);
	stats.thrown++;

	throw_timer = 1.0f;
	packing_timer = 0.0f;

}

// PACK!!!
void Player::charge_ball()	{
	if(is_player_KO())
		return;
	//This represents when the player is "packing" snow into a ball
	const float time = Game_Model::get().get_time_step();

	// not enough snow
	if(Snow_in_Pack <= 0) 	{
		add_message("Out of Ammo! Find SOFT SNOW and refill (B).");
		Snow_in_Pack = 0;
	}
	
	//Too big
	else if (current_radius >= max_snowball_size)	{
		current_radius = max_snowball_size;
	}
	
	// lets grow it
	else	{
		if(packing_timer < 0.5f)
			packing_timer = 1.0f;
		current_radius += packing_rate * time;
		stats.snow_used += packing_rate * time;
			
		Snow_in_Pack -= snow_depletion_rate * time;
		switch_state(PACK);
	}
}

// SCOOP!!!!
void Player::pack_snow()	{
	if(is_player_KO())
		return;



	//This will change, but exists for now as a simple test function
	if (!is_on_ground())
		return;

	if(!Game_Model::get().get_World()->allowed_to_scoop(center))
		return;

	switch_state(SCOOP);

	const float time = Game_Model::get().get_time_step();
	if(Snow_in_Pack >= Max_Snow_Amount)
		Snow_in_Pack = Max_Snow_Amount;
	else
		Snow_in_Pack += snow_absorbtion_rate * time;

}

void Player::stop_scooping()	{
//	switch_state(STAND);
}

 void Player::calculate_movement(const Vector2f input_vel)	{
	 if(is_player_KO())
		return;

	 if(!allowed_to_calculate_movement)
		 return;
	//input_vel is joystick values, from 0 to 32768
	//if(mini_open)	{	//Mini-map is open stop moving
	//	velocity = Vector3f(0,0, velocity.z);
	//	return;
	//}

	//Set up, get Camera Vectors and create variables
	Vector3f POV_face = m_camera.get_forward().get_ij();
	POV_face.normalize();
	Vector3f POV_left = m_camera.get_left().get_ij();
	POV_left.normalize();
		//The new velocity
	Vector3f New_vel = velocity;
		//The maximum speed allowed, based on how far joystick is pushed
	//if(abs(input_vel.y) < 1000) POV_face = Vector3f();
	//if(abs(input_vel.x) < 1000) POV_left = Vector3f();


	//multiplication and it's effects if negative number??
	//Vector2f input_vel2 = input_vel;
	//input_vel2.normalize();
	//Vector3f Input_Target_Vel = POV_face * input_vel2.y + POV_left * input_vel2.x;
	Vector3f Input_Target_Vel = ( POV_face * (input_vel.y/Max_Stick_Input)) + (POV_left * (input_vel.x/Max_Stick_Input));
	
	Input_Target_Vel *= standard_speed;
	Input_Target_Vel.z = 0;

	//Force Z movement to be independent
	float zvel = velocity.z;
	New_vel.z = 0;
	

	//friction coefficent
	float friction = Game_Model::get().get_World()->get_friction_coeff(center);
	//float friction = 0.2;
	//0 to 1, will be determined by tile type eventually
	//(0 represents frictionless environment), (1 immovable environment)
	
	//	New_vel = (New_vel + Vector3f(Input_Target_Vel.x, Input_Target_Vel.y,0));
	
	//New_vel = Input_Target_Vel;
	//New_vel = (1 - friction) * New_vel;


	//Vector3f input_dir = Input_Target_Vel;
	//input_dir.normalize();
	//if(Input_Target_Vel.magnitude() > 0.01)
	//	New_vel += input_dir * Stick_Accel * friction * Game_Model::get().get_time_step();

	//
	////input_dir.normalize();
	////if(Input_Target_Vel.magnitude() < 0.05)	{
	////	input_dir = Vector3f(0,0,0);
	////}
	////if(input_dir.magnitude() > 0.1)
	////	New_vel += input_dir * Stick_Accel * friction * Game_Model::get().get_time_step();
	//
	////Update Variables
	////velocity = New_vel;
	//velocity = New_vel;
	//velocity.z = zvel;

	Vector3f dir(Input_Target_Vel - New_vel);		//Determine vector difference of current v, and player desired v
	Vector3f Input_Accel_Dir(dir.normalize());	//The acceleration vector, based on above
	
	if(Input_Target_Vel.magnitude() < 0.05)	{
		Input_Accel_Dir = Vector3f();		//If Player isn't pushing on stick, don't change velocity at all.
		if(friction == Ice_friction) 
			New_vel *= (1 - friction/5);			//And do a more powerful effect of friction
		else
			New_vel *= (1 - friction);	
	}
											
	//How much the player can control the new direction is also effected by friction
	Input_Accel_Dir *= Stick_Accel * friction;
	New_vel *= (1 - friction/15);
	New_vel += Input_Accel_Dir * Game_Model::get().get_time_step();

	//
	////If the speed is close to player desired, then just set it to player desired speed
	//if(abs(New_vel.magnitude() - Input_Vel_Max.magnitude()) < 1)
	//	New_vel = Input_Vel_Max;

	velocity = New_vel;
	velocity.z = zvel;

	//Animations
	if (velocity.x <= 0.5 && velocity.y <= 0.5 && is_on_ground())
		switch_state(STAND);
	else if ((velocity.x >= 0.5 || velocity.y >= 0.5) && is_on_ground())
		switch_state(WALK);
	else {}

	
}

 void Player::push_away_from(Point3f &P, const float force)	{
	 Vector3f shove(center - P);
	 shove.z = 0;
	 shove *= force;
	 set_velocity(Vector3f(0,0, velocity.z));
	 accelerate(shove, Game_Model::get().get_time_step());
 }
 
void Player::jump()	{
	if(is_player_KO())
		return;
	switch(Jumping)	{
	case ON_GROUND:
		switch_state(JUMP);
		AirTime.start();
		accelerate(jump_vec, Game_Model::get().get_time_step());
		Jumping = BOOST;
		break;
	case BOOST:
		{
		switch_state(JUMP);
		if(AirTime.seconds() <= 0.4)	
			accelerate(jump_vec, Game_Model::get().get_time_step());
		else	{
			Jumping = FALLING_WITH_STYLE;
			AirTime.stop();
			AirTime.reset();
		}
		break;
		}
	case FALLING_WITH_STYLE:
		{
		if(is_on_ground())
			Jumping = ON_GROUND;
		break;
		}
	case JET_PACK:
		accelerate(jump_vec, Game_Model::get().get_time_step());
		break;
	default:
		if(is_on_ground())
			Jumping = ON_GROUND;
		else
			Jumping = FALLING_WITH_STYLE;
		break;
	}
	
}

void Player::handle_struct_type_change(bool left, bool right)	{
	if(left && right)
		return;
	if(!left && !right)
		return;

	switch(Selection)	{
	case SNOWMAN:
		Selection = FORT;
		if(left) Selection = HEALING_POOL;
		break;
	case FORT:
		Selection = SNOW_FACTORY;
		if(left) Selection = SNOWMAN;
		break;
	case SNOW_FACTORY:
		Selection = HEALING_POOL;
		if(left) Selection = FORT;
		break;
	case HEALING_POOL:
		Selection = SNOWMAN;
		if(left) Selection = SNOW_FACTORY;
		break;
	default:
		Selection = FORT;
		break;
	}


}

void Player::Make_Building(bool Go)	{
	if(is_player_KO())	{
		Builder = REST;
		return;
	}
	
	switch(Builder)	{
	case REST:
		//Oay to build fire away
		if(!Go)
			return;

		if(create_building(Selection))	{
			stats.built++;
			Builder = RECHARGE_BUILD;
			BuildTime.start();
		}
		else
			Builder = REST;
		break;
	case RECHARGE_BUILD:
		if(BuildTime.seconds() >= Building_Recharge_Time)	{
			BuildTime.stop();
			BuildTime.reset();
			Builder = REST;
		}
		break;
	default:
		Builder = REST;
		break;
	}
}

void Player::determine_active_view(bool build, bool mini)	{
	mini_open = mini;
	//build_open = build && !mini;
	build_open = false;
}

Structure_Type Player::select_type(const Vector2f &stick)	{
	if(stick.magnitude() == 0	||
		(stick.x < 0.1 && stick.x > -0.1 && stick.y < 0.1 && stick.y > -0.1))
		return NOTHING;

	float mytheta = atan2(stick.y, stick.x);
	if(mytheta < 0)
		mytheta += 2*Global::pi;

	stick_theta = mytheta;
		//changes the stick input into an angle ,
	//the we define the type by region of angle

	//Joystick points right
	if(	stick_theta > Global::three_pi_over_two + Global::pi/4 ||
			stick_theta < Global::pi/4)
			return SNOWMAN;
	//Up
	if(stick_theta < Global::pi - Global::pi/4 &&
		stick_theta > Global::pi/4)
		return FORT;

	//Left
	if(stick_theta < Global::pi + Global::pi/4 &&
		stick_theta > Global::pi_over_two + Global::pi/4)
		return SNOW_FACTORY;

	//Down
	if(stick_theta < Global::three_pi_over_two + Global::pi/4 && 
		stick_theta > Global::three_pi_over_two - Global::pi/4)
		return HEALING_POOL;
}

bool Player::create_building(Structure_Type Building)	{
	//Returns true if building was created, false if unable
		
	Tile *t = Game_Model::get().get_World()->player_is_looking_at(center, m_camera.get_forward());
//	Tile *t = Game_Model::get().get_World()->get_tile(center);

	try {

		//Checks if the tile can be built upon
		if(!myTeam->tile_is_ready(t, Building))
			return false;
		
		myTeam->stats.structures[Building]++;
		Build_Event(create_structure(Building, t, myTeam));

		return true;


	}
	catch (Error &E)
	{
		add_message(E.msg);
		return false;
	}
}

void Player::jet_pack_mode(bool state)	{
	if(state) //Super easy to add as a power up
		Jumping = JET_PACK;
	else if(Jumping == JET_PACK)
		Jumping = FALLING_WITH_STYLE;
}

void Player::raise_tile()	{
	//Add restrictions and shit to this later
	//wnership etc.
	Game_Model::get().get_World()->raise_tile(center);
}

void Player::lower_tile()	{
	Game_Model::get().get_World()->lower_tile(center);
}

void Player::create_body()
{
	body = Zeni::Collision::Capsule(center + Vector3f(0, 0 , size.z*0.25)
		, center - Vector3f(0, 0, size.z*0.25), size.z*0.25);
}

int Player::get_Team_Blocks() const	{
	return myTeam->get_Resources();
}

bool Player::vibrate_feedback()	{

	if(ShakeTime.seconds() > 0.4)	{
		ShakeTime.stop();
		ShakeTime.reset();
	}
	if(ShakeTime.seconds() > 0)
		return true;

	return false;
}


const model_key_t Player::get_model_name() const
{
	string Teamname;
	switch(myTeam->get_Team_Index())	{
	case GREEN:
		Teamname = "green";
		break;
	case RED:
		Teamname = "red";
		break;
	case BLUE:
		Teamname = "blue";
		break;
	case ORANGE:
		Teamname = "orange";
		break;
	default:
		Teamname = "blue";
		break;
	}

	//return animation_state->get_model_name();
	return Teamname + gender + animation_state->get_model_name();
}

Animator *Player::get_animator() const
{
	return animation_state;
}

void Player::switch_state(PlayerEvent_e pevent)
{
	PlayerAnimator *next = animation_state->get_next(pevent);
	if (next)
	{
		delete animation_state;
		animation_state = next;
	}
}

void Player::healing_waters(float health_up)	{
	health += health_up;
	if(health > Max_Player_Health)
		health = Max_Player_Health;
}

int Player::get_Team_Index() const	{
	return myTeam->get_Team_Index();
}

void Player::add_message(const Zeni::String &msg, int priority, float seconds)
{
	if (message.is_over() || priority >= message.priority)
	message = Message(msg, priority, seconds);
}

bool Player::has_message() const
{
	return !message.is_over();
}

Zeni::String Player::get_message() const
{
	return message.msg;
}

void Player::next_tip()
{	
	add_message(tips[cur_tip++%num_tips], 50);
}

void Player::play_sound()
{
	sound_choice++;
	sound_choice = sound_choice%2;
	if (sound_choice == 1)
		{
		snowball_hit1->set_gain(1.5);
		snowball_hit1->set_pitch(1.5);
		snowball_hit1->play();
		}
	else
		{
		snowball_hit2->set_gain(1);
		snowball_hit2->set_pitch(3);
		snowball_hit2->play();
		}
}