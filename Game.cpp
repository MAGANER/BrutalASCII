#include "Game.h"

Game::Game()
{
	window = new RenderWindow(VideoMode(720, 640), "BrutalDeath");
	window->setFramerateLimit(60); // to optimize CPU
	//window->setVerticalSyncEnabled(true);
	
	menu = new MainMenu();
	game_over = new GameOverMenu();
	parameters_panel = new Parameters();
	level = new myLevel();
	
	camera = new View();
	camera->setSize(400.0f,420.0f);
	camera->zoom(2);
	
	
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

	
	menu_is_deleted = false;
	current_state = GameState::main_menu;// game starts at main menu
	level_is_loaded = false; // at the game beginning level isn't loaded
	level_counter = 0;   // game starts from 0 level
	
	key_is_pressed = false;
}
Game::~Game()
{
	delete window;
	delete game_over;
	delete parameters_panel;
	delete level;
	delete camera;
	delete hero;
	
	// if user runs game and then close program at main menu
	// main menu must be deleted
	// if user played game, menu is not deleted
	delete_menu();
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
		switch (current_state)
		{
		case GameState::main_menu:
			run_main_menu();
			break;
		case GameState::game:
		    delete_menu();
			run_game();
			break;
		case GameState::death:
			run_game_over();
			break;
		}
	}
}
void Game::check_main_menu_key_pressing()
{
    //start game
    if(Keyboard::isKeyPressed(Keyboard::Space))
    {
        current_state = GameState::game;
    }
    
    //quit game
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window->close();
    }
}
void Game::run_main_menu()
{
    check_main_menu_key_pressing();
    
    window->clear();
    menu->draw(window);
    window->display();
}


void Game::check_game_key_pressing()
{
    typedef Keyboard kb;     
    
    if(kb::isKeyPressed(kb::A))
    {
        bool collision = check_object_collides_other_object(hero,Direction::left,level->get_walls());
        if(!collision) hero->move(Direction::left);
    }
    if(kb::isKeyPressed(kb::D))
    {
        bool collision = check_object_collides_other_object(hero,Direction::right,level->get_walls());
        if(!collision) hero->move(Direction::right);
    }
    if(kb::isKeyPressed(kb::W))
    {
        bool collision = check_object_collides_other_object(hero,Direction::up,level->get_walls());
        if(!collision)hero->move(Direction::up);
    }
    if(kb::isKeyPressed(kb::S))
    {
        bool collision = check_object_collides_other_object(hero,Direction::down,level->get_walls());
        if(!collision) hero->move(Direction::down);
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
    if(kb::isKeyPressed(kb::Num4))
    {
        hero->choose_new_gun(3);
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
    
    hero->animate();
}
void Game::draw_game()
{
    // camera always stays at the center
    camera->setCenter(hero->get_position());
    
    level->draw(window);
    window->draw(hero->returnSprite());
    draw_bullets();
    
    //panel doesn't move, cos it must has static position
    window->setView(window->getDefaultView());
    parameters_panel->draw(window);
}
void Game::run_game()
{
    load_level();
    
    check_game_key_pressing();
    check_hero_takes_gun();
    check_bullets_collided_walls();
    check_hero_died();
    check_hero_teleports_to_next_level();
    
    /// update count of hero's ammo and health counter
    parameters_panel->update(hero->get_ammo(),hero->get_health());
    
    window->setView(*camera);
    window->clear();
    draw_game();
    window->display();
    
}

void Game::run_game_over()
{
    
    check_game_over_key_pressing();
    
    /// there is nothing hard, it only shows that hero died
    window->setView(window->getDefaultView());
    game_over->draw(window);
}

void Game::check_game_over_key_pressing()
{
    /// when hero presses space game starts again
    /// 
    if(Keyboard::isKeyPressed(Keyboard::Space))
    {
        current_state = GameState::game;
        hero->set_health(5);
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

void Game::load_level()
{
    /// load level if it isn't loaded already
    
    if(!level_is_loaded)
    {
        level->load("levels/"+to_string(level_counter)+".json");
        hero->set_position(level->get_hero_start());
        level_is_loaded = true;
    }
}


bool Game::check_object_collides_other_object(GameObject* object, int direction,vector<GameObject*>& objects)
{
   CollisionCounter counter = collision_checker.count_object_collisions(object,objects);
   
   switch(direction)
   {
   case Direction::left:
       return counter.left_side_collisions>0;
       break;
   case Direction::right:
       return counter.right_side_collisions>0;
       break; 
   case Direction::up:
       return counter.top_side_collisions>0;
       break;
   case Direction::down:
       return counter.bottom_side_collisions>0;
       break;
   }
}
bool Game::check_hero_takes_gun()
{
    ///when hero takes gun his ammo increases
    ///and then gun must be deleted
    
    vector<GameObject*> guns = level->get_usable_objects();
    
    for(size_t i = 0; i<guns.size();++i)
    {
        string type = guns[i]->get_type();
        
        // level returns usable objects of ANY kind
        // and there are other objects,except guns
        // so it's needed to check 
        bool is_gun = type == "pistol" || 
                      type == "cumgun" || 
                      type == "brutgun"||
                      type == "doublegun";
        
        bool collision = collision_checker.object_collides(hero,guns[i]);
        if(is_gun && collision)
        {
            hero->set_ammo(1,type);
            
            //delete taken gun
            level->get_usable_objects().erase(level->get_usable_objects().begin()+i);
        }
    }
}
void Game::check_bullets_collided_walls()
{
    /// destroy bullet, if it collides wall
    
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
void Game::check_hero_died()
{
    /// when hero dies, state of program switches to death state
    /// then game over screen is shown
    
    if(hero->get_health() <= 0)
    {
        current_state = GameState::death;
        
        // level will be begun from the start
        // so clear level and reload it
        level_is_loaded = false;
        level->clear();
    }
}



void Game::check_hero_teleports_to_next_level()
{
    GameObject* portal = level->get_trigger("level_portal");
    CollisionCounter counter = collision_checker.count_object_collisions(hero,portal);
    int collision = counter.get_collisions_summ();
    
    if(collision > 0)
    {
        level->clear();
        level_counter++;
        level_is_loaded = false;
    }
}


void Game::delete_menu()
{
   if(!menu_is_deleted)
   {
       delete menu;
       menu_is_deleted = true;
   }
    
}



