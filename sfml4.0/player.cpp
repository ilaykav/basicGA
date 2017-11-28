#include "player.h"

void player::update_body()
{
	this->body.setPosition(this->x, this->y);
}

void player::update_x(int dir)
{
	this->x += speed*dir;
	update_body();
}
//float player::get_r() { return this->radius; }

void player::update_y(int dir)
{
	this->y += speed*dir;
	update_body();
}


void player::set_rand()
{
	this->y = (rand() % int(int(w_height)));
	this->x = (rand() % int(int(w_width)));
	this->body.setPosition(x, y);
}


void player::reset()
{
	//this->x = int(w_width / 2);
	//this->y = int(w_height / 2);
	this->speed = init_player_speed;
	this->radius = init_player_radius;
	this->body.setRadius(radius);
	this->body.setPosition(x, y);
}




player::player()
{
	this->x = int(w_width/2);
	this->y = int(w_height/2);
	this->speed = init_player_speed;
	this->body = sf::CircleShape(init_player_radius);
	this->radius = init_player_radius;
	this->body.setFillColor(color);
	this->body.setPosition(x, y);
}

void player::inc_radius(int inc)
{
	this->radius += inc;
	this->body.setRadius(radius);
	this->x -= inc;// / 2);
	this->y -= inc;// / 2);
	this->body.setPosition(x, y);
}

player::~player()
{
}
