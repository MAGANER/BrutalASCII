#ifndef MYLEVEL_H
#define MYLEVEL_H

#include <Level.h>
#include"Player.h"

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
    
    void sort_objects(); // loaded from file
public:
    myLevel();
    ~myLevel();
    
    vector<GameObject*>& get_walls();
    vector<GameObject*>& get_usable_objects();
    Vector2f get_hero_start();
    GameObject* get_trigger(string type);//this trigger is one at current level
    
    void draw(RenderWindow* window); // level
    void load(string level_path); // load objects and then sort them
    
    void clear();
};

#endif // MYLEVEL_H
