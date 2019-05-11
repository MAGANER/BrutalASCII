#ifndef COLLISIONCOUNTER_H
#define COLLISIONCOUNTER_H


class CollisionCounter
{
public:
    int top_side_collisions;
    int bottom_side_collisions;
    int left_side_collisions;
    int right_side_collisions;
public:
    int get_collisions_summ();

    void set_count(int top_collisions,
                   int bottom_collisions,
                   int left_collisions,
                   int right_collions);
    CollisionCounter();
    ~CollisionCounter();


};


#endif // COLLISIONCOUNTER_H
