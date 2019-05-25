/*
 base class for all objects in game:
*/

#pragma once
#include"Graphics/GraphicalObject.h"
#include"Physics/PhysicalObject.h"
struct GameSettings
{
	string type;
	int id;
};

class GameObject:public GraphicalObject,public PhysicalObject
{

private:
	string type;
	int id;
public:
	GameObject(GraphicalSettings graph_settings,PhysicalSettings phys_settings, GameSettings game_settings);
    virtual ~GameObject();
    
    string get_type();
	GameSettings get_game_settings();
	
    void set_position(float x, float y);
    void set_position(Vector2f position);
};

