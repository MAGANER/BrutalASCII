#ifndef BASESHOOTERMONSTER_H
#define BASESHOOTERMONSTER_H

#include"mod.h"
#include"Monster.h"
#include"Timer.h"
#include"Physics/CollisionChecker.h"

/*
 base class for monsters with guns
*/

class BaseShooterMonster : public Monster
{
private:
    CollisionChecker coll_checker;
    
    int old_direction;
private:
    int target_seeing_radius; // see target if it's in the radius
    Vector2f target_vision_radius[2]; //0 elem is start, 1 elem is end
   
    int attack_direction;
    
    Timer* shooting_timer;
protected:
    bool try_to_avoid_bullet;
    int avoiding_direction;
    
    bool pos_taken;
    Vector2f pos_before_running;
    void run_in_fear(int direction, bool able_to_go);
    
    void shoot(int direction,vector<Bullet*>& monster_bullets);
    bool is_bullet_near(vector<Bullet*>& hero_bullets);
    void animate();
public:
    BaseShooterMonster(GraphicalSettings graph_settings,
                       PhysicalSettings phys_settings,
                       GameSettings game_settings,
                       int visible_radius);
    virtual ~BaseShooterMonster();
    
    
    void search_target(Vector2f target_pos);
    void compute_target_vision_rad();
    
    bool does_see_any_wall(vector<GameObject*>& walls);
    void attack();
    void attack(vector<Bullet*>& monster_bullets);    
    
    virtual void avoid_bullet(vector<Bullet*> & hero_bullets, bool& able_to_go) =0;
    virtual void follow_target() =0;
};

#endif // BASESHOOTERMONSTER_H
