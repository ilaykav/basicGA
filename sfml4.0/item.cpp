#include "item.h"

item::item() {
//	body = new sf::CircleShape;
	this->radius = (rand() % int(int(plant_maxRadius) - plant_minRadius)) + plant_minRadius;
	this->health = plant_healthRatio * this->radius;
	this->body.setRadius(this->radius);
	this->body.setFillColor(this->color);
	this->x = (rand() % int(int(w_width)));
	this->y = (rand() % int(int(w_height)));
	this->body.setPosition(x, y);
}

void item::draw(sf::RenderWindow& win)
{
	win.draw(this->body);
}

void item::set_color(sf::Color c){
	this->body.setFillColor(c);
}

int item::get_x() { return this->x; }
int item::get_y() { return this->y; }
float item::get_r() { return this->radius; }


item::item(float radius = 5, unsigned int = 7)
{
	this->radius = radius;
	this->health = health;
	this->body.setRadius(radius);
	this->body.setFillColor(this->color);
	this->x = (rand() % int(int(w_width)));
	this->y = (rand() % int(int(w_height)));
	this->body.setPosition(x, y);
}

item::item(float radius)
{
	this->radius = radius;
	this->health = plant_healthRatio * radius;
	this->body.setRadius(radius);
	this->body.setFillColor(this->color);
	this->x = (rand() % int(int(w_width)));
	this->y = (rand() % int(int(w_height)));
	this->body.setPosition(x, y);
}

item::~item() {
	//delete body;	
}