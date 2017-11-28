#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "src/plot.h"
//#include "src/plot.cpp"
class Chart : public sf::Drawable
{
private:
	
	sf::plot::Plot plot_;
		
	std::string dns_;
	
public:
	void Chart::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(int value);
	Chart();
	~Chart();
};

