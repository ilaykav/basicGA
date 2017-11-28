#pragma once
#include <vector>
#include "brain.cpp"
#ifndef PROP
#define PROP
#include "item.h"
#endif

//#include "props.hpp"
#include <SFML/Graphics.hpp>

extern float enemy_maxRadius;
extern float enemy_minRadius;
extern float enemy_healthRatio;
extern sf::Color enemy_color;

class enemy : public item
{
private:
	int score;
	int init_x;
	int init_y;
	neural_network nn;// = nullptr;
	sf::Color color = enemy_color;
public:
	void add_score(int a);
	int get_s();
	void reset();
	void enemy::set_c(std::vector<std::vector<std::vector<float>>> v);
	std::vector<std::vector<std::vector<float>>> get_c();
	void set_moves(float dis_x, float dis_y);
	void update_x(int dis);
	void update_y(int dis);
	void update(int player_x, int player_y, int player_r);
	enemy();
	~enemy();
};

