#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include"CollisionCounter.h"
#include"GameObject.h"

class CollisionChecker
{
private:
    CollisionCounter collision_counter;

    bool is_object_lefter(PhysicalObject * objectA, PhysicalObject * objectB);
    bool is_object_lefter(PhysicalSettings objectA_settings, PhysicalSettings objectB_settings);

    bool is_object_righter(PhysicalObject * objectA, PhysicalObject * objectB);
    bool is_object_righter(PhysicalSettings objectA_settings, PhysicalSettings objectB_settings);


    bool are_objects_near_with_y(PhysicalObject * objectA, PhysicalObject * objectB);
    bool are_objects_near_with_y(PhysicalSettings objectA_settings, PhysicalSettings objectB_settings);

    bool are_object_near_with_x(PhysicalObject * objectA, PhysicalObject * objectB);
    bool are_object_near_with_x(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings);

    bool does_x1_equals_x2(PhysicalObject * objectA, PhysicalObject * objectB);
    bool does_x1_equals_x2(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings);

    bool does_y1_equals_y2(PhysicalObject * objectA, PhysicalObject * objectB);
    bool does_y1_equals_y2(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings);


    bool left_side_collision(PhysicalObject * objectA, PhysicalObject * objectB);
    bool left_side_collision(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings);

    bool right_side_collision(PhysicalObject * objectA, PhysicalObject * objectB);
    bool right_side_collision(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings);

    bool bottom_side_collision(PhysicalObject * objectA, PhysicalObject * objectB);
    bool bottom_side_collision(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings);

    bool top_side_collision(PhysicalObject * objectA, PhysicalObject * objectB);
    bool top_side_collision(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings);

public:
    CollisionChecker();
    ~CollisionChecker();

    CollisionCounter count_object_collisions(GameObject * object, vector<GameObject*> & other_objects);
    CollisionCounter count_object_collisions(GameObject * object, vector<GameObject*> & other_objects, string check_type);
    CollisionCounter count_object_collisions(GameObject * objectA, GameObject * objectB);
    CollisionCounter count_object_collisions(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings);


    bool object_collides(GameObject* object, vector<GameObject*> & other_objects);
    bool object_collides(GameObject* objectA, GameObject * objectB);
    bool object_collides(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings);
};

#endif // COLLISIONCHECKER_H
