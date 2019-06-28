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
    keys = 0;
    
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
        gobject_spr.move(-8.5f,0.0f);
        shooting_direction = Direction::left;
        animation_direction = moving_direction;
        break;
    case Direction::right:
        gobject_spr.move(8.5f,0.0f);
        shooting_direction = Direction::right;
        animation_direction = moving_direction;
        break;
    case Direction::up:
        gobject_spr.move(0.0f,-8.5f);
        break;
    case Direction::down:
        gobject_spr.move(0.0f,8.5f);
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
    if(type == "madgun")
    {
        this->ammo.madgun += ammo;
    }
    if(type == "doublegun")
    {
        this->ammo.doublegun +=ammo;
    }
}
bool Player::has_any_ammo()
{
    // checks can hero shoot any gun
    return ammo.brutgun+ammo.cumgun+ammo.pistol + ammo.doublegun + ammo.madgun;
}
void Player::animate()
{
    bool move_down_or_up = animation_direction == Direction::down || animation_direction == Direction::up;
    if(animation_direction == Direction::left || move_down_or_up)
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
        case Guns::doublegun:
            set_image("images/left_char_with_gun5.png");
            break;
        case Guns::madgun:
            set_image("images/left_char_with_gun4.png");
            break;
        default:
            set_image("images/left_char.png");
            break;
        }
    }
    if(animation_direction == Direction::right || move_down_or_up)
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
        case Guns::doublegun:
            set_image("images/char_with_gun5.png");
            break;
        case Guns::madgun:
            set_image("images/char_with_gun4.png");
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
    if(shooting_direction == Direction::right)
    {
        graph_settings.position = Vector2f(get_position().x+90,get_position().y+32);
    }
    if(shooting_direction == Direction::left)
    {
        graph_settings.position = Vector2f(get_position().x-10,get_position().y+32);
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
    if(current_gun == Guns::madgun && ammo.madgun > 0)
    {
        shoot_madgun(hero_bullets,graph_settings,phys_settings,game_settings);
        
        // when hero has no ammo, hide his current gun
        if(ammo.madgun == 0)
        {
            current_gun = -1;
        }
    }
    if(current_gun == Guns::doublegun && ammo.doublegun > 0)
    {
        shoot_doublegun(hero_bullets,graph_settings,phys_settings,game_settings);
        
        // when hero has no ammo, hide his current gun
        if(ammo.doublegun == 0)
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
    
    psettings.speed = Vector2f(10.6f,0.0f);
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
    
    psettings.speed = Vector2f(15.8f,0.0f);
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
    
    int damage = 2;
    grsettings.image = "images/brutgun_bullet.png";
    
    // first bullet flies forward
    psettings.speed = Vector2f(11.7f,0.0f);
    bullet1 = new Bullet(grsettings,psettings,gsettings,damage);
    bullet1->set_direction(shooting_direction);
    hero_bullets.push_back(bullet1);
    
    //second bullet flies down
    psettings.speed = Vector2f(11.3f,9.2f);
    bullet2 = new Bullet(grsettings,psettings,gsettings,damage);
    bullet2->set_direction(shooting_direction);
    hero_bullets.push_back(bullet2);
    
    //third bullet flies up
    psettings.speed = Vector2f(11.3f,-9.2f);
    bullet3 = new Bullet(grsettings,psettings,gsettings,damage);
    bullet3->set_direction(shooting_direction);
    hero_bullets.push_back(bullet3);
    
    ammo.brutgun-=1;
}
void Player::shoot_doublegun(vector<Bullet*>& hero_bullets,
                             GraphicalSettings& grsettings,
                             PhysicalSettings& psettings,
                             GameSettings& gsettings)
{
    Bullet* left_bullet;
    Bullet* right_bullet;
    
    psettings.speed = Vector2f(12.0f,0.0f);
    grsettings.image = "images/doublegunbullet.png";
    int damage = 2;
    
    Vector2f bullet_pos = grsettings.position;
    grsettings.position = Vector2f(get_position().x +80,bullet_pos.y);
    right_bullet = new Bullet(grsettings,psettings,gsettings,damage);
    right_bullet->set_direction(Direction::right);
    hero_bullets.push_back(right_bullet);
    
    
    psettings.speed = Vector2f(-12.0f,0.0f);
    
    Vector2f hero_position = get_position();
    Vector2f old_bullet_position = right_bullet->get_position();
    grsettings.position = Vector2f(hero_position.x -34,old_bullet_position.y);
    psettings.main_vertex = grsettings.position;
    
    grsettings.image = "images/doublegunbullet.png";
    
    left_bullet = new Bullet(grsettings,psettings,gsettings,damage);
    left_bullet->set_direction(Direction::right);
    hero_bullets.push_back(left_bullet);
    
    ammo.doublegun-=1;
}
void Player::shoot_madgun(vector<Bullet*>& hero_bullets,
                          GraphicalSettings& grsettings, 
                          PhysicalSettings& psettings, 
                          GameSettings& gsettings)
{
    MadBullet* bullet;
    
    grsettings.image = "images/madbullet.png";
    int damage = 1;//shall be generated,when mad bullet object will be constructed
    
    bullet = new MadBullet(grsettings,psettings,gsettings,damage);
    bullet->set_direction(shooting_direction);
        
    hero_bullets.push_back(bullet);
    ammo.madgun-=1;
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
        
    case Guns::doublegun:
        if(ammo.doublegun > 0)
            current_gun = Guns::doublegun;
        break;
        
    case Guns::madgun:
        if(ammo.madgun > 0)
            current_gun = Guns::madgun;
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
void Player::set_direction(int value)
{
    moving_direction = value;
}
void Player::destroy_ammo()
{
    ammo.brutgun*=0;
    ammo.cumgun*=0;
    ammo.doublegun*=0;
    ammo.madgun*=0;
    ammo.pistol*=0;
}

void Player::set_keys(int number)
{
    keys = number;
}
int Player::get_keys()
{
    return keys;
}










