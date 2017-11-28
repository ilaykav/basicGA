#pragma once

#ifndef ENEMIES
#define ENEMIES
#include "Players.h"
#include "enemy.h"
#include <vector>
class enemies
{
private:
	std::vector<enemy> enemieslist;
	std::vector<enemy> bests;
public:
	int get_total_score();
	void reset();
	std::vector<enemy> get_best();
	void change_c(int index, std::vector<std::vector<std::vector<float>>> dna);
	int enemies::min_dis(int x, int y);
	void draw(sf::RenderWindow& win);
	void update(Players &plrs);
	void add_enemy();
	void add_enemy(std::vector<std::vector<std::vector<float>>> dna);
	int distance(int x, int y, int x2, int y2);
	void update_x(int dis);
	std::vector<enemy> roulette(std::vector<enemy> b);
	void update_y(int dis);
	void remove_enemy(int index);
	void clear_enemies();
	void change_color();
	enemies(int count);
	~enemies();
};

#endif


