#include "Chart.h"



Chart::Chart()
{
	plot_.setSize(sf::Vector2f(600, 400));
	plot_.setTitle("generations");
	//plot_.setFont("./font.ttf");
	plot_.setXLabel("Number of generation");
	plot_.setYLabel("Seconds untill done");
	plot_.setBackgroundColor(sf::Color::Blue);
	plot_.setTitleColor(sf::Color::White);
	plot_.setPosition(0,0);
	sf::plot::Curve &curve = plot_.createCurve("gen", sf::Color::Red);
	curve.setFill(1);
	curve.setThickness(5);
	curve.setColor(sf::Color::White);
	curve.setLimit(405);
}

void Chart::update(int add)
{
	sf::plot::Curve &curve = plot_.getCurve("gen");
	curve.addValue(add);
	plot_.prepare();
}

void Chart::draw(sf::RenderTarget& target, sf::RenderStates states) const//, sf::RenderStates states) const
{
	target.draw(this->plot_);
}

Chart::~Chart()
{
}
