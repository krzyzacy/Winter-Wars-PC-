#include <zenilib.h>

#include "Crate.h"

#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;

const int Crate::crate_ID_c = 2;

  Crate::Crate(const Point3f &corner_,
        const Vector3f &scale_,
        const Quaternion &rotation_)
    : Game_Object(corner_, scale_, rotation_),
	m_source(new Sound_Source(get_Sounds()["collide"]))    
  {
    if(!m_instance_count)
      m_model = new Model("models/crate.3ds");
    ++m_instance_count;


    create_body();

  }

  Crate::~Crate() {
    delete m_source;

    if(!--m_instance_count) {
      delete m_model;
      m_model = 0lu;
    }
  }

  void Crate::collide() {
    if(!m_source->is_playing())
      m_source->play();
  }

  Model * Crate::m_model = 0;
  unsigned long Crate::m_instance_count = 0lu;

void Crate::create_body() {
	m_body = Parallelepiped(m_corner,
                        m_rotation * m_scale.get_i(),
                        m_rotation * m_scale.get_j(),
                        m_rotation * m_scale.get_k());

}