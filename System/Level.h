#ifndef LEVEL_H
#define LEVEL_H

#include<fstream>
#include<iostream>
#include"json.hpp"
#include<vector>
#include"Objects/GameObject.h"
using namespace std;
using nlohmann::json;

/*
 basic level class, that loads all objects
 from json file into one vector
*/
class Level
{
protected:
    json data;
    string level_path;
    
    vector<GameObject*> objects;
private:
	GraphicalSettings load_graphical_data(int object_counter);
	GameSettings  load_game_data(int object_counter);
	PhysicalSettings load_physical_body_data(int object_counter);
	

	
public:
    Level();
    virtual ~Level();

	string get_level_path();
	virtual void load(string level_path);
};

#endif // LEVEL_H
