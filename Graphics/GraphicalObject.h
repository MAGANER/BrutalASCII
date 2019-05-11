/*
  GraphicalObject is base class for
  Object class.
  This is drawable part of Object,
  that is used to draw objects.
*/
#pragma once

#include"SFML/Graphics.hpp"
#include<string>
using namespace sf;
using namespace std;


struct GraphicalSettings
{
    Vector2f position;
    string image;
    bool drawable;
    float rotation;
    IntRect texture_rect;

    void operator=(GraphicalSettings settings)
    {
        position = settings.position;
        image = settings.image;
        drawable = settings.drawable;
        rotation = settings.rotation;
        texture_rect = settings.texture_rect;
    }
};

class GraphicalObject
{
private:
    string image_path;
	Image gobject_img;
	Texture gobject_textr;

	bool drawable;
protected:
    Sprite gobject_spr;
public:
    void set_drawable(bool flag);
    bool is_drawable();

	void set_rotation_angle(float angle);
	float get_rotation_angle();

	void set_position(float x, float y);
    void set_position(Vector2f position);

    void set_texture_rect(const IntRect& rect);
    IntRect get_texture_rect();

    Vector2f get_position();
	Vector2f get_center();

	GraphicalSettings get_graphical_settings();


	void set_image(string img);
	string get_image_path();

	Sprite returnSprite();

	GraphicalObject();
	GraphicalObject(GraphicalSettings settings);

	virtual ~GraphicalObject();
};


