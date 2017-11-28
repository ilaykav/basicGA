#include "players.h"


void Players::draw(sf::RenderWindow & win)
{
	for (player &i : this->players)
	{
		win.draw(i.body);
	}
}

void Players::remove_player(int index)
{
	players.erase(players.begin() + index);
}

void Players::reset_set_random()
{
	for (player &p : players)
	{
		p.reset();
		p.set_rand();
	}
}

std::vector<player> Players::get_players()
{
	return this->players;
}

player Players::get_closest(int x, int y)
{
	player minp;
	int min = std::sqrt(w_height*w_height + w_width*w_width);
	for (player &p : this->players)
	{
		int dis_x = abs(x - p.get_x());
		int dis_y = abs(y - p.get_y());
		if (min > std::sqrt(dis_x*dis_x + dis_y*dis_y))
		{
			minp = p;
			min = std::sqrt(dis_x*dis_x + dis_y*dis_y);
		}
	}
	return minp;
}

void Players::add_player()
{
	player e;
	e.set_rand();
	this->players.push_back(e);
}

Players::Players()
{
	//players = new std::vector<player>;
}

Players::Players(int count)
{
	//players = new std::vector<player>;
	for (int i = 0; i<count; i++)
	{
		this->add_player();
	}
}


Players::~Players()
{/*
	if (!players.empty())
	{
		std::vector<player> tmpplayers;
		for (player &e : *players) { delete &e; }
		players.clear();
		players.swap(tmpplayers);
	}*/
}
