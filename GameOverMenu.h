#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H
#include"SFML/Graphics.hpp"
using namespace sf;

class GameOverMenu
{
private:
    Font font;
    Text* label;
    Text* to_return;
public:
    GameOverMenu();
    ~GameOverMenu();
    
    void draw(RenderWindow* window);


};

#endif // GAMEOVERMENU_H
