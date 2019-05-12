#include "Parameters.h"

Parameters::Parameters()
{
    font.loadFromFile("images/font.ttf");
    
    health = new Text("health:",font,16);
    health->setPosition(0.0f,0.0f);
    
    pistol_ammo = new Text("pistol ammo:",font,16);
    pistol_ammo->setPosition(0.0f,20.0f);
    
    cumgun_ammo = new Text("cumgun ammo:",font,16);
    cumgun_ammo->setPosition(0.0f,40.0f);
    
    brutgun_ammo = new Text("brutgun ammo:",font,16);
    brutgun_ammo->setPosition(0.0f,60.0f);
}

Parameters::~Parameters()
{
    delete health;
    delete pistol_ammo;
    delete cumgun_ammo;
    delete brutgun_ammo;
}

void Parameters::draw(RenderWindow* window)
{
    window->draw(*health);
    window->draw(*pistol_ammo);
    window->draw(*cumgun_ammo);
    window->draw(*brutgun_ammo);
}
void Parameters::update(Ammo ammo,int hero_health)
{
    health->setString("health:"+to_string(hero_health));
    pistol_ammo->setString("pistol ammo:"+to_string(ammo.pistol));
    cumgun_ammo->setString("cumgun ammo:"+to_string(ammo.cumgun));
    brutgun_ammo->setString("brutgun ammo:"+to_string(ammo.brutgun));
}






