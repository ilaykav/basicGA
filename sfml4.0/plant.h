#pragma once

#ifndef PLANT
#define PLANT
#include "item.h"

//#include "props.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <SFML/OpenGL.hpp>

extern sf::Color plant_color;

class plant : public item
{
private:
	sf::Color color = plant_color;
	// set the shape color to green	
public:
	void update_x(int dis);
	void update_y(int dis);
	void add_r(int a);
	void dec_health(int dec_by);
	int get_health();
	void set_rand_position(int min_x, int max_x, int min_y, int max_y);
	~plant();
	plant();
};

#endif

