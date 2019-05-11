#include "CollisionCounter.h"

CollisionCounter::CollisionCounter()
{
    top_side_collisions    = 0;
    bottom_side_collisions = 0;
    left_side_collisions   = 0;
    right_side_collisions  = 0;
}
int CollisionCounter::get_collisions_summ()
{
    return top_side_collisions     +
            bottom_side_collisions +
            left_side_collisions   +
            right_side_collisions;

}


void CollisionCounter::set_count(int top_collisions,
                                 int bottom_collisions,
                                 int left_collisions,
                                 int right_collisions)
{
    top_side_collisions    = top_collisions;
    bottom_side_collisions = bottom_collisions;
    left_side_collisions   = left_collisions;
    right_side_collisions  = right_collisions;
}
CollisionCounter::~CollisionCounter()
{

}
