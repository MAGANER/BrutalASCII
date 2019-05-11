#pragma once
#include"MainMenu.h"
#include<iostream>
//class runs whole game
class Game
{
private:
    MainMenu* menu;
    
	RenderWindow* window;
	View* camera;


	enum GameState
	{
		game,
		main_menu,
		death
	};
	int current_state;
private:
	void check_window_events();
	void check_key_pressing();
	void draw();

	void run_game();
	void draw_game();
	void check_game_key_pressing();

	void run_main_menu();
	void draw_main_menu();
	void check_main_menu_key_pressing();

	void run_game_over();
	void draw_game_over();
	void check_game_over_key_pressing();
public:
	Game();
	~Game();

	void run();
};

