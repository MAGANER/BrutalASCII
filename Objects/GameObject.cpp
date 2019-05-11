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
