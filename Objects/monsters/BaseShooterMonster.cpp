#include "BaseShooterMonster.h"

BaseShooterMonster::BaseShooterMonster(GraphicalSettings graph_settings,
                                       PhysicalSettings phys_settings,
                                        GameSettings game_settings,
                                        int visible_radius)
                :Monster(graph_settings,phys_settings,game_settings)
{
    target_seeing_radius = visible_radius;
    
    shooting_timer = new Timer(0.41f);
    
    try_to_avoid_bullet = false;
    pos_taken = false;
    
}

BaseShooterMonster::~BaseShooterMonster()
{
    delete shooting_timer;
}


void BaseShooterMonster::compute_target_vision_rad()
{
    Vector2f start;
    Vector2f end;
    if(looking_direction == Direction::left)
    {
        start.x = mod(get_position().x);
        start.y = mod(get_position().y);
        
        end.x = mod(start.x - target_seeing_radius);
        end.y = mod(start.y);
    }
    if(looking_direction == Direction::right)
    {
        start.x = mod(get_position().x + 64.0f);
        start.y = mod(get_position().y);
        
        end.x = mod(start.x + target_seeing_radius);
        end.y = mod(start.y);
    }
    
    target_vision_radius[0] = start;
    target_vision_radius[1] = end;
}
void BaseShooterMonster::search_target(Vector2f target_pos)
{
    Vector2f my_pos = get_position();
    
    compute_target_vision_rad();
    
    
    //check see target on Ox
    bool first_case = mod(target_vision_radius[0].x) < mod(target_pos.x) &&
                      mod(target_vision_radius[1].x) > mod(target_pos.x);
                      
    bool second_case= mod(target_vision_radius[0].x) > mod(target_pos.x) &&
                      mod(target_vision_radius[1].x) < mod(target_pos.x);
    
    //check see target on Oy
    bool on_the_same_line_OY_first_case =  ( my_pos.y < target_pos.y &&
                                             my_pos.y+64.0f > target_pos.y );
                                
                
    bool on_the_same_line_OY_second_case =  ( my_pos.y < target_pos.y+64.0f &&
                                              my_pos.y > target_pos.y );
    bool see_target_on_OY = on_the_same_line_OY_first_case ||
                            on_the_same_line_OY_second_case;
    
    
    //set attack direction
    if(first_case && see_target_on_OY)
    {
        attack_direction = Direction::right;
    }
    else if(second_case && see_target_on_OY)
    {
        attack_direction = Direction::left;
    }
    
    bool target_within_seeing_radius =see_target_on_OY && (first_case || second_case);
    if(target_within_seeing_radius)
    {
        see_target = true;
    }
    else
    {
        see_target = false;
    }
    
    animate();
}
bool BaseShooterMonster::does_see_any_wall(vector<GameObject*>& walls)
{
    for(size_t i = 0;i<walls.size();++i)
    {
        Vector2f wall_pos = walls[i]->get_position();
        Vector2f mob_pos = get_position();
        
        bool see_wall_OY_first_case = target_vision_radius[0].y < wall_pos.y &&
                                      target_vision_radius[1].y > wall_pos.y;
                                          
        bool see_wall_OY_second_case= target_vision_radius[0].y < wall_pos.y &&
                                      target_vision_radius[1].y > wall_pos.y;
                                      
        bool see_wall_OY = see_wall_OY_first_case || see_wall_OY_second_case;
        
        bool see_wall_OX = target_vision_radius[0].x < wall_pos.x &&
                           target_vision_radius[1].x > wall_pos.x;
                           
                           
        // if monster sees wall,than the end of his seeing vector is start of wall
        if(see_wall_OX && see_wall_OY)
        {
            target_vision_radius[1].x = wall_pos.x;
            return true;
        }
        else
        {
            return false;
        }
        
    }
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









