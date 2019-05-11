#include "PhysicalObject.h"

int PhysicalObject::get_width()
{
    return width;
}
int PhysicalObject::get_height()
{
    return height;
}
Vector2f PhysicalObject::get_left_vertex()
{
    return main_vertex;
}

void PhysicalObject::set_speed(Vector2f speed)
{
    this->speed = speed;
}
Vector2f PhysicalObject::get_speed()
{
    return speed;
}



bool PhysicalObject::is_collided()
{
    return collided;
}
void PhysicalObject::set_collided_state(bool flag)
{
    collided = flag;
}
PhysicalObject::PhysicalObject(PhysicalSettings settings)
{
    collided  = false;

    width  = settings.width;
    height = settings.height;
    main_vertex = settings.main_vertex;
    speed  = settings.speed;
	jumping_speed = settings.jumping_speed;

}
void PhysicalObject::update_position(Vector2f position)
{
    main_vertex = position;

    main_vertex.x = main_vertex.x;
    main_vertex.y = main_vertex.y;
}

PhysicalObject::~PhysicalObject()
{

}
sf::Vector2f PhysicalObject::get_phys_size()
{
    Vector2f size;
    size.x = (float)width;
    size.y = (float)height;
    return size;
}


PhysicalSettings PhysicalObject::get_phys_settings()
{
    PhysicalSettings settings;
    settings.speed = speed;
    settings.width = width;
    settings.height = height;
    settings.main_vertex = main_vertex;

    return settings;
}
Vector2f PhysicalObject::get_jumping_speed()
{
	return jumping_speed;
}
void PhysicalObject::set_jumping_speed(Vector2f speed)
{
	jumping_speed = speed;
}

