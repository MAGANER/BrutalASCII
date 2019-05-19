#include "Player.h"

Player::Player(GraphicalSettings graph_settings,
               PhysicalSettings phys_settings,
                GameSettings game_settings):GameObject(graph_settings,phys_settings,game_settings)
{
    health = 10;
    ammo.brutgun = 0;
    ammo.cumgun = 0;
    ammo.pistol = 0;
    current_gun = -1;
    
    key_is_pressed = false;
    
}

Player::~Player()
{

}
void Player::move(int direction)
{
    update_position(get_position()); // update position of physical body
    
    switch(direction)
    {
    case Direction::left:
        gobject_spr.move(-0.5f,0.0f);
        shooting_direction = Bullet::Direction::left;
        moving_direction = Direction::left;
        animation_direction = moving_direction;
        break;
    case Direction::right:
        gobject_spr.move(0.5f,0.0f);
        shooting_direction = Bullet::Direction::right;
        moving_direction = Direction::right;
        animation_direction = moving_direction;
        break;
    case Direction::up:
        gobject_spr.move(0.0f,-0.5f);
        moving_direction = Direction::up;
        break;
    case Direction::down:
        gobject_spr.move(0.0f,0.5f);
        moving_direction = Direction::down;
        break;
    }
}
int Player::get_health()
{
    return health;
}
void Player::set_health(int health)
{
    this->health = health;
}
Ammo Player::get_ammo()
{
    return ammo;
}
void Player::set_ammo(int ammo, string type)
{
    if(type == "pistol")
    {
        this->ammo.pistol += ammo;
    }
    if(type == "cumgun")
    {
        this->ammo.cumgun += ammo;
    }
    if(type == "brutgun")
    {
        this->ammo.brutgun += ammo;
    }
}
bool Player::has_any_ammo()
{
    // checks can hero shoot any gun
    return ammo.brutgun+ammo.cumgun+ammo.pistol;
}
void Player::animate()
{
    if(animation_direction == Direction::left)
    {
        switch(current_gun)
        {
        case Guns::pistol:
            set_image("images/left_char_with_gun3.png");
            break;
        case Guns::cumgun:
            set_image("images/left_char_with_gun1.png");
            break;
        case Guns::brutgun:
            set_image("images/left_char_with_gun2.png");
            break;
        default:
            set_image("images/left_char.png");
            break;
        }
    }
    if(animation_direction == Direction::right)
    {
        switch(current_gun)
        {
        case Guns::pistol:
            set_image("images/char_with_gun3.png");
            break;
        case Guns::cumgun:
            set_image("images/char_with_gun1.png");
            break;
        case Guns::brutgun:
            set_image("images/char_with_gun2.png");
            break;
        default:
            set_image("images/char.png");
            break;        
         }
    }
}
void Player::shoot(vector<Bullet*>& hero_bullets)
{
    GraphicalSettings graph_settings;
    graph_settings.drawable = true;
    graph_settings.rotation = 0.0f;
    graph_settings.texture_rect = IntRect(0,0,10,10);
    if(shooting_direction == Bullet::Direction::right)
    {
        graph_settings.position = Vector2f(get_position().x+74,get_position().y+32);
    }
    if(shooting_direction == Bullet::Direction::left)
    {
        graph_settings.position = Vector2f(get_position().x-4,get_position().y+32);
    }
    PhysicalSettings phys_settings;
    phys_settings.height = 10;
    phys_settings.width = 10;
    phys_settings.main_vertex = graph_settings.position;
    
    GameSettings game_settings;
    game_settings.type = "bullet";
    
    if(current_gun == Guns::pistol && ammo.pistol > 0)
    {
        shoot_pistol(hero_bullets,graph_settings,phys_settings,game_settings);
        
        // when hero has no ammo, hide his current gun
        if(ammo.pistol == 0)
        {
            current_gun = -1;
        }
    }
    if(current_gun == Guns::cumgun && ammo.cumgun > 0)
    {
        shoot_cumgun(hero_bullets,graph_settings,phys_settings,game_settings);
        
        // when hero has no ammo, hide his current gun
        if(ammo.cumgun == 0)
        {
            current_gun = -1;
        }
    }
    if(current_gun == Guns::brutgun && ammo.brutgun > 0)
    {
        shoot_brutgun(hero_bullets,graph_settings,phys_settings,game_settings);
        
        // when hero has no ammo, hide his current gun
        if(ammo.brutgun == 0)
        {
            current_gun = -1;
        }
    }

}
void Player::shoot_pistol(vector<Bullet*>& hero_bullets,
                          GraphicalSettings& grsettings,
                          PhysicalSettings& psettings,
                          GameSettings& gsettings)
{
    Bullet* bullet;
    
    psettings.speed = Vector2f(0.6f,0.0f);
    grsettings.image = "images/pistol_bullet.png";
    int damage = 1;
        
    bullet = new Bullet(grsettings,psettings,gsettings,damage);
    bullet->set_direction(shooting_direction);
        
    hero_bullets.push_back(bullet);
    ammo.pistol-=1;
}
void Player::shoot_cumgun(vector<Bullet*>& hero_bullets,
                          GraphicalSettings& grsettings,
                          PhysicalSettings& psettings,
                          GameSettings& gsettings)
{
    Bullet* bullet;
    
    psettings.speed = Vector2f(0.8f,0.0f);
    grsettings.image = "images/cumgun_bullet.png";
    int damage = 2;
    
    bullet = new Bullet(grsettings,psettings,gsettings,damage);
    bullet->set_direction(shooting_direction);
    hero_bullets.push_back(bullet);
    ammo.cumgun-=1;
}
void Player::shoot_brutgun(vector<Bullet*>& hero_bullets,
                           GraphicalSettings& grsettings,
                           PhysicalSettings& psettings,
                           GameSettings& gsettings)
{
    Bullet* bullet1;
    Bullet* bullet2;
    Bullet* bullet3;
    
    int damage = 3;
    grsettings.image = "images/brutgun_bullet.png";
    
    // first bullet flies forward
    psettings.speed = Vector2f(0.7f,0.0f);
    bullet1 = new Bullet(grsettings,psettings,gsettings,damage);
    bullet1->set_direction(shooting_direction);
    hero_bullets.push_back(bullet1);
    
    //second bullet flies down
    psettings.speed = Vector2f(0.3f,0.2f);
    bullet2 = new Bullet(grsettings,psettings,gsettings,damage);
    bullet2->set_direction(shooting_direction);
    hero_bullets.push_back(bullet2);
    
    //third bullet flies up
    psettings.speed = Vector2f(0.3f,-0.2f);
    bullet3 = new Bullet(grsettings,psettings,gsettings,damage);
    bullet3->set_direction(shooting_direction);
    hero_bullets.push_back(bullet3);
    
    ammo.brutgun-=1;
}

void Player::choose_new_gun(int gun_number)
{
    switch(gun_number)
    {
    case Guns::pistol:
        if(ammo.pistol > 0)
            current_gun = Guns::pistol;
        break;
    case Guns::cumgun:
        if(ammo.cumgun > 0)
            current_gun = Guns::cumgun;
        break;
    case Guns::brutgun:
        if(ammo.brutgun > 0)
            current_gun = Guns::brutgun;
        break;
    }
    if(!has_any_ammo())
    {
        current_gun = -1;
    }
}

int Player::get_direction()
{
    return moving_direction;
}












