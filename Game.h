#pragma once
#include"MainMenu.h"
#include"Player.h"
#include"myLevel.h"
#include"Physics/CollisionChecker.h"
#include"Bullet.h"
#include<iostream>
//class runs whole game
class Game
{
private:
    Player* hero;
    int hero_direction;
    
    myLevel* level;
    MainMenu* menu;
	RenderWindow* window;
	View* camera;
    CollisionChecker collision_checker;
    
    vector<Bullet*> hero_bullets;

	enum GameState
	{
		game,
		main_menu,
		death
	};
	int current_state;
	bool level_is_loaded;
	int level_counter;
	bool key_is_pressed;
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
	
	bool check_object_collides_other_object(GameObject* object, int side,vector<GameObject*>& objects);
	void check_bullets_collided_walls();
	bool check_hero_takes_gun();
	void load_level();
	void draw_bullets();
public:
	Game();
	~Game();

	void run();
};

