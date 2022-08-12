#include <SFML/Graphics.hpp>
#ifndef _TURTLEDOT_H_
#define _TURTLEDOT_H_

class TurtleDot : public sf::Drawable, public sf::Transformable
{
public:
	TurtleDot(const float& radius = 15.f, const sf::Color& color = sf::Color::Black);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::CircleShape circle;
};


#endif // !_TURTLEDOT_H_