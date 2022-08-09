#pragma once
#include "TurtleNode.h"
#include "Earcut.hpp"
#include <iostream>
class TurtleController
{
public:
	TurtleController();
	TurtleController(TurtleNode* turtle);
	void attachTurtle(TurtleNode* turtle);
	void forward(const float& distance);
	void fastForward(const float& distance);
	void backward(const float& distance);
	void fastBackward(const float& distance);
	void fd(const float& distance);
	void lt(const float& angle);
	void fastLeft(const float& angle);
	void right(const float& angle);
	void fastRight(const float& angle);
	void rt(const float& angle);
	void left(const float& angle);
	void setPosition(const float& x, const float& y);
	void setRotation(const float& angle);
	void move(const float& x, const float& y);
	void moveRad(const float& distance, const float& angle);
	void fastMove(const float& x, const float& y);
	void fastMoveRad(const float& distance, const float& angle);
	void dot(const float& radius = 15.f, const unsigned char& r = 0U, const unsigned char& g = 0U, const unsigned char& b=0U, const unsigned char& alpha = 255U);
	void clearDots();
	void circle(const float& radius = 100.f, const float& angle = 360.f,const bool& left = 1, const int& point_count = 360);
	void plotFunction(std::function<float(const float& x)> func, const float& start = -100.f, const float& end = 100.f, const float& step = 1.f, const float& wx = 1.f, const float& wy = 1.f);
	void logPosition(std::ostream& stream = std::cout);
	void penUp();
	void penDown();
	void showTurtle();
	void hideTurtle();
	void setFastUpdate(const bool& flag);
	void beginFill();
	void endFill();
	void sleep(const float& seconds);
	void setSpeed(const float& speed);
	void logAngle(std::ostream& stream = std::cout);
	void pushState();
	void popState();
	void clearLines();
	
	void setLinesColor(const unsigned char& r, const unsigned char& g, const unsigned char& b,const unsigned char& alpha = 255U);
private:

	struct EndFill
	{
		bool* done;
		void operator()(TurtleNode& turtle, const sf::Time& dt)
		{
			if (turtle.start_fill_iter == turtle.lines.end()) 
			{
				std::cerr << "Begin fill;" << std::endl;
				*done = true;
				return;
			}
			std::vector<std::vector<sf::Vector2f>> poly(1);
			for (auto iter = turtle.start_fill_iter; iter != turtle.lines.end(); ++iter) 
			{
				sf::VertexArray& arr = *iter;
				
				for (int i = 0; i < arr.getVertexCount(); ++i) 
				{
					poly[0].push_back(arr[i].position);
				}
				
			}

			std::vector<int> ind = mapbox::earcut<int>(poly);
			sf::VertexArray trianglesArray(sf::PrimitiveType::Triangles, ind.size());
			int c = 0;
			for (int& i : ind) 
			{
				trianglesArray[c] = poly[0][i];
				trianglesArray[c].color = turtle.lineColor;
				c++;
			}
			turtle.fillZones.push_back(trianglesArray);
			*done = true;
			turtle.start_fill_iter = turtle.lines.end();
		}
	};

	struct BeginFill 
	{
		bool* done;
		void operator()(TurtleNode& turtle, const sf::Time& dt) 
		{
			if (turtle.lines.empty()) 
			{
				turtle.start_fill_iter = turtle.lines.begin();
			}
			else 
			{
				turtle.start_fill_iter = std::prev(turtle.lines.end());
			}
			*done = true;
		}
	};

	struct FuncPlot 
	{
		std::function<float(const float& x)> func;
		float start;
		float end;
		float step;
		float absSpeed;
		bool init = false;
		bool* done;
		float len;
		float _cos;
		float _sin;
		float a_sin;
		float a_cos;
		float angle;
		int index = 0;
		sf::Vector2f current_vect;
		sf::Vector2f nextPos;
		sf::Transform Trans;
		std::vector < sf::Vector2f > dvect;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			sf::Vector2f position = node.getPosition();
			if (!init) 
			{
				Trans.rotate(node.getRotation());
				dvect.reserve((end - start)/step);

				sf::Vector2f firstPoint;
				sf::Vector2f secondPoint;
				absSpeed = node.getSpeed();
				for (float _start = start; _start <= end; _start += step) 
				{
					firstPoint.x = _start ;
					firstPoint.y = func(_start);
					secondPoint.x = (_start + step) ;
					secondPoint.y = func(_start + step);
					dvect.push_back(secondPoint - firstPoint);
					//std::cout << (secondPoint - firstPoint).x << ' ' << (secondPoint - firstPoint).y << std::endl;
 				}

				if (!node.isPenUp)
				{
					sf::VertexArray curve(sf::LineStrip, dvect.size() + 1);
					//curve.
					curve[0].position = position;
					curve[0].color = node.lineColor;
					for (int i = 1; i < dvect.size() + 1; ++i)
					{
						//curve[i].position = position;
						curve[i].color = sf::Color::Transparent;
					}
					node.lines.push_back(curve);
				}

				current_vect = Trans.transformPoint(dvect[index]);
				nextPos = position + current_vect;
				len = std::sqrt(std::pow(current_vect.x, 2) + std::pow(current_vect.y, 2));
				_cos = current_vect.x / len;
				_sin = current_vect.y / len;
				a_cos = std::acos(_cos) * 180.f / TurtleNode::PI;
				a_sin = std::asin(_sin) * 180.f / TurtleNode::PI;
				if (current_vect.x > 0) 
				{
					if (current_vect.y > 0) 
					{
						angle = a_sin;
					}
					else 
					{
						angle = a_cos;
					}
				}
				else 
				{

					angle = 180 - a_sin;

				}


				node.setRotation(angle);
				init = true;
			}//!init

			if (!node.isPenUp)
			{
				node.lines.back()[index].color = node.lineColor;
				node.lines.back()[index + 1].position = position;
			}

			if (index >= dvect.size())
			{
				*done = true;
				return;
			}
			

			float dtf = dt.asSeconds();
			if (std::pow((position.x - nextPos.x), 2) + std::pow((position.y - nextPos.y), 2) <= std::pow(dtf * absSpeed, 2) + 10.f) 
			{
				node.setPosition(nextPos);
				position = node.getPosition();
				if (index + 1 < dvect.size()) 
				{
					index += 1;
					if (!node.isPenUp)
					{
						node.lines.back()[index].position = nextPos;
					}
					current_vect = Trans.transformPoint(dvect[index]);
					nextPos = position + current_vect;
					len = std::sqrt(std::pow(current_vect.x, 2) + std::pow(current_vect.y, 2));
					_cos = current_vect.x / len;
					_sin = current_vect.y / len;
					a_cos = std::acos(_cos) * 180.f/TurtleNode::PI;
					a_sin = std::asin(_sin) * 180.f / TurtleNode::PI;
					if (current_vect.x > 0)
					{
						if (current_vect.y > 0)
						{
							angle = a_cos;
						}
						else
						{
							angle = a_sin;
						}
					}
					else
					{

						angle = 180 - a_sin;

					}
					node.setRotation(angle);
				}
				else
				{
					*done = true;
					return;
				}
			}
			else 
			{
				node.move(dtf * absSpeed * _cos, dtf * absSpeed * _sin);
			}
			//*done = true;
		};
	};
	struct DrawCircle 
	{
		bool* done;
		float radius;
		float angleSegment;
		int countPassed = 0;
		int passedRequired;
		int pointCount;
		float polyAngle;
		float outPolyAngle;
		float polySize;
		float absSpeed;
		int left = 1;
		float _cos;
		float _sin;
		sf::Vector2f nextPos;
		bool init = false;
		sf::Vector2f centerPos;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			const sf::Vector2f position = node.getPosition();
			if (!init) 
			{
				passedRequired = (angleSegment / 360.f)*pointCount;
				if (!node.isPenUp) 
				{
					sf::VertexArray circle(sf::LineStrip, passedRequired+1);
					//circle.
					circle[0].position = position;
					circle[0].color = node.lineColor;
					for (int i = 1; i < passedRequired + 1; ++i) 
					{
						//circle[i].position = position;
						circle[i].color = sf::Color::Transparent;
					}
					node.lines.push_back(circle);
				}
				polyAngle = 180.f - 360.f / pointCount;
				outPolyAngle = left*(180 - polyAngle);
				polySize = 2 * radius *std::cos(TurtleNode::PI * polyAngle / 360.f)/std::sin(TurtleNode::PI * polyAngle / 360.f);
				absSpeed = node.speed;
				node.rotate(outPolyAngle);
				float angle = node.getRotation();
				_cos = std::cos(TurtleNode::PI * angle/ 180.f);
				_sin = std::sin(TurtleNode::PI * angle/ 180.f);

				nextPos.x = position.x + _cos*polySize;
				nextPos.y = position.y + _sin*polySize;
				init = true;
			}
			if (!node.isPenUp) 
			{

				node.lines.back()[countPassed].color = node.lineColor;
				node.lines.back()[countPassed + 1].position = position;
			}
			float dtf = dt.asSeconds();
			if (std::pow((position.x - nextPos.x), 2) + std::pow((position.y - nextPos.y), 2) <= std::pow(dtf * absSpeed, 2) + 10.f) 
			{
				if (countPassed == passedRequired)
				{
					if (!node.isPenUp)
					{
						node.lines.back()[countPassed].color = node.lineColor;
					}
					*done = true;
					return;
				}
				if (!node.isPenUp) 
				{
					node.lines.back()[countPassed + 1].position = nextPos;
				}
				++countPassed;
				if (countPassed != passedRequired) 
				{
					node.rotate(outPolyAngle);
				}
				node.setPosition(nextPos);
				sf::Vector2f position = node.getPosition();
				float angle = node.getRotation();
				_cos = std::cos(TurtleNode::PI * angle / 180.f);
				_sin = std::sin(TurtleNode::PI * angle / 180.f);
				nextPos.x = position.x + _cos * polySize;
				nextPos.y = position.y + _sin * polySize;
			}
			else 
			{
				node.move(dtf*absSpeed*_cos, dtf  *absSpeed* _sin);
			}
			if (countPassed == passedRequired) 
			{
				*done = true;
				if (!node.isPenUp)
				{
					node.lines.back()[countPassed].color = node.lineColor;
				}
				*done = true;
				return;
			}
		}
	};

	struct SetFastUpdate 
	{
		bool* done;
		bool flag;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			node.fastUpdateFlag = flag;
			*done = true;
		}
	};

	struct PushStateCommand
	{
		bool* done;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			TurtleNode::TurtleState state;
			sf::Vector2f pos = node.getPosition();
			state.x = pos.x;
			state.y = pos.y;
			state.angle = node.getRotation();
			node.states.push(state);
			*done = true;
		}
	};
	struct PopStateCommand
	{
		bool* done;
		void operator()(TurtleNode& node, const sf::Time& dt)
		{
			if (node.states.size() == 0) 
			{
				std::cerr << "Turtle has no saved states" << std::endl;
				*done = true;
				return;
			}
			TurtleNode::TurtleState state = node.states.top();
			node.states.pop();
			node.setPosition(state.x, state.y);
			node.setRotation(state.angle);
			*done = true;
		}
	};

	struct setHideTurtle 
	{
		bool* done;
		bool hideFlag;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			node.isHide = hideFlag;
			*done = true;
		};
	};

	struct SleepCommand 
	{
		float seconds;
		bool* done;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			if (seconds <= 0) 
			{
				*done = true;
				return;
			}
			seconds -= dt.asSeconds();
		}
	};
	struct FastMoveCommand 
	{
		float x;
		float y;
		bool* done;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			sf::Vector2f position = node.getPosition();
			sf::Vector2f nextPos;
			nextPos.x = position.x + x;
			nextPos.y = position.y + y;
			if (!node.isPenUp) 
			{
				
				sf::VertexArray line(sf::Lines, 2);
				line[0].color = node.lineColor;
				line[1].color = node.lineColor;
				line[0].position = position;
				line[1].position = nextPos;
				node.lines.push_back(line);
			}
			node.setPosition(nextPos);
			*done = true;
			return;
		}
	};
	struct MoveCommand 
	{
		float x;
		float y;
		float _cos;
		float _sin;
		float absSpeed;
		sf::Vector2f nextPos;
		bool init = false;
		bool* done;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			sf::Vector2f position = node.getPosition();
			if (!init)
			{
				absSpeed = node.speed;
				sf::Vector2f vect{ x,y };
				if (!node.isPenUp) 
				{
					sf::VertexArray line(sf::Lines, 2);
					line[0].color = node.lineColor;
					line[1].color = node.lineColor;
					line[0].position = position;
					line[1].position = position;
					node.lines.push_back(line);
				}
				nextPos = vect + position;
				float distance = std::sqrt(std::pow((position.x - nextPos.x), 2) 
					+ std::pow((position.y - nextPos.y), 2));
				_cos =  x / distance;
				_sin =  y / distance;
				init = true;
			}
			if (!node.isPenUp)
			{
				node.lines.back()[1].position = position;
			}
			float dtf = dt.asSeconds();
			if (std::pow((position.x - nextPos.x), 2) + std::pow((position.y - nextPos.y), 2) <= 10.f + std::pow(dtf * absSpeed,2)) 
			{
				if (!node.isPenUp)
				{
					node.lines.back()[1].position = nextPos;
				}
				node.setPosition(nextPos);
				*done = true;
				return;
			}
			else 
			{
				node.move(_cos*dtf*absSpeed, _sin*dtf* absSpeed);
			}
		}
	};

	struct SetRotationCommand 
	{
		float newAngle;
		bool* done;
		void operator() (TurtleNode& node, const sf::Time& dt) 
		{
			node.setRotation(newAngle);
			*done = true;
		}
	};
	struct SetPositionCommand 
	{
		bool* done;
		float x;
		float y;
		bool init = false;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			if (!init) 
			{
				if (!node.isPenUp)
				{
					sf::Vector2f currentPos = node.getPosition();
					sf::VertexArray line(sf::Lines, 2);
					line[0].position = currentPos;
					line[1].position.x = x;
					line[1].position.y = y;
					line[0].color = node.lineColor;
					line[1].color = node.lineColor;
					node.lines.push_back(line);
				}
				init = true;
			}

			node.setPosition(x, y);
			*done = true;
		}
	};

	struct LtCommand 
	{
		bool init = false;
		bool* done;
		float speed;
		float absSpeed;
		float nextAngle;
		float angle;
		void operator()(TurtleNode& node, const sf::Time& dt)
		{
			if (!init) 
			{
				absSpeed = std::abs(node.speed);
				speed = node.speed * (angle > 0 ? 1 : -1);
				nextAngle = node.getRotation() + angle;
				init = true;
			}
			float currentAngle = node.getRotation();
			float dtf = dt.asSeconds();
			if (std::abs(currentAngle - nextAngle) <= 1.f + dtf * absSpeed ||
				std::abs(currentAngle - nextAngle) >= 358.f - dtf * absSpeed && 
				std::abs(currentAngle - nextAngle) <= 362.f + dtf * absSpeed)
			{
				node.setRotation(nextAngle);
				*done = true;
				return;
			}
			node.rotate(speed * dtf);
		};
	};


	struct setSpeedCommand
	{
		bool* done;
		float speed;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			node.speed = speed;
			*done = true;
		}
	};
	struct FastFdCommand
	{
		bool* done;
		float distance;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			float currentAngle = node.getRotation();
			sf::Vector2f position = node.getPosition();
			sf::Vector2f nextPos{distance*std::cos(TurtleNode::PI*currentAngle/180.f) + position.x,distance*std::sin(TurtleNode::PI *currentAngle/ 180.f) + position.y};
			if (!node.isPenUp) 
			{
				sf::VertexArray line( sf::Lines,2);
				line[0].color = node.lineColor;
				line[1].color = node.lineColor;
				line[0].position = position;
				line[1].position = nextPos;
				node.lines.push_back(line);
			}
			node.setPosition(nextPos);
			*done = true;
			return;
		}
	};
	struct FdCommand
	{
		sf::Vector2f nextPos;
		bool* done;
		bool init = false;
		float speed;
		float distance;
		float _cos;
		float _sin;
		float absSpeed;
		
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{
			if (!init) 
			{
				absSpeed = std::abs(node.speed);
				speed = node.speed * (distance > 0 ? 1 : -1);
				float currentAngle = node.getRotation();
				sf::Vector2f currentPos = node.getPosition();
				this->_cos = std::cos(currentAngle*TurtleNode::PI / 180.f);
				this->_sin = std::sin(currentAngle * TurtleNode::PI / 180.f);
				nextPos.x = currentPos.x + _cos*distance;
				nextPos.y = currentPos.y + _sin*distance;
				if (!node.isPenUp) 
				{
					sf::VertexArray line(sf::Lines, 2);
					line[0].position = currentPos;
					line[1].position = currentPos;
					line[0].color = node.lineColor;
					line[1].color = node.lineColor;
					node.lines.push_back(line);
				}
				init = true;
			}

			auto position = node.getPosition();
			if (!node.isPenUp) 
			{
				node.lines.back()[1].position = position;
			}
			float dtf = dt.asSeconds();
			if (std::pow((position.x - nextPos.x), 2) + std::pow((position.y - nextPos.y), 2) <= 10.f + std::pow(dtf*absSpeed,2))
			{
				if (!node.isPenUp)
				{
					node.lines.back()[1].position = nextPos;
				}
				node.setPosition(nextPos);
				*done = true;
				return;
			}
			else
			{
				node.move(speed * dtf * _cos, speed * dtf * _sin);
			}
		};
	};

	void getPosition(sf::Vector2f& out);
	void getAngle(float& out);
	TurtleNode* turtle;
};

