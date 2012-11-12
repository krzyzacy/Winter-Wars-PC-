#include <zenilib.h>

#include "Crate_State.h"
#include "Collision_Table.h"

Collision_Table ColT;

using namespace Zeni;
using namespace Zeni::Collision;

bool m_moved = true;

  Crate_State::Crate_State()
    : m_crate(Point3f(12.0f, 12.0f, 0.0f),
              Vector3f(30.0f, 30.0f, 30.0f)),
    m_player(Camera(Point3f(0.0f, 0.0f, 50.0f),
             Quaternion(),
             1.0f, 10000.0f))
    , m_model("models/player1.3DS")
  {
    set_pausable(true);

    get_Window().mouse_grab(true);
    get_Window().mouse_hide(true);


	 // Set up the Camera
    m_camera.near_clip = 100.0f;
    Projector3D projector(m_camera);
    const float camera_radius = projector.unproject(Vector3f()).magnitude();
    m_camera.position = Point3f(0.0f, camera_radius, 0.0f);
    m_camera.look_at(Point3f());
    m_camera.near_clip = 1.0f;
    m_camera.far_clip = 2.0f * camera_radius;

    // Misc.
    get_Video().set_clear_Color(Color(1,0,0,0));


  }

  Crate_State::~Crate_State() {
    get_Window().mouse_grab(false);
    get_Window().mouse_hide(false);
  }

  void Crate_State::on_key(const SDL_KeyboardEvent &event) {
    switch(event.keysym.sym) {
      case SDLK_w:
        m_player.m_controls.forward = event.type == SDL_KEYDOWN;
        break;

      case SDLK_a:
        m_player.m_controls.left = event.type == SDL_KEYDOWN;
        break;

      case SDLK_s:
        m_player.m_controls.back = event.type == SDL_KEYDOWN;
        break;

      case SDLK_d:
        m_player.m_controls.right = event.type == SDL_KEYDOWN;
        break;

      case SDLK_SPACE:
        if(event.type == SDL_KEYDOWN) {
          m_player.jump();
          m_moved = true;
        }
        break;

      default:
        Gamestate_Base::on_key(event);
        break;
    }
  }

  void Crate_State::on_mouse_motion(const SDL_MouseMotionEvent &event) {
    m_player.adjust_pitch(event.yrel / 500.0f);
    m_player.turn_left_xy(-event.xrel / 500.0f);
  }

  void Crate_State::perform_logic() {
    const Time_HQ current_time = get_Timer_HQ().get_time();
    float processing_time = float(current_time.get_seconds_since(time_passed));
    time_passed = current_time;

    /** Keep delays under control (if the program hangs for some time, we don't want to lose responsiveness) **/
    if(processing_time > 0.1f)
      processing_time = 0.1f;

	m_player.set_velo();
	
	const Vector3f x_vel = m_player.get_velocity().get_i();
    const Vector3f y_vel = m_player.get_velocity().get_j();
    Vector3f z_vel = m_player.get_velocity().get_k();
    /** Physics processing loop**/
    for(float time_step = 0.05f;
			processing_time > 0.0f;
			processing_time -= time_step)
	{
      if(time_step > processing_time)
			time_step = processing_time;

	        /** Gravity has its effect **/
      z_vel -= Vector3f(0.0f, 0.0f, 50.0f * time_step);

      /** Try to move on each axis **/
      partial_step(time_step, x_vel);
      partial_step(time_step, y_vel);
      partial_step(time_step, z_vel);

      /** Keep player above ground; Bookkeeping for jumping controls **/
      const Point3f &position = m_player.get_camera().position;
      if(position.z < 50.0f) {
        m_player.set_position(Point3f(position.x, position.y, 50.0f));
        m_player.set_on_ground(true);
      }

	}

	
    m_light.position = Point3f(
      100.0f,
      100.0f ,
      50.0f);


  }
  
void Crate_State::partial_step(const float &time_step, const Vector3f &velocity) {
    m_player.set_velocity(velocity);
	
    m_player.backup_position = m_player.get_camera().position;
    m_player.update(time_step);

    /** If collision with the crate has occurred, roll things back **/
	ColT.handle_collision(m_crate.get_ID(),m_player.get_ID(), &m_crate, &m_player);
     
}
  
  void Crate_State::render() {
    Video &vr = get_Video();

    vr.set_3d(m_player.get_camera());

    vr.set_lighting(true);
    vr.set_ambient_lighting(Color(1.0f, 0.50f, 0.50f, .5f));
    vr.set_Light(0, m_light);

    m_player.render();

    m_crate.render();

  }

