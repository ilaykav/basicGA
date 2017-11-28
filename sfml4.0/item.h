#pragma once


#ifndef ITEM
#define ITEM

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <SFML/OpenGL.hpp>

extern float plant_maxRadius;
extern float plant_minRadius;
extern float plant_healthRatio;
extern int w_width;
extern int w_height;
extern sf::Color player_color;

class item
{
protected:
	sf::Color color = player_color;
	unsigned int x;
	unsigned int y;
	float radius;
	unsigned int health;


	// set the shape color to green	
public:
	virtual void set_color(sf::Color);
	sf::CircleShape body;// = nullptr;
	void update();
	int get_x();
	int get_y();
	void set_r(int x) { this->radius = x; }
	virtual float get_r();
	void draw(sf::RenderWindow& win);
	item(float radius, unsigned int health);
	item();
	item(float radius);
	~item();
};

#endif

