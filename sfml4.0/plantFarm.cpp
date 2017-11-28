#include "plantFarm.h"

void plantFarm::draw(sf::RenderWindow& win)
{
	for (plant &i : this->plants)
	{
		win.draw(i.body);
	}
}

plant plantFarm::closest(int x, int y)
{
	plant minp;
	int min = std::sqrt(w_height*w_height + w_width*w_width);
	for(plant &p : this->plants)
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

void plantFarm::add_plant()
{
	plant p;
	this->plants.push_back(p);
}

void plantFarm::remove_plant(int index)
{
	plants.erase(plants.begin() + index);
}


void plantFarm::update_x(int dis)
{
	for (plant &p : plants)
	{
		p.update_x(dis);
	}
}

void plantFarm::update_disy(int dis)
{
	this->disy += dis;
	if (disy > this->y_max)
	{
		this->y_max += disy;
		plant p;
		p.set_rand_position(0, w_width, w_height, w_height + dis);
		plants.push_back(p);
	}
	if (disy < this->y_min)
	{
		this->y_min -= disy;
		plant p;
		p.set_rand_position(0, w_width, -dis, 0);
		this->plants.push_back(p);
	}
}

void plantFarm::update_disx(int dis)
{
	this->disx += dis;
	if (disx > this->x_max)
	{
		plant p;
		p.set_rand_position(w_width, w_width+dis, 0, w_height);
		this->plants.push_back(p);
		this->x_max += disx;
	}
	if (disx < this->x_min)
	{
		this->x_min -= disx;
		plant p;
		p.set_rand_position(w_width, w_width + dis, 0, w_height);
		this->plants.push_back(p);
	}
}

void plantFarm::update_y(int dis)
{
	for (plant &p : plants)
	{
		p.update_y(dis);
	}
}

bool plantFarm::update(int x_player, int y_player, int radius_player)
{
	bool delete_plant = false;
	bool touched = false;
	int index = -1;
	int index_touched = 0;
	for (plant &p : plants)
	{
		index += 1;
		int disx = abs((p.get_x() + p.get_r() - (x_player + radius_player)));
		int disy = abs(y_player + radius_player - (p.get_y() + p.get_r()));
		if ((p.get_r() + radius_player) > std::sqrt(std::pow(disx, 2) + std::pow(disy, 2)))
		{
			p.dec_health(10);
			if (p.get_health() < 80)
			{
				delete_plant = true;
				index_touched = index;
			}
			touched = true;
		}
	}
	if (delete_plant)
	{
		remove_plant(index_touched);
	}
	return touched;
}

int plantFarm::get_plants_size()
{
	return int(this->plants.size());
}

plant plantFarm::get_plant(int index)
{
	return this->plants.at(index);
}

void plantFarm::update()
{
	for (plant &i : this->plants)
	{
		i.add_r(10);
	}
}

plantFarm::plantFarm()
{
	//this->plants = new std::vector<plant>;
	for (int i = 0; i<10; i++)
	{
		this->add_plant();
	}
}



plantFarm::~plantFarm()
{
	/*if (!plants.empty())
	{
	std::vector<plant> tmpplants;
	for (plant &e : plants) 
	{
		delete &e; 
	}
	plants.clear();
	plants.swap(tmpplants);
	}*/
}