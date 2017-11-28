#include "Ball.h"


Ball::Ball(float r, Vector3f v, Vector3f pos, float m, Color c) :
	radius(r), velocity(v), center(pos), mass(m), color(c)
{
	int count = 0;
	float x, y, z;
	float squaredLength;


	while (count < pointNum)
	{
		x = (float)(rand() % (2 * res) - res) / res;
		y = (float)(rand() % (2 * res) - res) / res;
		z = (float)(rand() % (2 * res) - res) / res;
		squaredLength = x*x + y*y + z*z;
		if (squaredLength > 0)
		{
			x /= sqrt(squaredLength);
			y /= sqrt(squaredLength);
			z /= sqrt(squaredLength);

			points[count].x = x*radius;
			points[count].y = y*radius;
			points[count].z = z*radius;
			count++;

		}
	}
}
void Ball::move()
{
	center += frametime * velocity;
}

void Ball::draw(RenderWindow &window, RectangleShape &pixel)
{
	pixel.setFillColor(color);
	for (int i = 0; i < pointNum; i++)
	{
		float x = points[i].x + center.x;
		float y = points[i].y + center.y;

		pixel.setPosition(x, y);
		window.draw(pixel);
	}

}
