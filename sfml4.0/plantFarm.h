#pragma once
#include "plant.h"
#include <vector>

extern int border_x_min;
extern int border_x_max;
extern int border_y_min;
extern int border_y_max;


class plantFarm
{
private:
	int disx;
	int disy;
	int x_min = border_x_min;
	int x_max = border_x_max;
	int y_min = border_y_min;
	int y_max = border_y_max;
	std::vector<plant> plants;// = nullptr;
public:
	plant closest(int x, int y);
	void update_disx(int dis);
	void update_disy(int dis);
	void update_y(int dis);
	void update_x(int dis);
	void draw(sf::RenderWindow& win);
	void add_plant();
	void remove_plant(int index);
	bool update(int x_player, int y_player, int radius_player);
	int get_plants_size();
	plant get_plant(int index);
	plantFarm();
	void update();
	~plantFarm();
};

