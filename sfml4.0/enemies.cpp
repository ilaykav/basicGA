#include "enemies.h"



void enemies::draw(sf::RenderWindow & win)
{
	for (enemy &i : enemieslist)
	{
		win.draw(i.body);
	}
}


void enemies::add_enemy()
{
	enemy e;
	enemieslist.push_back(e);
}


void enemies::add_enemy(std::vector<std::vector<std::vector<float>>> dna) {
	enemy e;
	e.set_c(dna);
	this->enemieslist.push_back(e);
}


void enemies::change_c(int index, std::vector<std::vector<std::vector<float>>> dna)
{
	enemieslist.at(index).set_c(dna);
}


void enemies::reset()
{
	for (enemy &e : enemieslist)
	{
		e.reset();
	}
}


void enemies::remove_enemy(int index)
{
	enemieslist.erase(enemieslist.begin() + index);
}

int enemies::get_total_score()
{
	int sum = 0;
	for (enemy &e : enemieslist)
	{
		sum += e.get_s();
	}
	return sum;
}

void enemies::change_color()
{
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	for (enemy &e: enemieslist)
	{
		e.set_color(sf::Color(r, g, b));
	}
}

void enemies::update(Players &plrs)
{

	for (enemy &e : enemieslist)// update to their nn's
	{
		player closest_player = plrs.get_closest(e.get_x(), e.get_y());
		float disx = (e.get_x() - (closest_player.get_x()));
		float disy = closest_player.get_y() - (e.get_y());
		e.set_moves(disx / w_width * 10, disy / w_height * 10);//, disxpl / w_width * 10, disypl / w_height * 10);
	}

	bool touched = false;
	int index = -1;
	int player_index = -1;
	int index_touched = 0;
	int radius_touched = 0;
	for (player &player : plrs.get_players())
	{
		player_index += 1;
		for (enemy &enemy : enemieslist)
		{
			//p.update(x_player, y_player, radius_player);
			index += 1;
			int disx = abs((enemy.get_x()- (player.get_x())));
			int disy = abs(enemy.get_y() - (player.get_y()));
			if ((enemy.get_r() + player.get_r()) > std::sqrt(std::pow(disx, 2) + std::pow(disy, 2)))
			{
				if (enemy.get_r() > player.get_r())
				{
					enemy.add_score(1);
					plrs.add_player();
					plrs.remove_player(player_index);
					//enemy.set_r(enemy.get_r() + (player.get_r() / 2));
				}
				else
				{
					remove_enemy(index);
					plrs.get_players()[player_index].inc_radius(enemy.get_r()/3);
				}
			}
		}
		index = -1;
	}

	
}


enemies::enemies(int count)
{
//	bests = new std::vector<enemy>;
	//enemieslist = new std::vector<enemy>;
	for (int i = 0; i<count; i++)
	{
		this->add_enemy();
	}
}


std::vector<enemy> enemies::get_best()
{
	return this->bests;
}


std::vector<enemy> enemies::roulette(std::vector<enemy> b)
{
	std::vector<enemy> ret;
	std::vector<enemy> enemiescpy = enemieslist;
	
	for (int i = 0; i < 2; i++)
	{
		int sum = 1;
		for (enemy &e : enemiescpy)
		{
			int dis = e.get_s()*e.get_s();//make the best one greater
			sum += dis;
		}
		int count = -1;
		int r = ((rand()) % sum );
		int feetness_so_far = 0;
		for (enemy e : enemiescpy)
		{
			count++;
			feetness_so_far += e.get_s()*e.get_s();
			if (feetness_so_far > r)
			{
				enemiescpy.erase(enemiescpy.begin() + count);
				ret.push_back(e);
				break;
			}
		}
	}
	if (ret.size() < 2) {
		std::cout << " same parents" << std::endl;
		return b;
	}
	if (ret[0].get_x() == ret[1].get_x()) {
		std::cout << " same parents" << std::endl;
	}
	return ret;
}


int enemies::min_dis(int x, int y)
{

	int dis_y = abs(y - enemieslist.at(0).get_y());
	int dis_x = abs(x - enemieslist.at(0).get_x());
	int dis = int(std::sqrt(dis_x*dis_x + dis_y*dis_y));
	int min_dis = dis;

	for (enemy p : enemieslist)
	{
		int dis_y = abs(y - p.get_y());
		int dis_x = abs(x - p.get_x());
		int dis = int(std::sqrt(dis_x*dis_x + dis_y*dis_y));
		if (dis < min_dis)
		{
			min_dis = dis;
		}
	}

	return min_dis;
}


int enemies::distance(int x, int y, int x2, int y2)
{
	int dis_x = abs(x - x2);
	int dis_y = abs(y - y2);
			
	return int(std::sqrt(dis_x*dis_x + dis_y*dis_y));
}


void enemies::update_x(int dis)
{
	for (enemy &p : enemieslist)
	{
		p.update_x(dis);
	}
}


void enemies::update_y(int dis)
{
	for (enemy &p  : enemieslist)
	{
		p.update_y(dis);
	}
}


void enemies::clear_enemies() {
	this->enemieslist.clear();
}


enemies::~enemies()
{/*
	if (!enemieslist.empty())
	{
		std::vector<enemy> tmpenemieslist;
		//td::map<int, std::vector<CClass*>>::iterator it = pointers.begin(); it != pointers.end(); it++
		for (enemy &e : enemieslist) { delete &e; }
		enemieslist.clear();
		enemieslist.swap(tmpenemieslist);
	}
	
	if (!enemieslist.empty())
	{
		std::vector<enemy> tmpbests;
		for (enemy &e : enemieslist) { delete &e; }
		bests->clear();
		bests->swap(tmpbests);
	}*/
}
