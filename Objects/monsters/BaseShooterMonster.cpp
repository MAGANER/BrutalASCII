#include "BaseShooterMonster.h"

BaseShooterMonster::BaseShooterMonster(GraphicalSettings graph_settings,
                                       PhysicalSettings phys_settings,
                                        GameSettings game_settings,
                                        int visible_radius)
                :Monster(graph_settings,phys_settings,game_settings)
{
    target_seeing_radius = visible_radius;
       
    
      // \\    
    //(^_^)\\ 
    
    //just for fun
    if(direction == Direction::down || direction == Direction::up)
    {
        target_seeing_radius*=4;
    }
    
    shooting_timer = new Timer(1.0f);
}

BaseShooterMonster::~BaseShooterMonster()
{
    delete shooting_timer;
}


void BaseShooterMonster::search_target(Vector2f target_pos)
{
    Vector2f my_pos = get_position();
    
    bool is_lefter  = target_pos.x+64.0f < my_pos.x;
    bool is_righter = target_pos.x > my_pos.x+64.0f;
    
    bool on_the_same_line_OY;
    if(direction == Direction::left || direction == Direction::right)
    {
        bool on_the_same_line_OY_first_case = ( mod(my_pos.y) > mod(target_pos.y) ) &&
                                              ( mod(my_pos.y+64.0f) < mod(target_pos.y));
                                          
        bool on_the_same_line_OY_second_case = ( mod(my_pos.y) > mod(target_pos.y+64.0f) ) &&
                                               ( mod(my_pos.y) < mod(target_pos.y));
    
        bool on_the_same_line_OY_third_case  = mod(my_pos.y) == mod(target_pos.y);
                                          
        on_the_same_line_OY = on_the_same_line_OY_first_case ||
                              on_the_same_line_OY_second_case||
                              on_the_same_line_OY_third_case;
    }
    else
    {
        bool on_the_same_line_OY_first_case = ( mod(my_pos.y) > mod(target_pos.y) ) &&
                                              ( mod(my_pos.y) < mod(target_pos.y + 64.0f));
                                              
        bool on_the_same_line_OY_second_case = ( mod(target_pos.y) > mod(my_pos.y) ) &&
                                               ( mod(target_pos.y) < mod(my_pos.y + 64.0f));
                                               
        on_the_same_line_OY = on_the_same_line_OY_first_case ||
                              on_the_same_line_OY_second_case;
    }
    

                                                                               
    
    bool see_target_at_right_direction =  mod(target_pos.x) < mod(my_pos.x+64.0f+target_seeing_radius);
    bool see_target_at_left_direction  =  mod(target_pos.x+64.0f) < mod(my_pos.x-target_seeing_radius);
    
    
    bool monster_moves_up_or_down = direction == Direction::down || direction == Direction::up;
    
    bool target_is_lefter  = is_lefter                    &&
                             see_target_at_left_direction && 
                             (direction == Direction::left || monster_moves_up_or_down);
                            
    bool target_is_righter = is_righter                    && 
                             see_target_at_right_direction && 
                             (direction == Direction::right || monster_moves_up_or_down); 
                             
    bool attack_left  = target_is_lefter && on_the_same_line_OY;
    bool attack_right = target_is_righter && on_the_same_line_OY;
    if(attack_left)
    {
        attack_direction = Direction::left;
        see_target = true;
    }
    else if(attack_right)
    {
        attack_direction = Direction::right;
        see_target = true;
    }
    else
    {
        see_target = false;
    }
    
    animate();
}
void BaseShooterMonster::attack()
{
    //this method isn't used
}
void BaseShooterMonster::attack(vector<Bullet*>& monster_bullets)
{
        shooting_timer->tic();
        Time elapsed_time = shooting_timer->get_elapsed_time();
        if(elapsed_time.asSeconds() > 0.4f)
        {
            shoot(attack_direction,monster_bullets);
        }
}
void BaseShooterMonster::shoot(int direction, vector<Bullet*>& monster_bullets)
{
    Bullet* bullet;
    PhysicalSettings psettings;
    GraphicalSettings grsettings;
    GameSettings gsettings;
    
    grsettings.drawable = true;
    grsettings.rotation = 0.0f;
    grsettings.texture_rect = IntRect(0,0,10,10);
    if(attack_direction == Direction::right)
    {
        grsettings.position = Vector2f(get_position().x+90,get_position().y+32);
    }
    if(attack_direction == Direction::left)
    {
        grsettings.position = Vector2f(get_position().x-10,get_position().y+32);
    }
    
    psettings.speed = Vector2f(10.0f,0.0f);
    psettings.height = 10;
    psettings.width = 10;
    psettings.main_vertex = grsettings.position;
    
    gsettings.type = "bullet";
    grsettings.image = "images/cumgun_bullet.png";
    int damage = 2;
    
    bullet = new Bullet(grsettings,psettings,gsettings,damage);
    bullet->set_direction(direction);
    monster_bullets.push_back(bullet);
}
void BaseShooterMonster::go(bool ability_to_go)
{
    animate();
    Monster::go(ability_to_go);
}
void BaseShooterMonster::animate()
{
    if(direction == Direction::left || attack_direction == Direction::left)
    {
        set_image("images/left_enemy.png");
    }
    if(direction == Direction::right || attack_direction == Direction::right)
    {
        set_image("images/right_enemy.png");
    }
}
bool BaseShooterMonster::is_bullet_near(vector<Bullet*>& hero_bullets)
{
    for(size_t i = 0;i<hero_bullets.size();++i)
    {
        Vector2f bullet_pos = hero_bullets[i]->get_position();
        Vector2f my_pos = get_position();
        int length = bullet_pos.x + my_pos.x;
        if(length < 30)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
bool BaseShooterMonster::is_any_wall_between_itself_and_target(vector<GameObject*>& walls,Vector2f target_pos)
{
    for(size_t i = 0;i<walls.size();++i)
    {
        Vector2f wall_pos = walls[i]->get_position();
        Vector2f mob_pos = get_position();
        
        bool wall_is_lefter_than_target  = wall_pos.x +64.0f < target_pos.x;
        bool wall_is_righter_than_target = wall_pos.x > target_pos.x + 64.0f;
        
        bool wall_is_lefter_than_mob = wall_pos.x +64.0f < mob_pos.x;
        bool wall_is_righter_than_mob = wall_pos.x > mob_pos.x + 64.0f;
        
        //if wall is lefter/righter than both target and monster
        //than it's not between em
        
        bool first_case  = wall_is_lefter_than_mob  && wall_is_lefter_than_target;
        bool second_case = wall_is_righter_than_mob && wall_is_righter_than_target;
        if(first_case || second_case)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}










