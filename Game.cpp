#include "Game.h"

Game::Game()
{
	window = new RenderWindow(VideoMode(720, 640), "BrutalDeath");
	menu = new MainMenu();

	current_state = GameState::main_menu;
}
Game::~Game()
{
	delete window;
}

void Game::check_window_events()
{
	Event event;
	while (window->pollEvent(event))
	{
		if (Event::Closed == event.type)
		{
			window->close();
		}
	}
}
void Game::run()
{
	while (window->isOpen())
	{
		check_window_events();

		check_key_pressing();
		switch (current_state)
		{
		case GameState::main_menu:
			run_main_menu();
			break;
		case GameState::game:
			//run_game();
			break;
		case GameState::death:
			//run_game_over();
			break;
		}
		draw();

	}
}
void Game::draw()
{
	window->clear();
	switch (current_state)
	{
	case GameState::main_menu:
		draw_main_menu();
		break;
	case GameState::game:
		//draw_game();
		break;
	case GameState::death:
		//draw_game_over();
		break;
	}
	window->display();
}
void Game::check_key_pressing()
{
	switch (current_state)
	{
	case GameState::main_menu:
		check_main_menu_key_pressing();
		break;
	case GameState::game:
		//check_game_key_pressing();
		break;
	case GameState::death:
		//check_game_over_key_pressing();
		break;
	}
}

void Game::check_main_menu_key_pressing()
{
    if(Keyboard::isKeyPressed(Keyboard::Space))
    {
        current_state = GameState::game;
        delete menu;
    }
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
        current_state = GameState::game;
        delete menu;
        window->close();
    }
}
void Game::draw_main_menu()
{
    menu->draw(window);
}

void Game::run_main_menu()
{
    check_main_menu_key_pressing();
    draw_main_menu();
}





