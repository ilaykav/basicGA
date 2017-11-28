#include "enemy.h"



void enemy::update(int player_x, int player_y, int player_r)
{
	int x_d = this->x+this->radius - (player_x+player_r);
	int y_d = this->y+this->radius - (player_y + player_r);
	if (std::abs(x_d) < std::abs(y_d))
	{
		if (y_d > 0)
		{
			this->y -= 1;
		}
		else
		{

			this->y += 1;
		}
	}
	else
	{
		if (x_d > 0)
		{
			this->x -= 1;
		}
		else {
			this->x += 1;
		}
	}
	this->body.setPosition(this->x, this->y);
}

int enemy::get_s() { return this->score; }

enemy::enemy()
{
	//nn= neural_network();
	this->score = 0;
	this->init_x = this->x;
	this->init_y = this->y;
	this->body.setFillColor(this->color);
	this->nn = neural_network(2, 3, 0, 2); // (4, 2, 0, 2);
	this->radius = (rand() % int(int(enemy_maxRadius) - enemy_minRadius)) + enemy_minRadius;
	this->health = enemy_healthRatio * this->radius;
	this->body.setRadius(this->radius);
}

void enemy::set_c(std::vector<std::vector<std::vector<float>>> v)
{
	this->nn.set_c(v);
}

std::vector<std::vector<std::vector<float>>> enemy::get_c()
{
	return nn.get_weights();
}
void enemy::add_score(int a)
{
	this->score += 1;
}

void enemy::set_moves(float dis_x, float dis_y)//, float dis_p_x, float dis_p_y)
{
	std::vector<float> in = { dis_x, dis_y };//, dis_p_x, dis_p_y
	std::vector<float> moves =  this->nn.get_results(in);
	if (moves[0] > 0.5)
	{
		this->update_x(10);
	}
	else
	{
		this->update_x(-10);
	}
	if (moves[1] > 0.5)
	{
		this->update_y(10);
	}
	else
	{
		this->update_y(-10);
	}
}

void enemy::reset()
{
	this->x = init_x;
	this->y = init_y;
	this->body.setPosition(x, y);
}

void enemy::update_x(int dis) {
	this->x += dis;
	this->body.setPosition(x, y);
}

void enemy::update_y(int dis) {
	this->y += dis;
	this->body.setPosition(x, y);
}


enemy::~enemy()
{
	//delete nn;
}
