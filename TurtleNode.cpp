#include "TurtleNode.h"
#include <iostream>
TurtleNode::TurtleNode():
	speed(100.f),
	lineColor(sf::Color::Black),
	body(&this->arrow),
	isPenUp(false),
	isHide(false),
	fastUpdateFlag(false)
{
	this->lines.push_back(sf::VertexArray(sf::Lines, 0));
	this->start_fill_iter = lines.end();
}
void TurtleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RenderStates parentTransformState;
	parentTransformState.transform *= this->getParentTransform();
	if (this->lines.size()) 
	{
		//parentTransformState.transform.;
		for (const sf::VertexArray& line : this->lines) 
		{
			
			target.draw(line,parentTransformState);
		}
	}
	if (this->fillZones.size()) 
	{
		for (const sf::VertexArray& zone : this->fillZones) 
		{
			target.draw(zone,parentTransformState);
		}
	}
	if (this->dots.size()) 
	{
		for (const TurtleDot& dot : this->dots) 
		{
			target.draw(dot,parentTransformState);
		}
	}
	if (!this->isHide) 
	{
		target.draw(*this->body, states);
	}
}

void TurtleNode::updateCurrent(const sf::Time& dt)
{
	if (this->fastUpdateFlag) 
	{
		this->fastUpdate(dt);
	}
	if (this->commands.empty())
	{
		return;
	}
	if (this->commands.front().done)
	{
		this->commands.pop_front();
		return;
	}
	this->commands.front()(*this, dt);
}

void TurtleNode::fastUpdate(const sf::Time& dt)
{
	if (this->commands.empty())
	{
		return;
	}
	TurtleCommand& top = this->commands.front();
	while (true)
	{
		this->commands.front()(*this, dt);
		if(!this->commands.front().done)
		{
			return;
		}
		this->commands.pop_front();
		if (this->commands.empty()) 
		{
			return;
		}
	}
}

float TurtleNode::getSpeed() const
{
	return this->speed;
}

void TurtleNode::setSpeed(const float& speed)
{
	this->speed = speed;
}

void TurtleNode::pushCommand(const TurtleCommand& command)
{
	//this->commands.pu
	this->commands.push_back(command);
}

TurtleNode::TurtleCommand& TurtleNode::lastPushed()
{
	return this->commands.back();
}

void TurtleNode::setBody(sf::Drawable* body)
{
	this->body = body;
}

sf::Drawable* TurtleNode::getBody()
{
	return this->body;
}

void TurtleNode::setLineColor(const sf::Color& color)
{
	this->lineColor = color;
}

sf::Color TurtleNode::getLineColor()
{
	return this->lineColor;
}

void TurtleNode::setPenUp(const bool& flag)
{
	this->isPenUp = flag;
}

void TurtleNode::attachCanvas(Canvas* canvas)
{
	this->canvas = canvas;
}
