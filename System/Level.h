#ifndef LEVEL_H
#define LEVEL_H

#include<fstream>
#include<iostream>
#include"json.hpp"
#include<vector>
#include"Objects/GameObject.h"
using namespace std;
using nlohmann::json;


class Level
{
protected:
    json data;
    string level_path;
private:
	GraphicalSettings load_graphical_data(int object_counter);
	GameSettings  load_game_data(int object_counter);
	PhysicalSettings load_physical_body_data(int object_counter);
	
	vector<GameObject*> objects;
	
public:
    Level();
    ~Level();

	string get_level_path();
	virtual void load(string level_path);
};

#endif // LEVEL_H
