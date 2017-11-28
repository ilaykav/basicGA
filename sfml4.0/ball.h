
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cmath>
#include <vector>

using namespace std;
using namespace sf;

#pragma region data
extern const int wsize;
extern float frametime;
const int pointNum = 5000;
const int radius = 100;
const int res = 1000;
#pragma endregion data


class Ball
{
public:
	Vector3f center;
	Vector3f velocity;
	float mass;
	Vector3f points[pointNum];
	float radius;
	Color color;

	void draw(RenderWindow &window, RectangleShape &pixel);

	Ball(float r, Vector3f v, Vector3f pos, float m, Color c);
	void Ball::move();

};
