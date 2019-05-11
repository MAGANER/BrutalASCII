#include "Level.h"
Level::Level()
{
}

Level::~Level()
{

}
string Level::get_level_path()
{
    return level_path;
}
PhysicalSettings Level::load_physical_body_data(int object_counter)
{
	PhysicalSettings settings;

	float x = data["world"][to_string(object_counter)].at(0);
	float y = data["world"][to_string(object_counter)].at(1);
	settings.main_vertex = Vector2f(x, y);
	//settings.position = Vector2f(x, y);

	float width = data["world"][to_string(object_counter)][6].at(0);
	float height = data["world"][to_string(object_counter)][6].at(1);
	settings.width = width;
	settings.height = height;

	return settings;
}
GraphicalSettings Level::load_graphical_data(int object_counter)
{
	GraphicalSettings graph_settings;

	float x = data["world"][to_string(object_counter)].at(0);
	float y = data["world"][to_string(object_counter)].at(1);
	string image = data["world"][to_string(object_counter)].at(2);
	string type = data["world"][to_string(object_counter)].at(3);
	float rotation = data["world"][to_string(object_counter)].at(4);
	bool  drawable = data["world"][to_string(object_counter)].at(5);
	float width = data["world"][to_string(object_counter)][6].at(0);
	float height = data["world"][to_string(object_counter)][6].at(1);
	float txtur_rect_x = data["world"][to_string(object_counter)][6].at(2);
	float txtur_rect_y = data["world"][to_string(object_counter)][6].at(3);


	IntRect texture_rect = IntRect(txtur_rect_x, txtur_rect_y, width, height);

	graph_settings.texture_rect = texture_rect;
	graph_settings.drawable = drawable;
	graph_settings.image = image;
	graph_settings.position = Vector2f(x, y);
	graph_settings.rotation = rotation;

	return graph_settings;
}
GameSettings Level::load_game_data(int object_counter)
{
	GameSettings game_settings;

	int id = object_counter;
	string type = data["world"][to_string(object_counter)].at(3);

	game_settings.id = id;
	game_settings.type = type;

	return game_settings;
}

void Level::load(string level_path)
{
	ifstream file(level_path);
	if (file.fail())
	{
		cout << "error:level can not be loaded!" << endl;
		exit(-1);
	}
	this->level_path = level_path;
	file >> data;
	file.close();


	int object_counter = 0;
	bool loading = true;
	while (loading)
	{
		if (!data["world"][to_string(object_counter)].empty())
		{
			GraphicalSettings graph_settings = load_graphical_data(object_counter);
			GameSettings game_settings = load_game_data(object_counter);
			PhysicalSettings phys_settings = load_physical_body_data(object_counter);
			
			GameObject* object = new GameObject(graph_settings,phys_settings,game_settings);
			objects.push_back(object);
			
			++object_counter;
		}
		else
		{
			cout << "level is loaded" << endl;
			loading = false;
		}
	}
}


vector<GameObject*>& Level::get_ground()
{
	return ground;
}









