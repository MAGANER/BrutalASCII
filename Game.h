#pragma once
#include"Menu/MainMenu.h"
#include"Menu/GameOverMenu.h"
#include"Menu/Parameters.h"
#include"Player.h"
#include"myLevel.h"
#include"Physics/CollisionChecker.h"
#include"Physics/Direction.h"
#include"Bullet.h"
#include<iostream>
#include<time.h>

//class runs whole game
class Game
{
private:
    Player* hero;
    
    myLevel* level;
    bool level_is_loaded;
	int level_counter;
	int lever_counter; // counts activated levers
    
    ///menu///
    MainMenu* menu;
    //hero will never be back to menu from game
    //so when game starts menu must be deleted
    bool menu_is_deleted;
    void delete_menu();
    
    GameOverMenu* game_over;
    Parameters* parameters_panel;
    /////////////////////////
    
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

	bool key_is_pressed;
private:
	void check_window_events();

	void run_game();
	void draw_game();
	void check_game_key_pressing();

	void run_main_menu();
	void check_main_menu_key_pressing();

	void run_game_over();
	void check_game_over_key_pressing();
	
	bool check_object_collides_other_object(GameObject* object, int direction,vector<GameObject*>& objects);
	void check_bullets_collided_walls();
	void check_hero_collided_thorns();
	void check_hero_teleports_to_next_level();
	void check_hero_activated_lever();
	bool check_hero_takes_gun();
    void check_hero_died();
	
	void load_level();
	void draw_bullets();

public:
	Game();
	~Game();

	void run();
};

