#include "CollisionChecker.h"


CollisionCounter CollisionChecker::count_object_collisions(GameObject * object, vector<GameObject*> & other_objects)
{
    CollisionCounter counter;

    int top_side_collisions = 0;
    int bottom_side_collisions = 0;
    int left_side_collisions = 0;
    int right_side_collisions = 0;

    for(size_t i = 0; i<other_objects.size();i++)
    {
        if(top_side_collision(object,other_objects[i]))
        {
            top_side_collisions++;
        }
        if(bottom_side_collision(object,other_objects[i]))
        {
            bottom_side_collisions++;
        }
        if(left_side_collision(object,other_objects[i]))
        {
            left_side_collisions++;
        }
        if(right_side_collision(object,other_objects[i]))
        {
            right_side_collisions++;
        }
    }
    counter.set_count(top_side_collisions,
                      bottom_side_collisions,
                      left_side_collisions,
                      right_side_collisions);


    return counter;

}
CollisionCounter CollisionChecker::count_object_collisions(GameObject * object, vector<GameObject*> & other_objects, string check_type)
{
    //this method checks collision between object and only objects with check_type from vector
    CollisionCounter counter;

    int top_side_collisions = 0;
    int bottom_side_collisions = 0;
    int left_side_collisions = 0;
    int right_side_collisions = 0;

    for(size_t i = 0; i<other_objects.size();i++)
    {
        if(other_objects[i]->get_type() == check_type)
        {
            if(top_side_collision(object,other_objects[i]))
            {
                //
                top_side_collisions++;
            }
            if(bottom_side_collision(object,other_objects[i]))
            {
                bottom_side_collisions++;
            }
            if(left_side_collision(object,other_objects[i]))
            {
                left_side_collisions++;
            }
            if(right_side_collision(object,other_objects[i]))
            {
                right_side_collisions++;
            }
        }

    }

    counter.set_count(top_side_collisions,
                      bottom_side_collisions,
                      left_side_collisions,
                      right_side_collisions);


    return counter;

}
CollisionCounter CollisionChecker::count_object_collisions(GameObject * objectA, GameObject * objectB)
{
    CollisionCounter counter;

    int top_side_collisions = 0;
    int bottom_side_collisions = 0;
    int left_side_collisions = 0;
    int right_side_collisions = 0;


    if(top_side_collision(objectA,objectB))
    {
        top_side_collisions++;
    }
    if(bottom_side_collision(objectA,objectB))
    {
        bottom_side_collisions++;
    }
    if(left_side_collision(objectA,objectB))
    {
        left_side_collisions++;
    }
    if(right_side_collision(objectA,objectB))
    {
        right_side_collisions++;
    }

    counter.set_count(top_side_collisions,
                      bottom_side_collisions,
                      left_side_collisions,
                      right_side_collisions);

    return counter;

}
CollisionCounter CollisionChecker::count_object_collisions(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
        CollisionCounter counter;

    int top_side_collisions = 0;
    int bottom_side_collisions = 0;
    int left_side_collisions = 0;
    int right_side_collisions = 0;


    if(top_side_collision(objectA_settings,objectB_settings))
    {
        top_side_collisions++;
    }
    if(bottom_side_collision(objectA_settings,objectB_settings))
    {
        bottom_side_collisions++;
    }
    if(left_side_collision(objectA_settings,objectB_settings))
    {
        left_side_collisions++;
    }
    if(right_side_collision(objectA_settings,objectB_settings))
    {
        right_side_collisions++;
    }

    counter.set_count(top_side_collisions,
                      bottom_side_collisions,
                      left_side_collisions,
                      right_side_collisions);

    return counter;
}


bool CollisionChecker::object_collides(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    bool first_case  = bottom_side_collision(objectA_settings,objectB_settings);
    bool second_case = top_side_collision(objectA_settings,objectB_settings);
    bool third_case  = left_side_collision(objectA_settings,objectB_settings);
    bool fourth_case = right_side_collision(objectA_settings,objectB_settings);

    return first_case||second_case||third_case||fourth_case;
}
bool CollisionChecker::object_collides(GameObject* objectA, GameObject * objectB)
{
    bool first_case  = bottom_side_collision(objectA,objectB);
    bool second_case = top_side_collision(objectA,objectB);
    bool third_case  = left_side_collision(objectA,objectB);
    bool fourth_case = right_side_collision(objectA,objectB);

    return first_case||second_case||third_case||fourth_case;
}
bool CollisionChecker::object_collides(GameObject* object, vector<GameObject*> & other_objects)
{
    for(size_t i = 0; i< other_objects.size(); ++i)
    {
        if(object_collides(object,other_objects[i]))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // if there are no objects, so no any collisions
    return false;
}


bool CollisionChecker::is_object_lefter(PhysicalObject * objectA, PhysicalObject * objectB)
{
    //it's true if objectA's right side is lefter than objectB's left one

    float objectA_right_vertex = objectA->get_left_vertex().x + objectA->get_width();
    float objectB_left_vertex  = objectB->get_left_vertex().x;

    return objectB_left_vertex > objectA_right_vertex;
}
bool CollisionChecker::is_object_lefter(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
     //it's true if objectA's right side is lefter than objectB's left one

    float objectA_right_vertex = objectA_settings.main_vertex.x + objectA_settings.width;
    float objectB_left_vertex  = objectB_settings.main_vertex.x;

    return objectB_left_vertex > objectA_right_vertex;
}


bool CollisionChecker::is_object_righter(PhysicalObject * objectA, PhysicalObject * objectB)
{
    //it's true if objectA's left side is righter than objectB's right one

    float objectA_left_vertex = objectA->get_left_vertex().x;
    float objectB_right_vertex = objectB->get_left_vertex().x +objectB->get_width();

    return objectA_left_vertex > objectB_right_vertex;
}
bool CollisionChecker::is_object_righter(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    //it's true if objectA's left side is righter than objectB's right one

    float objectA_left_vertex = objectA_settings.main_vertex.x;
    float objectB_right_vertex = objectB_settings.main_vertex.x +objectB_settings.width;

    return objectA_left_vertex > objectB_right_vertex;
}


bool CollisionChecker::are_objects_near_with_y(PhysicalObject * objectA, PhysicalObject * objectB)
{
    /*
    objects' y positions are near to each other:
    (first case)
    if objectA's y position is between
    objectB's top and down y vertex
    (second case)
    if objectB's y position is between
    objectA's top and down y vertex
    */
    float objectA_top_vertex = objectA->get_left_vertex().y;
    float objectB_top_vertex = objectB->get_left_vertex().y;


    float objectA_bottom_vertex   = objectA->get_left_vertex().y + objectA->get_height();
    float objectB_bottom_vertex = objectB->get_left_vertex().y + objectB->get_height();


    bool first_case  = objectA_top_vertex  > objectB_top_vertex
                    && objectA_top_vertex <  objectB_bottom_vertex;


    bool second_case = objectA_top_vertex    < objectB_top_vertex
                    && objectA_bottom_vertex > objectB_top_vertex;

    return first_case || second_case;
}
bool CollisionChecker::are_objects_near_with_y(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    /*
    objects' y positions are near to each other:
    (first case)
    if objectA's y position is between
    objectB's top and down y vertex
    (second case)
    if objectB's y position is between
    objectA's top and down y vertex
    */
    float objectA_top_vertex = objectA_settings.main_vertex.y;
    float objectB_top_vertex = objectB_settings.main_vertex.y;


    float objectA_bottom_vertex   = objectA_settings.main_vertex.y + objectA_settings.height;
    float objectB_bottom_vertex = objectB_settings.main_vertex.y + objectB_settings.height;


    bool first_case  = objectA_top_vertex  > objectB_top_vertex
                    && objectA_top_vertex <  objectB_bottom_vertex;


    bool second_case = objectA_top_vertex    < objectB_top_vertex
                    && objectA_bottom_vertex > objectB_top_vertex;

    return first_case || second_case;
}


bool CollisionChecker::are_object_near_with_x(PhysicalObject * objectA, PhysicalObject * objectB)
{
    /*
    objects' x positions are near to each other:
    (first case)
    if objectA's x position is between
    objectB's left and right x vertex
    (second case)
    if objectB's x position is between
    objectA's left and right x vertex
    */

    float objectA_left_vertex = objectA->get_left_vertex().x;
    float objectB_left_vertex = objectB->get_left_vertex().x;


    float objectA_right_vertex = objectA->get_left_vertex().x + objectA->get_width();
    float objectB_right_vertex = objectB->get_left_vertex().x + objectB->get_width();


    bool first_case = objectA_right_vertex >  objectB_right_vertex
                   && objectA_left_vertex  <  objectB_right_vertex;

    bool second_case = objectA_left_vertex  < objectB_left_vertex
                   &&  objectA_right_vertex > objectB_left_vertex;


    return first_case || second_case;
}
bool CollisionChecker::are_object_near_with_x(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    /*
    objects' x positions are near to each other:
    (first case)
    if objectA's x position is between
    objectB's left and right x vertex
    (second case)
    if objectB's x position is between
    objectA's left and right x vertex
    */

    float objectA_left_vertex = objectA_settings.main_vertex.x;
    float objectB_left_vertex = objectB_settings.main_vertex.x;


    float objectA_right_vertex = objectA_settings.main_vertex.x + objectA_settings.width;
    float objectB_right_vertex = objectB_settings.main_vertex.x + objectB_settings.width;


    bool first_case = objectA_right_vertex >  objectB_right_vertex
                   && objectA_left_vertex  <  objectB_right_vertex;

    bool second_case = objectA_left_vertex  < objectB_left_vertex
                   &&  objectA_right_vertex > objectB_left_vertex;


    return first_case || second_case;
}


bool CollisionChecker::does_x1_equals_x2(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    //it's true if objectA's x position equals objectB's one
    return objectA_settings.main_vertex.x == objectB_settings.main_vertex.x;
}
bool CollisionChecker::does_x1_equals_x2(PhysicalObject * objectA, PhysicalObject * objectB)
{
    //it's true if objectA's x position equals objectB's one
    return objectA->get_left_vertex().x == objectB->get_left_vertex().x;
}


bool CollisionChecker::does_y1_equals_y2(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    //it's true if objectA's y position equals objectB's one
    return objectA_settings.main_vertex.y == objectB_settings.main_vertex.y;
}
bool CollisionChecker::does_y1_equals_y2(PhysicalObject * objectA, PhysicalObject * objectB)
{
    //it's true if objectA's y position equals objectB's one
    return objectA->get_left_vertex().y == objectB->get_left_vertex().y;
}


bool CollisionChecker::left_side_collision(PhysicalObject * objectA, PhysicalObject * objectB)
{
    //check is objectA's left side colliding objectB's right one

    float objectA_left_side  = objectA->get_left_vertex().x;
    float objectA_bottom_side = objectA->get_left_vertex().y + objectA->get_height();
    float objectA_top_side    = objectA->get_left_vertex().y;


    float objectB_right_side = objectB->get_left_vertex().x + objectB->get_width();
    float objectB_left_side  = objectB->get_left_vertex().x;
    float objectB_top_side    = objectB->get_left_vertex().y;
    float objectB_bottom_side = objectB->get_left_vertex().y+objectB->get_height();

    bool first_condition  = objectA_left_side  < objectB_right_side;
    bool fifth_condition  = objectA_left_side  > objectB_left_side;


    /*
     when objectA stands on objectB, it touches objectB
     and so it can not move.
    */
    bool second_condition = (int)objectA_bottom_side != (int)objectB_top_side;
    bool sixth_condition  = (int)objectA_top_side+1  != (int)objectB_bottom_side;

    bool third_condition = are_objects_near_with_y(objectA,objectB)
                          || does_y1_equals_y2(objectA,objectB);

    bool fourth_condition  = !is_object_righter(objectB,objectA);



    bool collision =  first_condition
                  && third_condition
                  && fourth_condition
                  && fifth_condition
                  && (second_condition && sixth_condition);


    return collision;
}
bool CollisionChecker::left_side_collision(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    //check is objectA's left side colliding objectB's right one

    float objectA_left_side  = objectA_settings.main_vertex.x;
    float objectA_bottom_side = objectA_settings.main_vertex.y + objectA_settings.height;
    float objectA_top_side    = objectA_settings.main_vertex.y;


    float objectB_right_side = objectB_settings.main_vertex.x + objectB_settings.width;
    float objectB_left_side  = objectB_settings.main_vertex.x;
    float objectB_top_side    = objectB_settings.main_vertex.y;
    float objectB_bottom_side = objectB_settings.main_vertex.y+objectB_settings.height;

    bool first_condition  = objectA_left_side  < objectB_right_side;
    bool fifth_condition  = objectA_left_side  > objectB_left_side;


    /*
     when objectA stands on objectB, it touches objectB
     and so it can not move.
    */
    bool second_condition = (int)objectA_bottom_side != (int)objectB_top_side;
    bool sixth_condition  = (int)objectA_top_side+1  != (int)objectB_bottom_side;

    bool third_condition = are_objects_near_with_y(objectA_settings,objectB_settings)
                          || does_y1_equals_y2(objectA_settings,objectB_settings);

    bool fourth_condition  = !is_object_righter(objectB_settings,objectA_settings);



    bool collision =  first_condition
                  && third_condition
                  && fourth_condition
                  && fifth_condition
                  && (second_condition && sixth_condition);


    return collision;
}


bool CollisionChecker::right_side_collision(PhysicalObject * objectA, PhysicalObject * objectB)
{
    //check is objectA's right side colliding objectB's left one

    float objectA_right_side  = objectA->get_left_vertex().x + objectA->get_width();
    float objectA_bottom_side = objectA->get_left_vertex().y + objectA->get_height();
    float objectA_top_side    = objectA->get_left_vertex().y;

    float objectB_left_side   = objectB->get_left_vertex().x;
    float objectB_right_side  = objectB->get_left_vertex().x + objectB->get_width();
    float objectB_top_side    = objectB->get_left_vertex().y;
    float objectB_bottom_side = objectB->get_left_vertex().y+objectB->get_height();

    bool first_condition  = objectA_right_side > objectB_left_side;
    bool fifth_condition  = objectB_right_side > objectA_right_side;



    /*
     when objectA stands on objectB, it touches objectB
     and so it can not move.
    */
    bool second_condition = (int)objectA_bottom_side != (int)objectB_top_side;
    bool sixth_condition  = (int)objectA_top_side+1  != (int)objectB_bottom_side;

    bool third_condition = are_objects_near_with_y(objectA,objectB)
                          || does_y1_equals_y2(objectA,objectB);

    bool fourth_condition  = !is_object_lefter(objectB,objectA);


    bool collision = first_condition
                  && third_condition
                  && fourth_condition
                  && fifth_condition;
                  //&& (second_condition && sixth_condition);


    return collision;
}
bool CollisionChecker::right_side_collision(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    //check is objectA's right side colliding objectB's left one

    float objectA_right_side  = objectA_settings.main_vertex.x + objectA_settings.width;
    float objectA_bottom_side = objectA_settings.main_vertex.y + objectA_settings.height;
    float objectA_top_side    = objectA_settings.main_vertex.y;

    float objectB_left_side   = objectB_settings.main_vertex.x;
    float objectB_right_side  = objectB_settings.main_vertex.x + objectB_settings.width;
    float objectB_top_side    = objectB_settings.main_vertex.y;
    float objectB_bottom_side = objectB_settings.main_vertex.y+objectB_settings.height;

    bool first_condition  = objectA_right_side > objectB_left_side;
    bool fifth_condition  = objectB_right_side > objectA_right_side;



    /*
     when objectA stands on objectB, it touches objectB
     and so it can not move.
    */
    bool second_condition = (int)objectA_bottom_side != (int)objectB_top_side;
    bool sixth_condition  = (int)objectA_top_side+1  != (int)objectB_bottom_side;

    bool third_condition = are_objects_near_with_y(objectA_settings,objectB_settings)
                          || does_y1_equals_y2(objectA_settings,objectB_settings);

    bool fourth_condition  = !is_object_lefter(objectB_settings,objectA_settings);


    bool collision = first_condition
                  && third_condition
                  && fourth_condition
                  && fifth_condition;
                  //&& (second_condition && sixth_condition);


    return collision;
}


bool CollisionChecker::bottom_side_collision(PhysicalObject * objectA, PhysicalObject * objectB)
{
    //check is objectA's bottom side colliding objectB's top one

    float objectA_bottom_side = objectA->get_left_vertex().y + objectA->get_height();
    float objectB_top_side    = objectB->get_left_vertex().y;

    float objectA_right_side  = objectA->get_left_vertex().x + objectA->get_width();
    float objectA_left_side   = objectA->get_left_vertex().x;

    float objectB_left_side   = objectB->get_left_vertex().x;
    float objectB_right_side  = objectB->get_left_vertex().x + objectB->get_width();

    bool first_condition   =  objectA_bottom_side > objectB_top_side;
    bool second_condition =  objectA_bottom_side < objectB_top_side+50;
    bool third_condition  =  are_object_near_with_x(objectA,objectB) ||
                             does_x1_equals_x2(objectA,objectB);

    // if objectA doesn't stand on ObjectB,than he collides its right/left side
    // and so objectA "touches" objectB and so collision is true
    bool fourth_condition =  (int)objectA_right_side != (int)objectB_left_side;
    bool fifth_condition  =  (int)objectA_left_side+50  != (int)objectB_right_side;



    bool collision = first_condition
                  && second_condition
                  && third_condition;
                //  && ( fifth_condition && fourth_condition);

    if(collision)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool CollisionChecker::bottom_side_collision(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    //check is objectA's bottom side colliding objectB's top one

    float objectA_bottom_side = objectA_settings.main_vertex.y + objectA_settings.height;
    float objectB_top_side    = objectB_settings.main_vertex.y;

    float objectA_right_side  = objectA_settings.main_vertex.x + objectA_settings.width;
    float objectA_left_side   = objectA_settings.main_vertex.x;

    float objectB_left_side   = objectB_settings.main_vertex.x;
    float objectB_right_side  = objectB_settings.main_vertex.x + objectB_settings.width;

    bool first_condition   =  objectA_bottom_side > objectB_top_side;
    bool second_condition =  objectA_bottom_side < objectB_top_side+50;
    bool third_condition  =  are_object_near_with_x(objectA_settings,objectB_settings) ||
                             does_x1_equals_x2(objectA_settings,objectB_settings);

    // if objectA doesn't stand on ObjectB,than he collides its right/left side
    // and so objectA "touches" objectB and so collision is true
    bool fourth_condition =  (int)objectA_right_side != (int)objectB_left_side;
    bool fifth_condition  =  (int)objectA_left_side+50  != (int)objectB_right_side;



    bool collision = first_condition
                  && second_condition
                  && third_condition;
                 // && ( fifth_condition && fourth_condition);

    if(collision)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool CollisionChecker::top_side_collision(PhysicalObject * objectA, PhysicalObject * objectB)
{
    //check is objectA's top side colliding objectB's bottom side

    float objectA_top_side    = objectA->get_left_vertex().y;
    float objectB_bottom_side = objectB->get_left_vertex().y + objectB->get_height();

    float objectA_right_side  = objectA->get_left_vertex().x + objectA->get_width();
    float objectA_left_side   = objectA->get_left_vertex().x;

    float objectB_left_side   = objectB->get_left_vertex().x;
    float objectB_right_side  = objectB->get_left_vertex().x + objectB->get_width();

    bool first_condition   = objectA_top_side < objectB_bottom_side;
    bool second_condition  = objectA_top_side > objectB_bottom_side-15;
    bool third_condition   = are_object_near_with_x(objectA,objectB) ||
                             does_x1_equals_x2(objectA,objectB);



    // if objectA doesn't stand on ObjectB,than he collides its right/left side
    // and so objectA "touches" objectB and so collision is true
    bool fourth_condition =  (int)objectA_right_side != (int)objectB_left_side;
    bool fifth_condition  =  (int)objectA_left_side+1  != (int)objectB_right_side;



    bool collision = first_condition
                  && second_condition
                  && third_condition;
                  //&& ( fifth_condition && fourth_condition);
    if(collision)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool CollisionChecker::top_side_collision(PhysicalSettings objectA_settings,PhysicalSettings objectB_settings)
{
    //check is objectA's top side colliding objectB's bottom side

    float objectA_top_side    = objectA_settings.main_vertex.y;
    float objectB_bottom_side = objectB_settings.main_vertex.y + objectB_settings.height;

    float objectA_right_side  = objectA_settings.main_vertex.x + objectA_settings.width;
    float objectA_left_side   = objectA_settings.main_vertex.x;

    float objectB_left_side   = objectB_settings.main_vertex.x;
    float objectB_right_side  = objectB_settings.main_vertex.x + objectB_settings.width;

    bool first_condition   = objectA_top_side < objectB_bottom_side;
    bool second_condition  = objectA_top_side > objectB_bottom_side-15;
    bool third_condition   = are_object_near_with_x(objectA_settings,objectB_settings) ||
                             does_x1_equals_x2(objectA_settings,objectB_settings);



    // if objectA doesn't stand on ObjectB,than he collides its right/left side
    // and so objectA "touches" objectB and so collision is true
    bool fourth_condition =  (int)objectA_right_side != (int)objectB_left_side;
    bool fifth_condition  =  (int)objectA_left_side+1  != (int)objectB_right_side;



    bool collision = first_condition
                  && second_condition
                  && third_condition;
                  //&& ( fifth_condition && fourth_condition);
    if(collision)
    {
        return true;
    }
    else
    {
        return false;
    }
}


CollisionChecker::CollisionChecker()
{
}

CollisionChecker::~CollisionChecker()
{
}
