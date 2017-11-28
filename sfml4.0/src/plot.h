#ifndef SFML_PLOT_PLOT_H
#define SFML_PLOT_PLOT_H

#include <map>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "axis.h"
#include "grid.h"
#include "curve.h"

namespace sf
{
namespace plot
{

class Plot
        : public sf::Drawable
        , public sf::Transformable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ////////////////////////////////////////////////////////////
    Plot();

    ////////////////////////////////////////////////////////////
    /// \brief constructor
    ///
    /// \param size plot size
    /// \param title plot title
    ////////////////////////////////////////////////////////////
    Plot(const sf::Vector2f &size, const std::string &title);

    ////////////////////////////////////////////////////////////
    /// \brief create a new curve
    ///
    /// \param name curve name
    /// \param color curve color
    ///
    /// \return Curve return ref to the new curve
    ////////////////////////////////////////////////////////////
    Curve &createCurve(const std::string &name, const Color &color);

    ////////////////////////////////////////////////////////////
    /// \brief test if a curve name exist
    ///
    /// \param name curve name query
    ///
    /// \return bool true if exist
    ////////////////////////////////////////////////////////////
    bool haveCurve(const std::string &name) const;

    ////////////////////////////////////////////////////////////
    /// \brief get a cuve
    ///
    /// \param name curve name query
    ///
    /// \return a ref to the curve of ... an exception
    ////////////////////////////////////////////////////////////
    Curve& getCurve(const std::string& name);

    ////////////////////////////////////////////////////////////
    /// \brief prepare the plot to be draw
    ////////////////////////////////////////////////////////////
    void prepare();

    ////////////////////////////////////////////////////////////
    /// \brief set the name of the X label
    ///
    /// \param name x label name
    ////////////////////////////////////////////////////////////
    void setXLabel(const std::string &name);

    ////////////////////////////////////////////////////////////
    /// \brief set the name of the Y label
    ///
    /// \param name y label name
    ////////////////////////////////////////////////////////////
    void setYLabel(const std::string &name);

    ////////////////////////////////////////////////////////////
    /// \brief set the color of the background
    ///
    /// \param color background color
    ////////////////////////////////////////////////////////////
    void setBackgroundColor(const sf::Color &color);

    ////////////////////////////////////////////////////////////
    /// \brief set the color of the title
    ///
    /// \param color title color
    ////////////////////////////////////////////////////////////
    void setTitleColor(const sf::Color &color);

    ////////////////////////////////////////////////////////////
    /// \brief set the title of the plot
    ///
    /// \param title
    ////////////////////////////////////////////////////////////
    void setTitle(const std::string &title);

    ////////////////////////////////////////////////////////////
    /// \brief set the font of the plot
    ///
    /// \param filename path of the font
    ////////////////////////////////////////////////////////////
    void setFont(const std::string &filename);

    ////////////////////////////////////////////////////////////
    /// \brief set the size
    ////////////////////////////////////////////////////////////
    void setSize(const sf::Vector2f& size);
private:
    ////////////////////////////////////////////////////////////
    /// \brief sfml method to draw
    ////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /// x axis
    Axis xaxis_;

    /// y axis
    Axis yaxis_;

    /// grid isntance
    plot::Grid grid_;

    /// size of the chart
    sf::Vector2f size_;

    /// collection of curves
    std::map<std::string, Curve> curves_;

    /// graph size (reduce size from size)
    sf::Vector2f graphSize_;
    /// graph real position
    sf::Vector2f graphPos_;

    static const int kTopSize = 10;
    static const int kLeftSize = 12;
    static const int kRightSize = 5;
    static const int kBottomSize = 12;
    static const int kBorderSize = 2;

    /// global font
    sf::Font font_;

    /// title
    sf::Text title_;

    /// background
    sf::RectangleShape bg_;
};


inline void Plot::setXLabel(const std::string &name)
{
    xaxis_.setName(name);
}

inline void Plot::setYLabel(const std::string &name)
{
    yaxis_.setName(name);
}

inline void Plot::setTitleColor(const sf::Color &color)
{
    title_.setColor(color);
}

inline void Plot::setBackgroundColor(const sf::Color &color)
{
    bg_.setFillColor(color);
}




Plot::Plot()
{
}

Plot::Plot(const Vector2f &size, const std::string &title)
{
	setTitle(title);
	setSize(size);
}

void Plot::setSize(const sf::Vector2f& size)
{
	size_ = size;
	graphPos_.x = size_.x * (kLeftSize / 100.0);
	graphPos_.y = size_.y * (kTopSize / 100.0);

	graphSize_.x = size_.x - kBorderSize * 2
		- size_.x * (kLeftSize / 100.0)
		- size_.x * (kRightSize / 100.0);
	graphSize_.y = size_.y - kBorderSize * 2
		- size_.y * (kTopSize / 100.0)
		- size_.y * (kBottomSize / 100.0);

	grid_.setup(graphSize_);
	grid_.setPosition(graphPos_);

	xaxis_.setSize(graphSize_.x);
	yaxis_.setSize(graphSize_.y);

	xaxis_.setPosition(graphPos_.x, graphPos_.y + graphSize_.y + 5);
	yaxis_.setPosition(graphPos_.x - 20, graphPos_.y + graphSize_.y);
	yaxis_.setRotation(-90);

	bg_.setSize(sf::Vector2f(size_.x - kBorderSize * 2, size_.y - kBorderSize * 2));
	bg_.setFillColor(sf::Color(220, 220, 200));
	bg_.setOutlineColor(sf::Color(200, 0, 0));
	bg_.setOutlineThickness(kBorderSize);
	bg_.setPosition(sf::Vector2f(kBorderSize, kBorderSize));
}

bool Plot::haveCurve(const std::string &name) const
{
	return curves_.find(name) != curves_.end();
}

Curve& Plot::getCurve(const std::string& name)
{
	if (haveCurve(name) == false)
		throw std::string("Curve not found");
	return curves_[name];
}

Curve &Plot::createCurve(const std::string &name, const sf::Color& color)
{
	curves_[name] = Curve(graphSize_, color);
	curves_[name].setLabel(name);
	curves_[name].setPosition(graphPos_);
	return curves_[name];
}

void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(bg_, states);
	target.draw(grid_, states);
	target.draw(title_, states);
	target.draw(xaxis_, states);
	target.draw(yaxis_, states);

	for (std::map<std::string, Curve>::const_iterator it = curves_.begin();it != curves_.end();++it)
		target.draw(it->second, states);
}

void Plot::prepare()
{
	sf::Vector2f rangex;
	sf::Vector2f rangey;

	rangex.x = std::numeric_limits<float>::max();
	rangey.x = std::numeric_limits<float>::min();

	rangey.x = std::numeric_limits<float>::max();
	rangey.y = std::numeric_limits<float>::min();

	for (std::map<std::string, Curve>::iterator it = curves_.begin();it != curves_.end();++it)
	{
		Curve &curve = it->second;
		curve.prepare(rangex, rangey);
	}

	xaxis_.prepare(rangex);
	yaxis_.prepare(rangey);
}

void Plot::setFont(const std::string &filename)
{
	if (!font_.loadFromFile(filename))
	{
		throw;
	}
	title_.setFont(font_);
	xaxis_.setFont(&font_);
	yaxis_.setFont(&font_);
	title_.setPosition(sf::Vector2f(-title_.getLocalBounds().width / 2 + size_.x / 2, 0));
}

void Plot::setTitle(const std::string &title)
{
	title_.setString(title);
	title_.setCharacterSize(22);
}

}
}


#endif // SFML_PLOT_PLOT_H

