#include "GraphicalObject.h"
void GraphicalObject::set_drawable(bool flag)
{
    drawable = flag;
}
bool GraphicalObject::is_drawable()
{
    return drawable;
}
void GraphicalObject::set_rotation_angle(float angle)
{
	gobject_spr.setRotation(angle);
}
float GraphicalObject::get_rotation_angle()
{
	return gobject_spr.getRotation();
}


void GraphicalObject::set_position(float x, float y)
{
    Vector2f position;

    position.x = x;
    position.y = y;

	gobject_spr.setPosition(position);
}
void GraphicalObject::set_position(Vector2f position)
{
	gobject_spr.setPosition(position);
}


Vector2f GraphicalObject::get_center()
{
    Vector2f position = get_position();
	Vector2f center;

	center.x = (gobject_spr.getTextureRect().width + position.x)/2;
	center.y = (gobject_spr.getTextureRect().height + position.y)/2;

	return center;
}

Vector2f GraphicalObject::get_position()
{
    return gobject_spr.getPosition();
}


Sprite GraphicalObject::returnSprite()
{
	return gobject_spr;
}

void GraphicalObject::set_image(string img)
{
    image_path = img;
	gobject_img.loadFromFile(img);
	//gobject_img.createMaskFromColor(Color::White); every object is white :) in this game
	gobject_textr.loadFromImage(gobject_img);
	gobject_spr.setTexture(gobject_textr);

}
string GraphicalObject::get_image_path()
{
	return image_path;
}

GraphicalObject::GraphicalObject()
{

}
GraphicalObject::GraphicalObject(GraphicalSettings settings)
{
    set_image(settings.image);
    set_position(settings.position);
    set_drawable(settings.drawable);
    set_rotation_angle(settings.rotation);
    set_texture_rect(settings.texture_rect);

}
GraphicalObject::~GraphicalObject()
{
}

void GraphicalObject::set_texture_rect(const IntRect& rect)
{
    gobject_spr.setTextureRect(rect);
}
IntRect GraphicalObject::get_texture_rect()
{
    return gobject_spr.getTextureRect();
}
GraphicalSettings GraphicalObject::get_graphical_settings()
{
    GraphicalSettings settings;
    settings.drawable = drawable;
    settings.image = image_path;
    settings.position = get_position();
    settings.rotation = get_rotation_angle();
    settings.texture_rect = get_texture_rect();
    return settings;

}
















