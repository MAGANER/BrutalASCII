#ifndef MYLEVEL_H
#define MYLEVEL_H

#include <Level.h>
#include"Player.h"


class myLevel : public Level
{
private:
    vector<GameObject*> walls;
    vector<GameObject*> usable_objects;//gun ammo
    vector<GameObject*> triggers;
    
    void sort_objects(); // loaded from file
public:
    myLevel();
    ~myLevel();
    
    vector<GameObject*>& get_walls();
    vector<GameObject*>& get_usable_objects();
    
    void draw(RenderWindow* window);
    void load(string level_path);
};

#endif // MYLEVEL_H
