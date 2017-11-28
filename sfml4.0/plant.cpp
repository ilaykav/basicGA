
#include "plant.h"


plant::plant(){
	this->body.setFillColor(color);
}

void plant::set_rand_position(int min_x, int max_x, int min_y, int max_y)
{
	this->x = (rand() % int(int(max_x)+min_x));
	this->y = (rand() % int(int(max_y))+min_y);
	this->body.setPosition(x, y);
}

void plant::update_x(int dis) {
	this->x += dis;
	this->body.setPosition(x, y);
}

void plant::update_y(int dis) {
	this->y += dis;
	this->body.setPosition(x, y);
}

void plant::add_r(int add)
{
	this->radius += add;
}

void plant::dec_health(int dec_by)
{
	/*if (this->get_health() < 70)
	{
		this->color = sf::Color::Black;
		this->body.setFillColor(color);
		this->health = -1;
	}*/
	this->health -= dec_by;
	this->radius -= 10;
	this->x += 10;
	this->y += 10;
	this->body.setRadius(this->radius);
	this->body.setPosition(x, y);
	
}

int plant::get_health()
{
	return this->health;
}

plant::~plant() {
}