#ifndef MYLEVEL_H
#define MYLEVEL_H

#include <Level.h>
#include"Player.h"
#include"triggers/Lever.h"
#include"triggers/Turrell.h"
#include"Physics/Direction.h"
#include"monsters/SuicideBoy.h"
#include"monsters/StupidShooter.h"

/*
 when all data is loaded to objects vector
 all of them must be sorted into different vectors,
 relating to their types
*/
class myLevel : public Level
{
private:
    vector<GameObject*> walls;
    vector<GameObject*> usable_objects;//gun, ammo e.t.c
    vector<GameObject*> triggers;
    vector<GameObject*> thorns;
    vector<Monster*> monsters;
    vector<BaseShooterMonster*> shooting_monsters;
    vector<Lever*> levers;
    
    vector<Turrell*> turrels;
    int get_turrell_direction(string type);
    
    void sort_objects(); // loaded from file
    
    void draw(vector<GameObject*> objects, RenderWindow* window);
public:
    myLevel();
    ~myLevel();
    
    vector<GameObject*>& get_walls();
    vector<GameObject*>& get_usable_objects();
    vector<GameObject*>& get_triggers();
    vector<GameObject*>& get_thorns();
    vector<Monster*>& get_monsters();
    vector<BaseShooterMonster*>& get_shooting_monsters();
    vector<Monster*>& get_ALL_monsters();
    vector<Lever*>& get_levers();
    vector<Turrell*>& get_turrels();
    
    Vector2f get_hero_start();
    GameObject* get_trigger(string type);//this trigger is one at current level
    
    void draw_level(RenderWindow* window); // whole level
    void load(string level_path); // load objects and then sort them
    
    
    void clear();
};

#endif // MYLEVEL_H
