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
    
    //draw triggers
    auto trigger = triggers.begin();
    while(trigger != triggers.end())
    {
        bool is_drawable = (*trigger)->is_drawable();
        if(is_drawable)window->draw((*trigger)->returnSprite());
        ++trigger;
    }
    
    //draw thorns
    auto thorn = thorns.begin();
    while(thorn != thorns.end())
    {
        bool is_drawable = (*thorn)->is_drawable();
        if(is_drawable)window->draw((*thorn)->returnSprite());
        ++thorn;
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
        
        bool is_gun = type == "pistol" ||
                      type == "cumgun" || 
                      type == "brutgun"||
                      type == "madgun" ||
                      type == "doublegun";
                      
        bool is_trigger = type == "start" || 
                          type == "level_portal";
                          
        bool is_thorn = type == "thorn";
                          
        
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
            triggers.push_back(*object);
        }
        else if(is_thorn)
        {
            thorns.push_back(*object);
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
vector<GameObject*>& myLevel::get_triggers()
{
    return triggers;
}
vector<GameObject*>& myLevel::get_thorns()
{
    return thorns;
}

void myLevel::clear()
{
    walls.clear();
    usable_objects.clear();
    triggers.clear();
    thorns.clear();
}
Vector2f myLevel::get_hero_start()
{
    auto trigger = triggers.begin();
    while(trigger != triggers.end())
    {
        string type = (*trigger)->get_type();
        if(type == "start")
        {
            return (*trigger)->get_position();
        }
        ++trigger;
    }
}
GameObject* myLevel::get_trigger(string type)
{
    auto trigger = triggers.begin();
    while(trigger != triggers.end())
    {
        string current_trigger_type = (*trigger)->get_type();
        if(type == current_trigger_type)
        {
            return (*trigger);
        }
        ++trigger;
    }
}



