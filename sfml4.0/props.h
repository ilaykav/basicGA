#pragma once
#ifndef PROPS
#define PROPS
#include <SFML/Graphics.hpp>
extern float plant_minRadius;
extern float plant_maxRadius;
extern float plant_regenerate;
extern float plant_healthRatio;
extern float enemy_minRadius;
extern float enemy_maxRadius;
extern int border_x_min;
extern int border_x_max;
extern int border_y_min;
extern int border_y_max;
extern float enemy_healthRatio;
extern int num_enemies;
extern int init_player_radius;
extern int init_player_speed;
extern int w_width;
extern int w_height;//sf::VideoMode::getDesktopMode().height;
extern sf::Color plant_color;
extern sf::Color player_color;
extern sf::Color enemy_color;
#endif

