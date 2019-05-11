#include "MainMenu.h"

MainMenu::MainMenu()
{
    font.loadFromFile("images/font.ttf");
    
    label = new Text("Brutal ASCII",font,64);
    label->setPosition(100.0f,40.0f);
    
    to_play = new Text("To play:SPACE",font,32);
    to_play->setPosition(190.0f,200.0f);
    
    to_die = new Text("To die:ESCAPE",font,32);
    to_die->setPosition(190.0f,300.0f);
}

MainMenu::~MainMenu()
{
    delete label;
    delete to_play;
    delete to_die;
}

void MainMenu::draw(RenderWindow* window)
{
    window->draw(*to_die);
    window->draw(*to_play);
    window->draw(*label);
}








