#include "Game.h"

Game::Game()
{
	window = new RenderWindow(VideoMode(720, 640), "BrutalDeath");
	menu = new MainMenu();
	level = new myLevel();
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
	
	key_is_pressed = false;
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

void Game::check_game_key_pressing()
{
    typedef Keyboard kb;     
    
    if(kb::isKeyPressed(kb::A))
    {
        bool collision = check_object_collides_other_object(hero,Sides::left,level->get_walls());
        if(!collision) hero->move(hero->Direction::left);
        hero_direction =  hero->Direction::left;
    }
    if(kb::isKeyPressed(kb::D))
    {
        bool collision = check_object_collides_other_object(hero,Sides::right,level->get_walls());
        if(!collision) hero->move(hero->Direction::right);
        hero_direction =  hero->Direction::right;
    }
    if(kb::isKeyPressed(kb::W))
    {
        bool collision = check_object_collides_other_object(hero,Sides::top,level->get_walls());
        if(!collision)hero->move(hero->Direction::up);
    }
    if(kb::isKeyPressed(kb::S))
    {
        bool collision = check_object_collides_other_object(hero,Sides::bottom,level->get_walls());
        if(!collision) hero->move(hero->Direction::down);
    }
    if(kb::isKeyPressed(kb::Num1))
    {
        hero->choose_new_gun(0);
    }
    if(kb::isKeyPressed(kb::Num2))
    {
        hero->choose_new_gun(1);
    }
    if(kb::isKeyPressed(kb::Num3))
    {
        hero->choose_new_gun(2);
    }
    if(kb::isKeyPressed(kb::Space) && !key_is_pressed)
    {
        hero->shoot(hero_bullets);
        key_is_pressed = true;
    }
    if(!kb::isKeyPressed(kb::Space))
    {
        key_is_pressed = false;
    }
    
    hero->animate(hero_direction);
}
void Game::draw_game()
{
    level->draw(window);
    window->draw(hero->returnSprite());
    draw_bullets();
}
void Game::run_game()
{
    load_level();
    
    check_game_key_pressing();
    check_hero_takes_gun();
    check_bullets_collided_walls();
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
bool Game::check_object_collides_other_object(GameObject* object, int side,vector<GameObject*>& objects)
{
   CollisionCounter counter = collision_checker.count_object_collisions(hero,objects);
   
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
bool Game::check_hero_takes_gun()
{
    vector<GameObject*> guns = level->get_usable_objects();
    
    for(size_t i = 0; i<guns.size();++i)
    {
        string type = guns[i]->get_type();
        
        // level returns usable objects of ANY kind
        // and there are other objects,except guns
        // so it's needed to check 
        bool is_gun = type == "pistol" || type == "cumgun" || type == "brutgun";
        
        bool collision = collision_checker.object_collides(hero,guns[i]);
        if(is_gun && collision)
        {
            hero->set_ammo(1,type);
            
            //delete taken gun
            level->get_usable_objects().erase(level->get_usable_objects().begin()+i);
        }
    }
}
void Game::draw_bullets()
{
    for(size_t bullet = 0; bullet<hero_bullets.size();++bullet)
    {
        hero_bullets[bullet]->move();
        window->draw(hero_bullets[bullet]->returnSprite());
    }
}

void Game::check_bullets_collided_walls()
{
    vector<GameObject*> walls = level->get_walls();
    for(size_t wall = 0; wall<walls.size();++wall)
    {
        for(size_t bullet = 0; bullet<hero_bullets.size();++bullet)
        {
            bool collision = collision_checker.object_collides(hero_bullets[bullet],walls[wall]);
            if(collision)
            {
                hero_bullets.erase(hero_bullets.begin()+bullet);
            }
        }
    }
}











