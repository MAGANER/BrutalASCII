#include "Game.h"

Game::Game()
{
	window = new RenderWindow(VideoMode(720, 640), "BrutalDeath");
	menu = new MainMenu();
	level = new myLevel();
	timer = new Timer(3.0f);
	camera = new View();
	camera->setSize(400.0f,420.0f);
	
	///////hero creating//////////
	//////////////////////////////
	GraphicalSettings* graph_settings = new GraphicalSettings();
	PhysicalSettings* phys_settings = new PhysicalSettings();
	GameSettings* game_settings = new GameSettings();
	
	graph_settings->drawable = true;
	graph_settings->image = "images/char.png";
	graph_settings->position = Vector2f(80.0f,200.0f);
	graph_settings->texture_rect = IntRect(0,0,64,64);
	
	phys_settings->width = 64;
	phys_settings->height = 64;
	phys_settings->main_vertex = graph_settings->position;
	
	game_settings->type = "hero";
	
    hero = new Player(*graph_settings,*phys_settings,*game_settings);
	delete graph_settings;
	delete phys_settings;
	delete game_settings;
	//////////////////////////////

	current_state = GameState::main_menu;
	level_is_loaded = false;
	level_counter = 0;
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
			run_game();
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
    
    camera->setCenter(hero->get_position());
	window->clear();
	switch (current_state)
	{
	case GameState::main_menu:
		draw_main_menu();
		break;
	case GameState::game:
        window->setView(*camera);
		draw_game();
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

void Game::check_game_key_pressing(float delta_time)
{
    typedef Keyboard kb;     
    
    if(kb::isKeyPressed(kb::A))
    {
        bool collision = check_object_collides_wall(hero,Sides::left);
        if(!collision) hero->move(hero->Direction::left,delta_time);
    }
    if(kb::isKeyPressed(kb::D))
    {
        bool collision = check_object_collides_wall(hero,Sides::right);
        if(!collision) hero->move(hero->Direction::right,delta_time);
    }
    if(kb::isKeyPressed(kb::W))
    {
        bool collision = check_object_collides_wall(hero,Sides::top);
        if(!collision)hero->move(hero->Direction::up,delta_time);
    }
    if(kb::isKeyPressed(kb::S))
    {
        bool collision = check_object_collides_wall(hero,Sides::bottom);
        if(!collision) hero->move(hero->Direction::down,delta_time);
    }
}
void Game::draw_game()
{
    level->draw(window);
    window->draw(hero->returnSprite());
}
void Game::run_game()
{
    timer->tic();
    float elapsed_time = timer->get_elapsed_time().asMilliseconds();
    float delta_time = 1.0f;
    
    load_level();
    check_game_key_pressing(delta_time);
    draw_game();
}
void Game::load_level()
{
    if(!level_is_loaded)
    {
        level->load("levels/"+to_string(level_counter)+".json");
        camera->zoom(2);
        level_is_loaded = true;
    }
}
bool Game::check_object_collides_wall(GameObject* object, int side)
{
   vector<GameObject*> walls = level->get_walls();
   CollisionCounter counter = collision_checker.count_object_collisions(hero,walls);
   
   switch(side)
   {
   case Sides::left:
    if(counter.left_side_collisions>0)
    {
        return true;
    }
    else
    {
        return false;
    }
    break;
   case Sides::right:
    if(counter.right_side_collisions>0)
    {
        return true;
    }
    else
    {
        return false;
    }
    break; 
   case Sides::top:
    if(counter.top_side_collisions>0)
    {
        return true;
    }
    else
    {
        return false;
    }
    break;
   case Sides::bottom:
    if(counter.bottom_side_collisions>0)
    {
        return true;
    }
    else
    {
        return false;
    }
    break;
   }
}















