#include "TurtleDot.h"

TurtleDot::TurtleDot(const float& radius, const sf::Color& color)
{
	this->circle.setRadius(radius);
	this->circle.setFillColor(color);
	this->circle.move(-radius, -radius );
}

void TurtleDot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	target.draw(this->circle, states);
}
