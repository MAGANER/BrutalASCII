#include "myLevel.h"

myLevel::myLevel()
{
}

myLevel::~myLevel()
{
}

void myLevel::draw(vector<GameObject*>objects, RenderWindow* window)
{
    auto object = objects.begin();
    while(object != objects.end())
    {
        bool is_drawable = (*object)->is_drawable();
        if(is_drawable) window->draw((*object)->returnSprite());
        ++object;
    }
}
void myLevel::draw_level(RenderWindow* window)
{
    draw(walls,window);
    draw(usable_objects,window);
    draw(triggers,window);
    draw(thorns,window);
    
    auto lever = levers.begin();
    while(lever != levers.end())
    {
        (*lever)->animate();
        window->draw((*lever)->returnSprite());
        ++lever;
    }
    
    auto turrel = turrels.begin();
    while(turrel != turrels.end())
    {
        window->draw((*turrel)->returnSprite());
        ++turrel;
    }
    
    auto monster = monsters.begin();
    while(monster != monsters.end())
    {
        window->draw((*monster)->returnSprite());
        ++monster;
    }
    
    auto shooter  = shooting_monsters.begin();
    while(shooter !=shooting_monsters.end())
    {
        window->draw((*shooter)->returnSprite());
        ++shooter;
    }
}
void myLevel::sort_objects()
{
    // sort objects,relating to their types
    
    auto object = objects.begin();
    
    while(object != objects.end())
    {
        string type = (*object)->get_type();
        
        bool is_wall = type == "wall" || type == "twall";
        
        bool is_gun = type == "pistol" ||
                      type == "cumgun" || 
                      type == "brutgun"||
                      type == "madgun" ||
                      type == "doublegun" ||
                      type == "key";
                      
        bool is_trigger = 
                          type == "level_portal" ||
                          type == "door" ||
                          type == "shit"; // means start
        
        bool is_thorn = type == "thorn";
        
        bool is_lever = type =="lever";
        
        bool is_turrel = type == "lturrell" ||
                         type == "rturrell" ||
                         type == "uturrell" ||
                         type == "dturrell";
                         
        bool is_suicide_boy = type == "sboy";
        bool is_stupid_monster = type =="smob";
        bool is_middle_monster = type =="mmob";
        bool is_monster = is_suicide_boy || is_stupid_monster || is_middle_monster;
        if(is_monster)
        {
            GraphicalSettings graph_settings = (*object)->get_graphical_settings();
            PhysicalSettings phys_settings = (*object)->get_phys_settings();
            phys_settings.speed = Vector2f(5.0f,5.0f);
            GameSettings game_settings = (*object)->get_game_settings();
            
            
            srand(time(0)); //in monster's constructor moving direction is generated 
            if(is_suicide_boy)
            {
                SuicideBoy* monster = new SuicideBoy(graph_settings,phys_settings,game_settings);
                monsters.push_back(monster);
            }
            if(is_stupid_monster)
            {
                StupidShooter* monster = new StupidShooter(graph_settings,phys_settings,game_settings,160);
                shooting_monsters.push_back(monster);
            }
            if(is_middle_monster)
            {
                MiddleShooter* monster = new MiddleShooter(graph_settings,phys_settings,game_settings,180);
                shooting_monsters.push_back(monster);
            }
        }
        else if(is_wall)
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
        else if(is_lever || is_turrel)
        {
            GraphicalSettings graph_settings = (*object)->get_graphical_settings();
            PhysicalSettings phys_settings = (*object)->get_phys_settings();
            GameSettings game_settings = (*object)->get_game_settings();
            if(is_lever)
            {
                 Lever* lever = new Lever(graph_settings,phys_settings,game_settings);
                 levers.push_back(lever);
            }
            if(is_turrel)
            {
                int direction = get_turrell_direction(type);
                Turrell* turrell = new  Turrell(graph_settings,phys_settings,game_settings,direction);
                turrels.push_back(turrell);
            }

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
vector<Lever*>& myLevel::get_levers()
{
    return levers;
}
vector<Turrell*>& myLevel::get_turrels()
{
    return turrels;
}
vector<Monster*>& myLevel::get_monsters()
{
    return monsters;
}
vector<BaseShooterMonster*>& myLevel::get_shooting_monsters()
{
    return shooting_monsters;
}
int myLevel::get_turrell_direction(string type)
{
    if(type == "lturrell")
    {
        return Direction::left;
    }
    if(type == "rturrell")
    {
        return Direction::right;
    }
    if(type == "uturrell")
    {
        return Direction::up;
    }
    if(type == "dturrell")
    {
        return Direction::down;
    }
}

void myLevel::clear()
{
    walls.clear();
    usable_objects.clear();
    triggers.clear();
    thorns.clear();
    levers.clear();
    monsters.clear();
    shooting_monsters.clear();
    
}
Vector2f myLevel::get_hero_start()
{
    auto trigger = triggers.begin();
    while(trigger != triggers.end())
    {
        string type = (*trigger)->get_type();
        if(type == "shit")
        {
            cout<<"ass"<<endl;
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










