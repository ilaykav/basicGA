#pragma once



#ifndef PLAYER
#define PLAYER
#include "props.hpp"
#include "item.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <SFML/OpenGL.hpp>
#include <string>

extern sf::Color player_color;
extern int init_player_speed;
extern int init_player_radius;

class player : public item
{
private:
	std::string name;
	int speed;
	sf::Color color = player_color;
	void update_body();
public:
	//float get_r();
	//void setName(std::string name);
	void reset();
	void set_rand();
	void update_x(int direcation);
	void update_y(int direcation);
	void inc_radius(int inc);
	player();
	~player();
};

#endif
