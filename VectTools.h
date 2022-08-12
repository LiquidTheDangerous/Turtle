#include <SFML/Graphics.hpp>
#ifndef _VECTTOOLS_H_
#define _VECTTOOLS_H_

namespace VectTools
{
	float dot(const sf::Vector2f& l, const sf::Vector2f& r);
	float sqrMagnitude(const sf::Vector2f& vect);
	float magnitude(const sf::Vector2f& vect);
	sf::Vector2f leftNormal(const sf::Vector2f& vect);
	sf::Vector2f rightNormal(const sf::Vector2f& vect);
	sf::Vector2f normalize(const sf::Vector2f& vect);
	float cosAngle(const sf::Vector2f& first, const sf::Vector2f& second);
	float angleRad(const sf::Vector2f& first, const sf::Vector2f& second);
	float angleDeg(const sf::Vector2f& first, const sf::Vector2f& second);

	constexpr float PI = 3.1415926535897932f;
};
#endif // !_VECTTOOLS_H_