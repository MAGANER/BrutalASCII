#include "BaseShooterMonster.h"

BaseShooterMonster::BaseShooterMonster(GraphicalSettings graph_settings,
                                       PhysicalSettings phys_settings,
                                        GameSettings game_settings,
                                        int visible_radius)
                :Monster(graph_settings,phys_settings,game_settings)
{
    target_seeing_radius = visible_radius;
}

BaseShooterMonster::~BaseShooterMonster()
{
}

void BaseShooterMonster::search_target(Vector2f target_pos)
{
    Vector2f my_pos = get_position();
    
    bool is_lefter  = target_pos.x+64.0f < my_pos.x;
    bool is_righter = target_pos.x > my_pos.x+64.0f;
    
    bool see_target = abs(target_pos.x < my_pos.x+target_seeing_radius);
    
    if(is_lefter && see_target)
    {
        attack_direction = Direction::left;
    }
    if(is_righter && see_target)
    {
        attack_direction = Direction::right;
    }
}
void BaseShooterMonster::attack()
{
    //this method isn't used
}
void BaseShooterMonster::attack(vector<Bullet*>& monster_bullets)
{
    if(see_target)
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
    if(direction == Direction::left)
    {
        set_image("images/left_enemy.png");
    }
    if(direction == Direction::right)
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


