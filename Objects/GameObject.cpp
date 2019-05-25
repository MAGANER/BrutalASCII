#include "GameObject.h"



GameObject::GameObject(GraphicalSettings graph_settings, PhysicalSettings phys_settings, GameSettings game_settings)
	:GraphicalObject(graph_settings), PhysicalObject(phys_settings)
{
	type = game_settings.type;
	id = game_settings.id;
}


GameObject::~GameObject()
{
}

string GameObject::get_type()
{
	return type;
}
int GameObject::get_id()
{
	return id;
}
void GameObject::set_position(Vector2f position)
{
    gobject_spr.setPosition(position);
    update_position(position);
}
void GameObject::set_position(float x, float y)
{
    Vector2f position;

    position.x = x;
    position.y = y;

	gobject_spr.setPosition(position);
	update_position(position);
}