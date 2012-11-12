#ifndef CRATE_H
#define CRATE_H

#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>

#include "Game_Object.h"

class Collision_Table;

  class Crate : public Game_Object {
  public:
    Crate(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
          const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
          const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Crate(const Crate &rhs);
    Crate & operator=(const Crate &rhs);
    ~Crate();

    void collide();
	
	Zeni::Model *get_m() const {return m_model;}
	
  virtual int get_ID() const
		{return crate_ID_c;}

  private:

    // Level 1
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;

    Zeni::Sound_Source * m_source;

    // Level 4
    // A stationary Crate has no controls

  Zeni::Collision::Parallelepiped m_body;

	const static int crate_ID_c;
  friend Collision_Table;

  void create_body();
  };

#endif
