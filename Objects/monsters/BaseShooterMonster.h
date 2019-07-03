#ifndef BASESHOOTERMONSTER_H
#define BASESHOOTERMONSTER_H


#include"Monster.h"

/*
 base class for monsters with guns
*/

class BaseShooterMonster : public Monster
{
private:
    int target_seeing_radius;
protected:
    int attack_direction;
    void shoot(int direction,vector<Bullet*>& monster_bullets);
    bool is_bullet_near(vector<Bullet*>& hero_bullets);
    void animate();
public:
    BaseShooterMonster(GraphicalSettings graph_settings,
                       PhysicalSettings phys_settings,
                       GameSettings game_settings,
                       int visible_radius);
    virtual ~BaseShooterMonster();
    
    void go(bool ability_to_go);
    void search_target(Vector2f target_pos);
    void attack();
    void attack(vector<Bullet*>& monster_bullets);
    
    
    virtual void avoid_bullet() =0;
    virtual void follow_target() =0;
    
};

#endif // BASESHOOTERMONSTER_H
