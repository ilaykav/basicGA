#include "props.h"

float plant_minRadius = 50;
float plant_maxRadius = 80;
float plant_regenerate = 2;
float plant_healthRatio = 1.8;
float enemy_minRadius = 15;
float enemy_maxRadius = 20;
int border_x_min = -20;
int border_x_max = -20;
int border_y_min = -20;
int border_y_max = -20;
float enemy_healthRatio = 1.8;
int num_enemies = 30;
int init_player_radius = 4;
int init_player_speed = 10;
int w_width = 2500;//sf::VideoMode::getDesktopMode().width;
int w_height = 1300;//sf::VideoMode::getDesktopMode().height;
sf::Color plant_color = sf::Color::Green;
sf::Color player_color = sf::Color::Magenta;
sf::Color enemy_color = sf::Color::Red;