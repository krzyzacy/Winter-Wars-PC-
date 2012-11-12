#include "Game_Object.h"
#include <zenilib.h>

#include "Utility.h"
#include "Game_Model.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;


const int Game_Object::object_ID_c = 0;
const float friction_c = 1.0f/5.0f; 
const float gravity_c = -.005f;

void Game_Object::render(const String &texture, const Color &filter) const {

	/*
    // Use a helper defined in Zeni/EZ2D.h
    render_image(
      texture, // which texture to use
      m_pos, // upper-left corner
      m_pos + m_size, // lower-right corner
      m_theta, // rotation in radians
      1.0f, // scaling factor
      m_pos + 0.5f *m_size, // point to rotate & scale about
      false, // whether or not to horizontally flip the texture
      filter); // what Color to "paint" the texture

	  */
  }

void Game_Object::render() const
{
	const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();

    get_m()->set_translate(center());
    get_m()->set_scale(m_size);
    get_m()->set_rotate(rotation.second, rotation.first);

    get_m()->render();
}

void Game_Object::accelerate(const Vector3f &acc)
{
	m_velo += acc * Game_Model::get().time_step() * 120;
}

void Game_Object::update()
{
	m_pos += m_velo * Game_Model::get().time_step() * 120;

	if (get_bottom() > 2000)
		Game_Model::get().add_to_delete(this);

    create_body();

	add_gravity();
}

 void Game_Object::add_gravity()
 {
	accelerate(gravity_c * Vector3f(0,0,-1));
 }

 void Game_Object::create_body() 
 {
    m_body = Sphere(center(), get_radius());
 }
