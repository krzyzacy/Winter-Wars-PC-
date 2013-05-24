#include "Elf.h"

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

float standard_speed = 200;


float Max_Player_Health = 100;	
float Max_Snow_Amount = 100;		// most you can scoop/reload
float max_snowball_size = 50;		// most you can pack/charge	
float packing_rate = 50;			// Packing to snowball
float snow_depletion_rate = 25;	// Packing from pouch
float snow_absorbtion_rate = 100;  // Scooping

float Max_Stick_Input	= 32768;
float Building_Recharge_Time = 0.2;
float Respawn_Time = 6;

const Vector3f jump_vec(0,0,500);
float Stick_Accel = 1200;
int Elf::max_id = 0;

Elf::Elf(Team* team_, const std::string &gender_)	
	: Moveable(team_->get_spawn_point(), Vector3f(1,1,1)*35),
	gender(gender_),
	current_radius(0.0f),
	Snow_in_Pack(Max_Snow_Amount), 
	health(Max_Player_Health), 
	hit_timer(0.0f), throw_timer(0.0f), packing_timer(0.0f),
	ID(max_id++),
	stats(ID),
	myTeam(team_),
	backup(center),
	allowed_to_calculate_movement(true),
	Jumping(ON_GROUND), 
	Builder(REST), 
	Selection(HEALING_POOL), 
	dead_mode(false),
	animation_state(new Standing()), 

	player_boy_hit(new Zeni::Sound_Source(Zeni::get_Sounds()["boy_hit"])),
	player_girl_hit(new Zeni::Sound_Source(Zeni::get_Sounds()["girl_hit"])),
	player_dead(new Zeni::Sound_Source(Zeni::get_Sounds()["Dead"])),
	snowball_hit1(new Zeni::Sound_Source(Zeni::get_Sounds()["HitBySnow1"])), 
	snowball_hit2(new Zeni::Sound_Source(Zeni::get_Sounds()["HitBySnow2"])),
	sound_choice(0)	
{
	
	stats.add_stat("X pos", &center.x);
	stats.add_stat("Y pos", &center.y);


	Player_Movement_Message_Ticker.reset();
	Player_Movement_Message_Ticker.start();

}

Elf::~Elf(void)	
{
	//Delete sounds
	delete player_boy_hit;
	delete player_girl_hit;
	delete player_dead;
	delete snowball_hit1;
	delete snowball_hit2;
}

//Movement Functions
 void Elf::calculate_movement(const Vector2f input_vel)	{
	 
	//Animations
	if (velocity.x <= 0.5 && velocity.y <= 0.5 && is_on_ground())
		switch_state(STAND);
	else if ((velocity.x >= 0.5 || velocity.y >= 0.5) && is_on_ground())
		switch_state(WALK);
	else {}

	
}

 void Elf::push_away_from(Point3f &P, const float force)	{
	 Vector3f shove(center - P);
	 shove.z = 0;
	 shove *= force;
	 set_velocity(Vector3f(0,0, velocity.z));
	 accelerate(shove, Game_Model::get().get_time_step());
 }

 void Elf::manage_shooting_state(bool shoot_input)	{
	switch(Shoot)		{
	case CHILL:
		//Check for charge command, else do nothing
		if(shoot_input)
			Shoot = CHARGING;
		break;
	case CHARGING:
		charge_ball();
		if(!shoot_input)
			Shoot = FIRE;
		break;
	case FIRE:
		throw_ball();
		Shoot = CHILL;
		break;
	default:
		Shoot = CHILL;
		break;
	}
 }





 Animator* Elf::get_animator() const	{
	 return animation_state;
 }

 void Elf::throw_ball() {
	//This is overwritten by player. And Maybe should be by AI?
	//But I am hesitant to make it a pure virtual function and this an abstract class
	if(is_player_KO())
		return;
	
	if(current_radius <= 0)	{
		//if radius is 0, means out of snow, and therefore don't throw
		return;
	}

	Game_Model::get().play_snowballthrow();

	if (current_radius > max_snowball_size/2)
		stats.num_large_snowballs++;
	else
		stats.num_small_snowballs++;

	current_radius = 0;
	switch_state(THROW);
	stats.thrown++;

	throw_timer = 1.0f;
	packing_timer = 0.0f;
}

 // PACK!!!
void Elf::charge_ball()	{
	if(is_player_KO())
		return;
	
	//Not enough snow to make a ball
	if(Snow_in_Pack <= 0)	{
		Snow_in_Pack = 0;
		return;
	}
	
	//This represents when the player is "packing" snow into a ball
	const float time = Game_Model::get().get_time_step();

	
	//Too big
	if (current_radius >= max_snowball_size)	{
		current_radius = max_snowball_size;
	}
	
	//%%%%% HERERERERE

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
void Elf::scoop_snow()	
{
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
	{
		Snow_in_Pack += snow_absorbtion_rate * time;
		stats.amount_scooped += snow_absorbtion_rate * time;
	}

}

void Elf::stop_scooping()	{ }//	switch_state(STAND);}


void Elf::jump()	{
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

void Elf::jet_pack_mode(bool state)	{
	if(state) //Super easy to add as a power up
		Jumping = JET_PACK;
	else if(Jumping == JET_PACK)
		Jumping = FALLING_WITH_STYLE;
}

bool Elf::create_building(Structure_Type Building)	{
	//Returns true if building was created, false if unable
		
	Tile *t = Game_Model::get().get_World()->get_tile(center);
	
	if(t->has_building() && t->get_building()->get_type() == Building)
		return false;
	
	
	//true if the player is trying to build on the tree
	if(t->has_building() && t->get_building()->get_type() == TREE)
		Building = TREE;

	if(myTeam->allowed_to_build_on_Tile(t) && myTeam->can_afford_building(Building))	{
		Build_Event(create_structure(Building, t, myTeam));
		return true;
	}

		//Checks if the tile can be built upon
	return false;
}

void Elf::Make_Building(bool Go)	{
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

void Elf::raise_tile()	{
	Game_Model::get().get_World()->raise_tile(center);
}
void Elf::stop_raising()	{
	stats.tiles_raised++;
}

void Elf::lower_tile()	{
	Game_Model::get().get_World()->lower_tile(center);
}
void Elf::stop_lowering()	{
	stats.tiles_lowered++;
}

void Elf::player_death()	{

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

	Deathclock.start();
	stats.deaths++;
	dead_mode = true;
}

void Elf::respawn()	{
	Deathclock.stop();
	Deathclock.reset();
	dead_mode = false;
	health = Max_Player_Health;
	Snow_in_Pack = Max_Snow_Amount;

	current_radius = 0;
	packing_timer = 0.0f;

	center = myTeam->get_spawn_point();
	switch_state(RESPAWN);
}

void Elf::healing_waters(float health_up)	{
	health += health_up;
	if(health > Max_Player_Health)
		health = Max_Player_Health;
}

void Elf::get_damaged(float damage)
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
	

}

int Elf::get_Team_Blocks() const		
{return myTeam->get_Resources(); }

int Elf::get_Team_Resource_Rate() const	
{return myTeam->get_Resource_Rate(); }

int Elf::get_Team_Index() const
{return myTeam->get_Team_Index(); }

void Elf::create_body()
{
	body = Zeni::Collision::Capsule(center + Vector3f(0, 0 , size.z*0.25)
		, center - Vector3f(0, 0, size.z*0.25), size.z*0.25);
}

void Elf::play_sound()
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

void Elf::switch_state(PlayerEvent_e pevent)
{
	PlayerAnimator *next = animation_state->get_next(pevent);
	if (next)
	{
		delete animation_state;
		animation_state = next;
	}
}

const model_key_t Elf::get_model_name() const
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

void Elf::update(const float &time)	{
	backup = center;
	
	if(Deathclock.seconds() > Respawn_Time)
		respawn();

	if(is_player_KO())
		return;

	Moveable::update(time);

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
	

}

Elf::Player_Stats::Player_Stats(int id) :
	Stats(string("Elf") + itoa(id).std_str()),
			kills(0), friendly_kills(0), deaths(0), thrown(0),
			hit(0), tips(0), biggest_snowball(0), 
			num_large_snowballs(0),
			num_small_snowballs(0), amount_scooped(0),
			tiles_raised(0), tiles_lowered(0), friendly_hit(0),
			snow_used(0), built(0), destroyed(0),
			damage_taken(0), damage_dealt(0)
{
	add_stat("Kills", &kills);
	add_stat("Deaths", &deaths); 
	add_stat("Snowballs Thrown", &thrown);
	add_stat("Hit", &hit);
	add_stat("Friendly Fire", &friendly_hit);
	add_stat("Structures Built", &built); 
	add_stat("Structures Destroyed", &destroyed);
	add_stat("Damage Dealt", &damage_dealt); 
	add_stat("Damage Taken", &damage_taken);
	add_stat("Snow Used", &snow_used); 
	add_stat("Biggest Snowball", &biggest_snowball);
	add_stat("# Large", &num_large_snowballs); 
	add_stat("# Small", &num_small_snowballs);
	add_stat("Amount Scooped", &amount_scooped); 
	add_stat("Tiles Raised", &tiles_raised);
	add_stat("Tiles Lowered", &tiles_lowered);		
	add_stat("Tips", &tips);
			
}


