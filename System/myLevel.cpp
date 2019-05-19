#include "myLevel.h"

myLevel::myLevel()
{
}

myLevel::~myLevel()
{
}


void myLevel::draw(RenderWindow* window)
{
    /// draw whole level
    
    //draw walls
    auto wall = walls.begin();
    while(wall != walls.end())
    {
        window->draw((*wall)->returnSprite());
        ++wall;
    }
    
    //draw usable objects
    auto usable_object = usable_objects.begin();
    while(usable_object != usable_objects.end())
    {
        window->draw((*usable_object)->returnSprite());
        ++usable_object;
    }
}
void myLevel::sort_objects()
{
    
    // sort objects,relating to their types
    auto object = objects.begin();
    while(object != objects.end())
    {
        string type = (*object)->get_type();
        
        bool is_wall = type == "wall";
        bool is_gun = type == "pistol" || type == "cumgun" || type == "brutgun";
        bool is_trigger = type == "start";
        
        if(is_wall)
        {
            walls.push_back(*object);
        }
        else if(is_gun)
        {
            usable_objects.push_back(*object);
        }
        else if(is_trigger)
        {
            usable_objects.push_back(*object);
        }
        ++object;
    }
    
    // now it's useless
    objects.clear();
}
void myLevel::load(string level_path)
{
    Level::load(level_path);
    sort_objects();
}
vector<GameObject*>& myLevel::get_walls()
{
    return walls;
}
vector<GameObject*>& myLevel::get_usable_objects()
{
    return usable_objects;
}
void myLevel::clear()
{
    walls.clear();
    usable_objects.clear();
    triggers.clear();
}

