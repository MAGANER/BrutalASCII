#include "Game.h"

Game::Game()
{
	window = new RenderWindow(VideoMode(720, 640), "BrutalDeath");
	window->setFramerateLimit(60); // to optimize CPU
	
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
	
	phys_settings->width = 70;
	phys_settings->height = 80;
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
	
	space_is_pressed = false;
	
	lever_counter = 0; //hero must activate 3 to activate portal 
                       //and then teleport to next level
                       
                       
    S_can_be_pressed = false;
    W_can_be_pressed = false;
    D_can_be_pressed = false;
    A_can_be_pressed = false;
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
    //check SFML events or window ones
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
    //run whole app, relating to current state
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
    CollisionCounter counter = collision_checker.count_object_collisions(hero,level->get_walls());
    
    //if there is no bottom side collisions, hero can go down
    if(counter.bottom_side_collisions == 0)
    {
        S_can_be_pressed = true;
    }
    else if(counter.bottom_side_collisions == 1 && (counter.right_side_collisions > 1 ||
                                                    counter.left_side_collisions  > 1) )
    {
        //if hero is lefter/righter than object, than he can go down
        S_can_be_pressed = true;
    }
    
    //if there is no top side collisions, hero can go up
    if(counter.top_side_collisions == 0)
    {
        W_can_be_pressed = true;
    }
    else if(counter.top_side_collisions == 1 && (counter.right_side_collisions    > 1 ||
                                                    counter.left_side_collisions  > 1)  )
    {
        //if hero is lefter/righter than object, than he can go up
        W_can_be_pressed = true;
    }
    
    //if there is not right side collisions, hero can go right
    if(counter.right_side_collisions == 0)
    {
        D_can_be_pressed = true;
    }
    else if(counter.right_side_collisions == 1 && (counter.bottom_side_collisions > 1 ||
                                                   counter.top_side_collisions    > 1)  )
    {
        //if hero stands on objects, than he can go right
        D_can_be_pressed = true;
    }

    //if there is not left side collisions, hero can go left
    if(counter.left_side_collisions == 0)
    {
        A_can_be_pressed = true;
    }
    else if(counter.left_side_collisions == 1 && (counter.bottom_side_collisions > 1 ||
                                                  counter.top_side_collisions    > 1)  )
    {
        //if hero stands on objects, than he can go left
        A_can_be_pressed = true;
    }
    
    cout<<"bottom:"<<counter.bottom_side_collisions << endl
        <<"right:" <<counter.right_side_collisions  << endl
        <<"left:"  <<counter.left_side_collisions   << endl
        <<"top:"   <<counter.top_side_collisions    << endl; 
    
    
    //check keys to move hero
    int direction = hero->get_direction();
    
    if(kb::isKeyPressed(kb::A) && A_can_be_pressed)
    {
        /*
          S can not be pressed, because
          when you press A and then S
          hero walks trough the wall down
        */
        S_can_be_pressed = false;
        
        //the same reason for S
        W_can_be_pressed = false;
        
        hero->set_direction(Direction::left);
        
        //just look at console output to understand the sense of hack
        //not the best way, but IT IS FUCKING WORKING
        if(counter.left_side_collisions == 0)
        {
            hero->move(direction,true);
        }
        else if(counter.left_side_collisions == 1 && counter.bottom_side_collisions > 1)
        {
            hero->move(direction,true);
        }
        else if(counter.right_side_collisions == 1 && counter.top_side_collisions > 1)
        {
            hero->move(direction,true);
        }
    }
    if(kb::isKeyPressed(kb::D) && D_can_be_pressed)
    {
        /*
          S can not be pressed, because
          when you press D and then S
          hero walks trough the wall down
        */
        S_can_be_pressed = false;
        
        //the same reason for S
        W_can_be_pressed = false;
        
        hero->set_direction(Direction::right);
        
        //just look at console output to understand the sense of hack
        //not the best way, but IT IS FUCKING WORKING
        if(counter.right_side_collisions == 0)
        {
            hero->move(direction,true);
        }
        else if(counter.right_side_collisions == 1 && counter.bottom_side_collisions > 1)
        {
            hero->move(direction,true);
        }
        else if(counter.right_side_collisions == 1 && counter.top_side_collisions > 1)
        {
            hero->move(direction,true);
        }


    }
    if(kb::isKeyPressed(kb::W) && W_can_be_pressed)
    {
        /*
          S can be pressed, because hero doesn't move down
          and so there is not bottom side collisions
        */
        S_can_be_pressed = true;
        /*
         D can not be pressed, because 
         if you press S and then D
            hero walks through the wall
        */
        D_can_be_pressed = false;
        
        //the same reason for D
        A_can_be_pressed = false;
        
        hero->set_direction(Direction::up);
        
        //just look at console output to understand the sense of hack
        //not the best way, but IT IS FUCKING WORKING
        if(counter.top_side_collisions == 0)
        {
            hero->move(direction,true);
        }    

        else if(counter.top_side_collisions == 1 && counter.right_side_collisions > 1)
        {
            hero->move(direction,true);
        }
        else if(counter.top_side_collisions == 1 && counter.left_side_collisions  > 1)
        {
            hero->move(direction,true);
        }
    }
    if(kb::isKeyPressed(kb::S) && S_can_be_pressed)
    {
        /*
          W can be pressed, because hero doesn't move up
          and so there is not top side collisions
        */
        W_can_be_pressed = true;
        
        /*
         D can not be pressed, because 
         if you press S and then D
            hero walks through the wall
        */
        D_can_be_pressed = false;
        
        //the same reason for D
        A_can_be_pressed = false;
        
        hero->set_direction(Direction::down);

        //just look at console output to understand the sense of hack
        //not the best way, but IT IS FUCKING WORKING
        if(counter.bottom_side_collisions == 0)
        {
            hero->move(direction,true);
        }
        else if(counter.bottom_side_collisions == 1 && counter.right_side_collisions > 1)
        {
            hero->move(direction,true);
        }
        else if(counter.bottom_side_collisions == 1 && counter.left_side_collisions  > 1)
        {
            hero->move(direction,true);
        }
    }
    
    //check keys to choose gun
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
    if(kb::isKeyPressed(kb::Num5))
    {
        hero->choose_new_gun(4);
    }
    
    //check key to shoot
    if(kb::isKeyPressed(kb::Space) && !space_is_pressed)
    {
        hero->shoot(hero_bullets);
        space_is_pressed = true;
    }
    if(!kb::isKeyPressed(kb::Space))
    {
        space_is_pressed = false;
    }
    
    hero->animate();
}
void Game::draw_game()
{
    // camera always stays at the center
    camera->setCenter(hero->get_position());
    
    
    level->draw_level(window);
    window->draw(hero->returnSprite());
    
    draw_bullets(hero_bullets);
    draw_bullets(turrells_bullets);
    draw_bullets(monsters_bullets);
    
    //panel doesn't move, cos it must has static position
    //the same for level
    window->setView(window->getDefaultView());
    parameters_panel->draw(window);
}
void Game::run_game()
{
    load_level();
    
    //check hero's taken actions
    check_game_key_pressing();
    check_hero_takes_gun();
    check_hero_died();
    check_hero_teleports_to_next_level();
    check_hero_collided_thorns();
    check_hero_activated_lever();
    check_hero_collided_bullets(monsters_bullets);
    check_hero_collided_bullets(turrells_bullets);
    check_hero_collided_bullets(hero_bullets);
    check_hero_takes_key();
    check_hero_opens_door();
    
    check_bullets_collided_walls(hero_bullets);
    check_bullets_collided_walls(turrells_bullets);
    check_bullets_collided_walls(monsters_bullets);
    
    check_bullets_shot_down_monsters();
    check_suicide_boys_collided_walls();
    check_suicide_boys_collided_hero();
    
    make_turrells_shoot();
    make_monsters_live();
    
    /// update count of hero's ammo and health counter
    parameters_panel->update(hero->get_ammo(),hero->get_health(),hero->get_keys());
    
    window->setView(*camera);
    window->clear();
    draw_game();
    window->display();
    
}

void Game::run_game_over()
{
    check_game_over_key_pressing();
    
    /// there is nothing hard, it only shows that hero died
    window->clear();
    window->setView(window->getDefaultView());
    game_over->draw(window);
    window->display();
}

void Game::check_game_over_key_pressing()
{
    /// when hero presses space game starts again
    if(Keyboard::isKeyPressed(Keyboard::Space))
    {
        current_state = GameState::game;
        hero->set_health(10);
    }
}


void Game::draw_bullets(vector<Bullet*>& bullets)
{
    for(size_t bullet = 0; bullet<bullets.size();++bullet)
    {
        bullets[bullet]->move();
        window->draw(bullets[bullet]->returnSprite());
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
   
   string object_type = object->get_type();
   switch(direction)
   {
   case Direction::left:
       return counter.left_side_collisions>0;
       break;
   case Direction::right:
       return counter.right_side_collisions>0;
       break; 
   case Direction::up:
       
       //check it,cos monster sticks to walls
       if(object_type == "smob")
       {
           if(counter.right_side_collisions==0 && counter.left_side_collisions==0)
           {
               return counter.top_side_collisions>0;
           }
       }
       else
       {
           return counter.top_side_collisions>0;
       }
       break;
   case Direction::down:
       if(object_type == "smob")
       {
           if(counter.right_side_collisions==0 && counter.left_side_collisions==0)
           {
               return counter.bottom_side_collisions>0;
           }
       }
       else
       {
           return counter.bottom_side_collisions>0;
       }
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
                      type == "doublegun" ||
                      type == "madgun";
        
        bool collision = collision_checker.object_collides(hero,guns[i]);
        if(is_gun && collision)
        {
            hero->set_ammo(1,type);
            
            //delete taken gun
            level->get_usable_objects().erase(level->get_usable_objects().begin()+i);
        }
    }
}
void Game::check_bullets_collided_walls(vector<Bullet*>& bullets)
{
    /// destroy bullet, if it collides wall
    
    vector<GameObject*> walls = level->get_walls();
    for(size_t wall = 0; wall<walls.size();++wall)
    {
        for(size_t bullet = 0; bullet<bullets.size();++bullet)
        {
            bool collision = collision_checker.object_collides(bullets[bullet],walls[wall]);
            if(collision && walls[wall]->get_type() == "wall")
            {
                bullets.erase(bullets.begin()+bullet);
            }
            else if(collision && walls[wall]->get_type() == "twall") // bullet's type is twall
            {
                //bullet changes its direction
                int direction = bullets[bullet]->get_direction();
                Vector2f bullet_pos = bullets[bullet]->get_position();
                switch(direction)
                {
                case Direction::left:
                    bullets[bullet]->set_position(bullet_pos.x + 30.0f,bullet_pos.y);
                    bullets[bullet]->set_direction(Direction::right);
                    break;
                case Direction::right:
                    bullets[bullet]->set_position(bullet_pos.x - 30.0f,bullet_pos.y);
                    bullets[bullet]->set_direction(Direction::left);
                    break;
                case Direction::up:
                    bullets[bullet]->set_position(bullet_pos.x,bullet_pos.y+30.0f);
                    bullets[bullet]->set_direction(Direction::down);
                    break;
                case Direction::down:
                    bullets[bullet]->set_position(bullet_pos.x,bullet_pos.y-30.0f);
                    bullets[bullet]->set_direction(Direction::up);
                    break;
                }
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
        lever_counter = 0;
        
        hero->destroy_ammo(); // cos when hero dies he must lost all of his ammo
        hero->choose_new_gun(-1); // no gun, cos he lost all ammo
    }
}



void Game::check_hero_teleports_to_next_level()
{
    //if hero collided portal and he activated 3 levers, he can teleport
    GameObject* portal = level->get_trigger("level_portal");
    CollisionCounter counter = collision_checker.count_object_collisions(hero,portal);
    int collision = counter.get_collisions_summ();

    if(collision > 0 && lever_counter == 3)
    {
        level->clear();
        hero_bullets.clear();
        turrells_bullets.clear();
        
        level_counter++;
        level_is_loaded = false;
        lever_counter = 0;
    }
}
void Game::check_hero_collided_thorns()
{
    //if hero collides thorns, than it kills him
    
    vector<GameObject*> thorns = level->get_thorns();
    
    auto trigger = thorns.begin();
    while(trigger != thorns.end())
    {
        if(collision_checker.object_collides(hero,*trigger))
        {
            cout<<(*trigger)->get_type()<<endl;
            hero->set_health(hero->get_health()-1);
            break;
        }
        
        ++trigger;
    }
    
}
void Game::check_hero_activated_lever()
{
    //if he collides lever, it became activated
    vector<Lever*> levers = level->get_levers();
    auto lever = levers.begin();
    while(lever != levers.end())
    {
        GameObject* converted_lever = static_cast<GameObject*>(*lever);
        
        bool collision = collision_checker.object_collides(hero,converted_lever);
        bool lever_is_activated = (*lever)->is_activated();
        if(collision && !lever_is_activated)
        {
            lever_counter++;
            (*lever)->set_activated_state(true);
            break;
        }
        ++lever;
    }
}
void Game::check_hero_collided_bullets(vector<Bullet*>& bullets)
{
        for(size_t bullet = 0; bullet<bullets.size();++bullet)
        {
            bool collision = collision_checker.object_collides(hero,bullets[bullet]);
            if(collision)
            {
                bullets.erase(bullets.begin()+bullet);
                
                hero->set_health(hero->get_health()-1);
            }
        }
}
void Game::check_hero_takes_key()
{
    //when hero takes key, his key counter increases 
    vector<GameObject*> usable_objects = level->get_usable_objects();
    
    for(size_t i = 0;i<usable_objects.size();++i)
    {
        string type = usable_objects[i]->get_type();
        
        bool collision = collision_checker.object_collides(hero,usable_objects[i]);
        if(type == "key" && collision)
        {
            level->get_usable_objects().erase(level->get_usable_objects().begin() + i);
            hero->set_keys(hero->get_keys()+1);
        }
    }
}
void Game::check_hero_opens_door()
{
    //when hero opens door, door wall becomes destroyed
    //but to do that, hero needs at least 1 key
    vector<GameObject*> walls = level->get_triggers();
    for(size_t i = 0;i<walls.size();++i)
    {
        string type = walls[i]->get_type();
        if(type == "door")
        {
            bool collision = collision_checker.object_collides(hero,walls[i]);
            bool has_hero_got_enough_keys = hero->get_keys() > 0;
            if(has_hero_got_enough_keys && collision)
            {
                hero->set_keys(hero->get_keys()-1);
                level->get_triggers().erase(level->get_triggers().begin()+i);
            }
        }
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
void Game::make_turrells_shoot()
{
    //they always shoot
    vector<Turrell*> turrells = level->get_turrels();
    auto turrell = turrells.begin();
    while(turrell != turrells.end())
    {
        (*turrell)->shoot(turrells_bullets);
        ++turrell;
    }
}
void Game::make_monsters_live()
{
    vector<Monster*> monsters = level->get_monsters();
    for(size_t i = 0; i<monsters.size();++i)
    {
        bool collision = check_object_collides_other_object(monsters[i],monsters[i]->get_direction(),level->get_walls());
        monsters[i]->go(collision);
        
        Vector2f hero_pos = hero->get_position();
        monsters[i]->search_target(hero_pos);
        
        monsters[i]->attack();
    }
    
    vector<BaseShooterMonster*> smonsters = level->get_shooting_monsters();
    for(size_t i = 0; i<smonsters.size();++i)
    {
        
        //search target
        Vector2f hero_pos = hero->get_position();
        smonsters[i]->search_target(hero_pos);
        
        // see target, if there is no wall before one
        bool see_no_walls = !smonsters[i]->is_any_wall_between_itself_and_target(level->get_walls(),hero_pos);
        bool see_target = smonsters[i]->does_see_target();
        
        bool able_to_attack = see_target && see_no_walls;
        if(able_to_attack)
        {
            smonsters[i]->attack(monsters_bullets);
        }
        
        
        smonsters[i]->avoid_bullet(hero_bullets);
        
        bool collision = check_object_collides_other_object(smonsters[i],
                                                            smonsters[i]->get_direction(),
                                                            level->get_walls());
        
        bool cannot_go = !smonsters[i]->is_any_wall_between_itself_and_target(level->get_walls(),hero_pos) &&
                         smonsters[i]->does_see_target();
        if(!cannot_go)
        {
            smonsters[i]->go(collision);
        }
        // fix bug, when monster sticks to the wall
        int monster_direction = smonsters[i]->get_direction();
        if(collision && monster_direction == Direction::down)
        {
            Vector2f pos = smonsters[i]->get_position();
            smonsters[i]->set_position(pos.x,pos.y - 20.0f);
        }
        if(collision && monster_direction == Direction::up)
        {
            Vector2f pos = smonsters[i]->get_position();
            smonsters[i]->set_position(pos.x,pos.y + 20.0f);
        }
    }
}
void Game::check_bullets_shot_down_monsters()
{
    //not shooting monsters
    vector<Monster*> monsters = level->get_monsters();
    for(size_t i = 0; i<monsters.size();++i)
    {
        for(size_t n = 0;n<hero_bullets.size();++n)
        {
            bool collision = collision_checker.object_collides(monsters[i],hero_bullets[n]);
            if(collision)
            {
                int old_monster_health = level->get_monsters()[i]->get_health();
                int bullet_damage = hero_bullets[n]->get_damage();
                
                level->get_monsters()[i]->set_health(old_monster_health - bullet_damage);
                hero_bullets.erase(hero_bullets.begin() + n);
            }
        }
    }
    for(size_t i = 0;i<monsters.size();++i)
    {
        if(monsters[i]->is_dead())
        {
            level->get_monsters().erase(level->get_monsters().begin() + i);
        }
    }
    
    
    //shooting monsters
    vector<BaseShooterMonster*> smonsters = level->get_shooting_monsters();
    for(size_t i = 0; i<smonsters.size();++i)
    {
        for(size_t n = 0;n<hero_bullets.size();++n)
        {
            bool collision = collision_checker.object_collides(smonsters[i],hero_bullets[n]);
            if(collision)
            {
                int old_monster_health = level->get_shooting_monsters()[i]->get_health();
                int bullet_damage = hero_bullets[n]->get_damage();
                
                level->get_shooting_monsters()[i]->set_health(old_monster_health - bullet_damage);
                hero_bullets.erase(hero_bullets.begin() + n);
            }
        }
    }

    for(size_t y = 0;y<level->get_shooting_monsters().size();++y)
    {
        if(level->get_shooting_monsters()[y]->is_dead())
        {
            level->get_shooting_monsters().erase(level->get_shooting_monsters().begin() + y);
        }
    }
    

}
void Game::check_suicide_boys_collided_walls()
{
    vector<GameObject*> walls = level->get_walls();
    for(size_t i = 0;i<walls.size();++i)
    {
        //directly get monsters vector
        //cos this vector can be changed at any time
        for(size_t n = 0; n<level->get_monsters().size();++n)
        {
            bool collision = collision_checker.object_collides(walls[i],level->get_monsters()[n]);
            if(collision && level->get_monsters()[n]->does_see_target())
            {
                auto monsters_begin = level->get_monsters().begin();
                level->get_monsters().erase(monsters_begin+n);
            }
        }
        
    }
}
void Game::check_suicide_boys_collided_hero()
{
    for(size_t n = 0; n<level->get_monsters().size();++n)
    {
        bool collision = collision_checker.object_collides(level->get_monsters()[n],hero);
        if(collision)
        {
            auto monsters_begin = level->get_monsters().begin();
            level->get_monsters().erase(monsters_begin+n);
            
            int old_health = hero->get_health();
            hero->set_health(old_health-2);
        }
    }
}

bool Game::is_pressing_only_one()
{
    typedef Keyboard kb;
    bool A = kb::isKeyPressed(kb::A);
    bool S = kb::isKeyPressed(kb::S);
    bool D = kb::isKeyPressed(kb::D);
    bool W = kb::isKeyPressed(kb::W);
    
    bool first_case  =  A && !S && !D && !W;
    bool second_case = !A && S  && !D && !W;
    bool third_case  = !A && !S &&  D && !W;
    bool fourth_case = !A && !S && !D &&  W;
    
    return first_case || 
           second_case||
           third_case ||
           fourth_case; 
}




















