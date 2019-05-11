/*
  PhysicalObject is base class for
  Object class.
  This is physical part of Object,
  that is used to check collisions with
  other objects.
*/

#ifndef PhysicalObject_H
#define PhysicalObject_H

#include<SFML/System.hpp>
#include<iostream>



using namespace std;
using namespace sf;

struct PhysicalSettings
{
    unsigned int width;
    unsigned int height;
    Vector2f main_vertex;
    Vector2f speed;
	Vector2f jumping_speed;

    void operator=(PhysicalSettings settings)
    {
        width = settings.width;
        height = settings.height;
        main_vertex = settings.main_vertex;
        speed = settings.speed;
		jumping_speed = settings.jumping_speed;
    }
};

class PhysicalObject
{
private:
    bool collided;
protected:
    int width, height;
    Vector2f main_vertex; // hight left x and y
    Vector2f speed, jumping_speed;
    bool active;

    void update_position(Vector2f position);

public:
    PhysicalObject(PhysicalSettings settings);
    virtual ~PhysicalObject();

    int get_width();
    int get_height();
    Vector2f get_left_vertex();


    void set_speed(Vector2f speed);
    Vector2f get_speed();

	void set_jumping_speed(Vector2f speed);
	Vector2f get_jumping_speed();

    bool is_collided();
    void set_collided_state(bool flag);

    sf::Vector2f get_phys_size();
    PhysicalSettings get_phys_settings();
};

#endif // PhysicalObject_H
