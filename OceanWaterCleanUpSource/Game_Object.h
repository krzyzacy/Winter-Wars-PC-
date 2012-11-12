#pragma once

#include <zenilib.h>

class Collision_Table;


class Game_Object {
public:
  Game_Object(const Zeni::Point3f &position_,
              const Zeni::Vector3f &size_,
			  int mass_,
              const Zeni::Quaternion &theta_ 
				= Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f),
			  const Zeni::Vector3f &velo_ = Zeni::Vector3f())
  : m_pos(position_),
    m_size(size_),
    m_rotation(theta_),
    m_velo(velo_),
	mass(mass_)
	, radius_factor(1)
  {
    create_body();
  }
 
  // If you might delete base class pointers, you need a virtual destructor.
  virtual ~Game_Object() {}
  virtual void update();
  virtual void render() const; // pure virtual function call
  
  void accelerate(const Zeni::Vector3f &acc);
	
  const Zeni::Point3f & get_position() const {return m_pos;}
  const Zeni::Vector3f & get_size() const {return m_size;}
  const Zeni::Quaternion & get_theta() const {return m_rotation;}
 
  const float get_radius() const 
	{return 0.5f * m_size.x * radius_factor;}
	
  virtual int get_ID() const
		{return object_ID_c;}
  
  virtual Zeni::Model *get_m() const = 0;
    
  const Zeni::Collision::Sphere & get_body() const {return m_body;}

protected:
  void render(const Zeni::String &texture, const Zeni::Color &filter = Zeni::Color()) const;
  
	virtual int get_parent_ID() const = 0;
	
	float get_speed() {return m_velo.magnitude2();}
		
	float radius_factor;

	const Zeni::Point3f &get_pos() const 
		{return m_pos;}

	Zeni::Vector3f m_velo;

	void set_pos(Zeni::Point3f pos_)
		{m_pos = pos_;}

	float get_bottom() {
		return center().z - get_radius();
	}

	Zeni::Point3f m_pos; // Center!
private:
    Zeni::Vector3f m_size;
    Zeni::Quaternion m_rotation;
  
  int mass;

  void add_gravity();

	Zeni::Point3f center() const {
		return m_pos;
	}
	
	Zeni::Point3f corner() const {
		return m_pos + m_size/2;
	}

	
    void create_body();
    Zeni::Collision::Sphere m_body;

  const static int object_ID_c;

  friend Collision_Table;
};
