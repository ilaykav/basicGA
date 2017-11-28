#pragma once
#ifndef PLAYERS
#define PLAYERS
#include <vector>
#include "player.h"


class Players
{
private:
	std::vector<player> players;// = nullptr;

public:
	void reset_set_random();
	void remove_player(int index);
	std::vector<player> get_players();
	player get_closest(int x, int y);
	void Players::add_player();
	void draw(sf::RenderWindow& win);
	Players::Players(int count);
	Players();
	~Players();
};

#endif

