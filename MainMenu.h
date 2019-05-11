#ifndef MAINMENU_H
#define MAINMENU_H
#include"SFML/Graphics.hpp"
using namespace sf;

class MainMenu
{
private:
    Font font;
    Text* label;
    
    Text* to_play;
    Text* to_die;
public:
    MainMenu();
    ~MainMenu();
    
    void draw(RenderWindow* window);


};

#endif // MAINMENU_H
