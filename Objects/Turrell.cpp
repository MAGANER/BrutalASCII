#include "Turrell.h"

Turrell::Turrell(GraphicalSettings graph_settings,
                 PhysicalSettings phys_settings,
                 GameSettings game_settings,
                 int shooting_direction):GameObject(graph_settings,phys_settings,game_settings)
{
    timer = new Timer(1.5f);
    time_to_shoot = 1.4f; 
    
    this->shooting_direction = shooting_direction;
}

Turrell::~Turrell()
{
    delete timer;
}

void Turrell::shoot(vector<Bullet*>& turrells_bullets)
{
    timer->tic();
    float elapsed_time = timer->get_elapsed_time().asSeconds();
    bool must_shoot = elapsed_time > time_to_shoot;
    if(must_shoot)
    {
        GraphicalSettings graph_settings;
        graph_settings.drawable = true;
        graph_settings.rotation = 0.0f;
        graph_settings.texture_rect = IntRect(0,0,10,10);
        graph_settings.image = "images/bullet.png";
        
        PhysicalSettings phys_settings;
        phys_settings.height = 10;
        phys_settings.width = 10;        
        GameSettings game_settings;
        game_settings.type = "bullet";
        int damage =1;
        
        //set position and speed, relating to shooting direction
        Vector2f turrel_pos = get_position();
        Vector2f bullet_pos;
        int bullet_direction;
        switch(shooting_direction)
        {
        case Direction::left:
            bullet_pos.x = turrel_pos.x - 4.0f;
            bullet_pos.y = turrel_pos.y +32.0f;
            phys_settings.speed = Vector2f(12.0f,0.0f);
            bullet_direction = Direction::left;
            break;
        case Direction::right:
            bullet_pos.x = turrel_pos.x + 68.0f;
            bullet_pos.y = turrel_pos.y + 32.0f;
            phys_settings.speed = Vector2f(12.0f,0.0f);
            bullet_direction = Direction::right;
            break;
        case Direction::down:
            bullet_pos.x = turrel_pos.x + 32.0f;
            bullet_pos.y = turrel_pos.y + 68.0f;
            phys_settings.speed = Vector2f(0.0f,12.0f);
            bullet_direction = Direction::down;
            break;
        case Direction::up:
            bullet_pos.x = turrel_pos.x + 25.0f;
            bullet_pos.y = turrel_pos.y + 4.0f;
            phys_settings.speed = Vector2f(0.0f,12.0f);
            bullet_direction = Direction::up;
            break;
        }
        graph_settings.position = bullet_pos;
        phys_settings.main_vertex = bullet_pos;
        
        
        Bullet* bullet = new Bullet(graph_settings,phys_settings,game_settings,damage);
        bullet->set_direction(bullet_direction);
        turrells_bullets.push_back(bullet);
    }
}
