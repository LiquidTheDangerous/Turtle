#include "TurtleArrow.h"

TurtleArrow::TurtleArrow(const float& d,const float& angle,const sf::Color& color):
	triangle(sf::Triangles,3)
{

	triangle[0].color = color;
	triangle[1].color = color;
	triangle[2].color = color;
	triangle[0].position = sf::Vector2f(d/2.f,0);
	triangle[1].position = sf::Vector2f(-d/2.f,d*std::tan(3.1415926535f*angle/180.f));
	triangle[2].position = sf::Vector2f(-d/2.f,d*std::tan(-3.1415926535f*angle/180.f));

}

void TurtleArrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->triangle, states);
}

void TurtleArrow::setColor(const sf::Color& color)
{
	triangle[0].color = color;
	triangle[1].color = color;
	triangle[2].color = color;
}
