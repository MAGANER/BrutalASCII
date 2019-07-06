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
    
    shooting_timer = new Timer(0.41f);
    
    try_to_avoid_bullet = false;
    pos_taken = false;
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
    if(!see_target)
    {
        Monster::go(ability_to_go);
    }
    else if(try_to_avoid_bullet)
    {
        cout<<"FUCK"<<endl;
        if(ability_to_go)
        {
            cout<<"hey"<<endl;
            run_in_fear(avoiding_direction);
        }
    }

}
void BaseShooterMonster::animate()
{
    if(direction == Direction::left && !see_target)
    {
        set_image("images/left_enemy.png");
    }
    if(direction == Direction::right  && !see_target)
    {
        set_image("images/right_enemy.png");
    }
    
    if(attack_direction == Direction::left && see_target)
    {
        set_image("images/left_enemy.png");
    }
    if(attack_direction == Direction::right && see_target)
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
        int length = mod(my_pos.x) - mod(bullet_pos.x);
        //cout<<length<<endl;
        if(length > 50)
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
void BaseShooterMonster::run_in_fear(int direction)
{
    cout<<"ass"<<endl;
    Vector2f pos_to_run; 
    Vector2f current_pos = get_position();
    if(avoiding_direction == Direction::down)
    {
      pos_to_run = Vector2f(pos_before_running.x, pos_before_running.y-100.0f);
      
      bool finished_pos_to_run  = current_pos.y < pos_to_run.y;
      if(!finished_pos_to_run)
      {
          speed = Vector2f(0.0f,10.0f);//increase speed
          update_position(current_pos);
          gobject_spr.move(0.0f,-speed.y);
      }
      else
      {
          try_to_avoid_bullet = false;
          speed = Vector2f(5.0f,5.0f);
      }
      
    }
    if(avoiding_direction == Direction::up)
    {
        pos_to_run = Vector2f(pos_before_running.x, pos_before_running.y+100.0f);
        
        bool finished_pos_to_run = current_pos.y > pos_to_run.y;
        if(!finished_pos_to_run)
        {
          speed = Vector2f(0.0f,10.0f);//increase speed
          update_position(current_pos);
          gobject_spr.move(0.0f,speed.y);
        }
        else
        {
            try_to_avoid_bullet = false;
            speed = Vector2f(5.0f,5.0f);
        }
    }
}









