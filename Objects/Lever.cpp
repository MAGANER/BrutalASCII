#include "Lever.h"

Lever::Lever(GraphicalSettings graph_settings,
             PhysicalSettings phys_settings, 
             GameSettings game_settings):GameObject(graph_settings,
                                                    phys_settings,
                                                    game_settings)
{
    activated = false;
}

Lever::~Lever()
{

}
void Lever::set_activated_state(bool flag)
{
    activated = flag;
}
bool Lever::is_activated()
{
    return activated;
}
void Lever::animate()
{
    if(activated)
    {
        set_image("images/lever1.png");
    }
    else
    {
        set_image("images/lever.png");
    }
}