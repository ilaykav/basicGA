#pragma once
#ifndef PROPS
#define PROPS
#include "plant.h"
#endif

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cmath>
#include <vector>
#include "Ball.h"
#include "plantFarm.h"
#include "player.h"
#include "enemies.h"
#include <random>
#include <stdlib.h>
#include "enemy.h"
#include "Players.h"

using namespace std;
using namespace sf;
const int wsize = 800;
float frametime = 1.0;
extern int w_height;
extern int w_width;
extern int num_enemies;

int y = 7;
int* py = &y;
int found = 0;
enemy e;// = new enemy;
enemy e2;// = new enemy;
Players plrs(32);// = new Players(32);
std::vector<enemy> best = { e, e2 };
int time_gen = 0;
int mutate_rate = 198;
int gen = 0;
int last_score = 0;

int size_v_3(std::vector<std::vector<std::vector<float>>> v)
{
	int n = 0;
	for (std::vector<std::vector<float>> &vi : v)
	{

			n += 1;
		
	}
	return n;
}


int full_size_v_3(std::vector<std::vector<std::vector<float>>> v)
{
	int n = 0;
	for (std::vector<std::vector<float>> &vi : v)
	{
		for (std::vector<float> &v2 : vi)
		{
			n += v2.size();
		}
	}
	return n;
}


void crossover(std::vector<enemy>& e)
{
	float r = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	if (r > 0.75 || (e[0].get_x() == e[1].get_x() && e[0].get_x() == e[1].get_x()))
	{
	return;
	}
	enemy dad = e[0];
	enemy mom = e[1];
	int limit = size_v_3(mom.get_c());
	int k_middle = (rand() % limit);
	int vd = 0;
	int vdd = 0;
	std::vector<std::vector<std::vector<float>>> m = mom.get_c();
	std::vector<std::vector<std::vector<float>>> d = dad.get_c();
	//create the offspring
	for (std::vector<std::vector<float>> &v : m)
	{
		for (std::vector<float> &vv : v)
		{
			int k_middle = (rand()% vv.size());
			for (int ind = 0; ind < k_middle; ind++)
			{
				float tmp = vv[ind];
				vv[ind] = d[vd][vdd][ind];
				d[vd][vdd][ind] = tmp;
			}
			vdd++;
		}
		vd++;
		vdd = 0;
	}
	

	e[0].set_c(m);
	e[1].set_c(d);
}


void mutate(std::vector<enemy>& e, int mutate_rate)
{
	for (enemy &en : e){
		std::vector<std::vector<std::vector<float>>> c6 =  en.get_c();
		for (std::vector<std::vector<float>> &c1 : c6){
			for (std::vector<float> &c2 : c1){
				for (float &c3 : c2){
					int mutate_risk = (rand() % int(int(200) - 0)) + 0;
					if (mutate_risk > mutate_rate){
						float change = (rand() % int(int(200))) - 100;
						c3 += change/100;
						if (c3 > 1) { c3 = c3 - 1; }
						if (c3 < -1) { c3 = c3 + 1; }
					}
				}
			}
		}
		en.set_c(c6);
	}
}


int main() // change roulette??????????
{
	int timer = 0;
	// create the window
	srand(static_cast <unsigned> (time(NULL)));
	// run the main loop
	int x = 0;
	sf::RenderWindow window(sf::VideoMode(w_width, w_height), "Game");

	enemies enms(num_enemies);
	//plantFarm * pf = new plantFarm;
	bool b = true;
	while (window.isOpen())
	{
		x += 1;
		time_gen += 1;
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				window.close();
				break;
			/*case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					//pf->update_x(50);
					enms.update_x(50);
					break;
				case sf::Keyboard::Right:
					//pf->update_x(-50);
					enms.update_x(-50);
					break;
				case sf::Keyboard::Up:
					//pf->update_y(50);
					enms.update_y(50);
					break;
				case sf::Keyboard::Down:
					//pf->update_y(-50);
					enms.update_y(-50);
					break;
				}*/
				break;

			default:
				break;
			}
		}


		//plant closest = pf->closest(p.get_x(), p.get_y());
		timer = 0;
		enms.update(plrs);
		int min_dis = enms.min_dis(w_width / 2, w_height / 2);
		if (min_dis > 4000 || time_gen > 650)
		{
			enemies e(0);
			std::vector<enemy> bestcp = best;
			//if (enms.get_total_score()*1.5 > last_score) {//enms.get_total_score() > last_score
			best = enms.roulette(best);
			bestcp = best;
			last_score = enms.get_total_score();
			//}
			for (int i = 0; i < num_enemies / 2; i++)
			{
				best = bestcp;
				crossover(best);
				mutate(best, mutate_rate);
				e.add_enemy(best[0].get_c());
				e.add_enemy(best[1].get_c());
			}
			gen += 1;
			std::cout << "generation: " << gen << " score: "<< enms.get_total_score() << std::endl;
			time_gen = 0;
			enms.clear_enemies();
			enms = e; // ????
			plrs.reset_set_random();
			enms.change_color();
		}
		
		/*	if (update == -1)
			{
				mutate_rate = 5;
				p.reset();
				p.set_rand();
				found += 1;
				if (found > 0)
				{
					found = 0;
					enemies e(0);
					std::vector<enemy> bestcp = best;
					for (int i = 0; i < num_enemies / 2; i++)
					{
						best = enms.roulette(p.get_x(), p.get_y());
						crossover(best);
						mutate(best, mutate_rate);
						e.add_enemy(best[0].get_c());
						e.add_enemy(best[1].get_c());
						best = bestcp;
					}
					enms.clear_enemies();
					enms = e;
					pf = new plantFarm();
					gen += 1;
					std::string g = "generation ";
					//std::cout << g << gen << " time  -- " << time_gen << " -- found " << std::endl;
					for (int i = 1; i < time_gen/3; i++)
					{
						std::cout << "|";
					}
					std::cout << "|" << std::endl;
					time_gen = 0;
					p.set_rand();
				}
			}
		}


		/*if (pf->update(p.get_x(), p.get_y(), p.get_r()))
		{
			p.inc_radius(2);
		}*/

		window.clear();
		//pf->draw(window);
		enms.draw(window);
		plrs.draw(window);
		//window.draw(p.body);
		sf::RenderStates r;
		window.display();
	}
	return 0;
}
