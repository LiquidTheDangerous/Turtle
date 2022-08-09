#pragma once
#include <SFML/Graphics.hpp>
class TurtleDot : public sf::Drawable, public sf::Transformable
{
public:
	TurtleDot(const float& radius = 15.f, const sf::Color& color = sf::Color::Black);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::CircleShape circle;
};

