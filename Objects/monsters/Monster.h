#ifndef MONSTER_H
#define MONSTER_H
#include"GameObject.h"
#include"bullets/Bullet.h"
#include"Physics/CollisionChecker.h"

/*
  base class for all monsters of any kind.
*/
    ///MONSTERS' TYPES
    /*
     stupid:
       >>> doesn't try to avoid hero's bullet
       >>> after finding hero waits 0.5 sec till shoot
       >>> don't "listen to" comrades 
       
     middle:
       >>> listen to comrades
       >>> try to avoid hero's bullet if hero isn't near
     
     smart:
       >>> listen to comrades
       >>> always avoid hero's bullet if one is near
       >>> shoot faster 
       
     suicide_boy:
       >>> the most stupid
       >>> when collides hero causes damage to him
       >>> when he see hero he flies to the one direction with high speed
       >>> dies if collides any wall
    */   
/*
  all monsters move at randomly chosen directory
  until they find target
*/
class Monster: public GameObject
{
protected: 
    int damage, health, direction;
    bool see_target;
 
    CollisionChecker collision_checker;
    bool check_collided_walls(vector<GameObject*>& walls);
    int generate_direction();
public:
    Monster(GraphicalSettings graph_settings,PhysicalSettings phys_settings, GameSettings game_settings);
    virtual ~Monster();

    virtual void go(vector<GameObject*>& walls)=0;
    virtual void search_target(Vector2f& target_pos)=0;
    bool is_dead();
    
};

#endif // MONSTER_H
