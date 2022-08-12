#include <SFML/Graphics.hpp>

#ifndef _TURTLEARROW_H_
#define _TURTLEARROW_H_

class TurtleArrow : public sf::Drawable
{
public:
	TurtleArrow(const float& d = 30.f,const float& angle = 20.f,const sf::Color& = sf::Color::Black );
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setColor(const sf::Color& color);
private:
	float d;
	sf::VertexArray triangle;
	friend class TurtleNode;
};


#endif // !_TURTLEARROW_H_