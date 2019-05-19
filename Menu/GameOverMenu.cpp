#include "GameOverMenu.h"

GameOverMenu::GameOverMenu()
{
    font.loadFromFile("images/font.ttf");
    
    label = new Text("GAME FUCKIN' OVER",font,64);
    label->setPosition(5.0f,40.0f);
    
    to_return = new Text("To return:SPACE",font,32);
    to_return->setPosition(190.0f,200.0f);
    

}

GameOverMenu::~GameOverMenu()
{
    delete label;
    delete to_return;
}
void GameOverMenu::draw(RenderWindow* window)
{
    window->draw(*label);
    window->draw(*to_return);
}