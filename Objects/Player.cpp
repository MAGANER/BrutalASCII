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
}

Player::~Player()
{

}

void Player::move(int direction)
{
    update_position(get_position());
    switch(direction)
    {
    case Direction::left:
        gobject_spr.move(-0.6f,0.0f);
        shooting_direction = Bullet::Direction::left;
        break;
    case Direction::right:
        gobject_spr.move(0.6f,0.0f);
        shooting_direction = Bullet::Direction::right;
        break;
    case Direction::up:
        gobject_spr.move(0.0f,-0.6f);
        break;
    case Direction::down:
        gobject_spr.move(0.0f,0.6f);
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
    return ammo.brutgun+ammo.cumgun+ammo.pistol;
}
void Player::animate(int direction)
{
    bool only_pistol = ammo.pistol > 0 && ammo.brutgun == 0 && ammo.cumgun == 0;
    bool only_cumgun = ammo.cumgun > 0 && ammo.brutgun == 0 && ammo.pistol == 0;
    bool only_brutgun= ammo.brutgun > 0 && ammo.cumgun == 0 && ammo.pistol == 0;
    if(only_brutgun)
    {
        current_gun = Guns::brutgun;
    }
    else if(only_cumgun)
    {
        current_gun = Guns::cumgun;
    }
    else if(only_pistol)
    {
        current_gun = Guns::pistol;
    }
    else
    {
        current_gun = -1; // no gun
    }
    if(direction == Direction::left)
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
    if(direction == Direction::right)
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
    Bullet* bullet;
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
        graph_settings.image = "images/pistol_bullet.png";
        bullet = new Bullet(graph_settings,phys_settings,game_settings,1);
        bullet->set_direction(shooting_direction);
        hero_bullets.push_back(bullet);
        ammo.pistol-=1;
    }
    if(current_gun == Guns::cumgun && ammo.cumgun > 0)
    {
        graph_settings.image = "images/cumgun_bullet.png";
        bullet = new Bullet(graph_settings,phys_settings,game_settings,2);
        bullet->set_direction(shooting_direction);
        hero_bullets.push_back(bullet);
        ammo.cumgun-=1;
    }
    if(current_gun == Guns::brutgun && ammo.brutgun > 0)
    {
        graph_settings.image = "images/brutgun_bullet.png";
        bullet = new Bullet(graph_settings,phys_settings,game_settings,3);
        bullet->set_direction(shooting_direction);
        hero_bullets.push_back(bullet);
        ammo.brutgun-=1;
    }

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














