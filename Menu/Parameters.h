#ifndef PARAMETERS_H
#define PARAMETERS_H
#include"SFML/Graphics.hpp"
#include"Player.h"
using namespace sf;

/*
  menu that draws hero's ammo counter,
  health and maybe something else
*/

class Parameters
{
private:
    Font font;
    Text* health;
    Text* pistol_ammo;
    Text* cumgun_ammo;
    Text* brutgun_ammo;
    Text* doublegun_ammo;
    Text* madgun_ammo;
public:
    Parameters();
    ~Parameters();
    
    void draw(RenderWindow* window);
    void update(Ammo ammo,int hero_health);

};

#endif // PARAMETERS_H
