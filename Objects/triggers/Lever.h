#ifndef LEVER_H
#define LEVER_H

#include <GameObject.h>

//levers activates portal
//hero must activate 3 lever
//and then he will be able to teleport
class Lever : public GameObject
{
private:
    bool activated;
public:
    Lever(GraphicalSettings graph_settings,
          PhysicalSettings phys_settings, 
          GameSettings game_settings);
    ~Lever();
    
    void set_activated_state(bool flag);
    bool is_activated();
    void animate();

};

#endif // LEVER_H
