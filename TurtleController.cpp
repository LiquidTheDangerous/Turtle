#include "TurtleController.h"

TurtleController::TurtleController():
	turtle(nullptr)
{
}

TurtleController::TurtleController(TurtleNode* turtle):
	turtle(turtle)
{
}

void TurtleController::attachTurtle(TurtleNode* turtle)
{
	this->turtle = turtle;
}

void TurtleController::forward(const float& distance)
{
	this->fd(distance);
}

void TurtleController::fastForward(const float& distance)
{
	TurtleNode*& turtle = this->turtle;
	FastFdCommand command;
	command.distance = distance;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::backward(const float& distance)
{
	this->fd(-distance);
}

void TurtleController::fastBackward(const float& distance)
{
	this->fastForward(-distance);
}

void TurtleController::fd(const float& distance)
{
	FdCommand command;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());

	command.distance = distance;
	command.done = &turtle->lastPushed().done;

	turtle->lastPushed().action = command;
}

void TurtleController::lt(const float& angle)
{
	LtCommand command;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.angle = angle;
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::fastLeft(const float& angle)
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	bool& done = turtle->lastPushed().done;
	turtle->lastPushed().action =
		[angle, &done](TurtleNode& node, const sf::Time& dt)
	{
		node.rotate(angle);
		done = true;
	};
}

void TurtleController::right(const float& angle)
{
	this->lt(-angle);
}

void TurtleController::fastRight(const float& angle)
{
	this->fastLeft(-angle);
}

void TurtleController::rt(const float& angle)
{
	this->lt(-angle);
}

void TurtleController::setSpeed(const float& speed)
{
	TurtleNode*& turtle = this->turtle;
	setSpeedCommand command;
	command.speed = std::abs(speed);
	command.speed = (command.speed < 10.f ? 10.f : command.speed);
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::left(const float& angle)
{
	this->lt(angle);
}

void TurtleController::setPosition(const float& x, const float& y)
{
	SetPositionCommand command;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.x = x;
	command.y = y;
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::setRotation(const float& angle)
{
	TurtleNode*& turtle = this->turtle;
	SetRotationCommand command;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.newAngle = angle;
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::move(const float& x, const float& y)
{
	TurtleNode*& turtle = this->turtle;
	MoveCommand command;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	command.x = x;
	command.y = y;
	turtle->lastPushed().action = command;
}

void TurtleController::moveRad(const float& distance, const float& angle)
{
	this->move(distance*std::cos(TurtleNode::PI*angle/180.f),distance*std::sin(TurtleNode::PI * angle / 180.f));
}

void TurtleController::fastMove(const float& x, const float& y)
{
	TurtleNode*& turtle = this->turtle;
	FastMoveCommand command;
	command.x = x;
	command.y = y;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::fastMoveRad(const float& distance, const float& angle)
{
	this->fastMove(distance * std::cos(TurtleNode::PI * angle / 180.f), distance * std::sin(TurtleNode::PI * angle / 180.f));
}

void TurtleController::dot(const float& radius, const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& alpha)
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	auto* done = &turtle->lastPushed().done;
	std::list<TurtleDot>* dotList = &turtle->dots;
	turtle->lastPushed().action =
		[done,radius,r,g,b,alpha,dotList](TurtleNode& node, const sf::Time& dt)
	{
		TurtleDot dot(radius, sf::Color(r, g, b, alpha));
		dot.setPosition(node.getPosition());
		dotList->push_back(dot);
		*done = true;
	};
}

void TurtleController::clearDots()
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	bool* done = &turtle->lastPushed().done;
	auto* dotList = &turtle->dots;
	turtle->lastPushed().action =
		[done, dotList](TurtleNode& node, const sf::Time& dt)
	{
		dotList->clear();
		*done = true;
	};
}

void TurtleController::circle(const float& radius, const float& angle,const bool& left, const int& point_count)
{
	
	TurtleNode*& turtle = this->turtle;
	DrawCircle command;
	command.radius = radius;
	command.angleSegment = angle;
	command.pointCount = point_count;
	command.left = (left == 1? 1 : -1);
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::plotFunction(std::function<float(const float& x)> func, const float& start, const float& end, const float& step, const float& wx, const float& wy)
{
	TurtleNode*& turtle = this->turtle;
	FuncPlot command;
	command.func= func;
	command.start = start;
	command.end = end;
	command.step = step;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::logPosition(std::ostream& stream)
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	auto &done = turtle->lastPushed().done;
	turtle->lastPushed().action =
		[&stream,&done](TurtleNode& node, const sf::Time& dt)
	{
		auto position = node.getPosition();
		stream << '(' << position.x << " : " << position.y << ')' << std::endl;
		done = true;
	};
}

void TurtleController::penUp()
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	bool* done = &turtle->lastPushed().done;
	turtle->lastPushed().action =
		[done](TurtleNode& node, const sf::Time& dt)
	{
		node.setPenUp(true);
		*done = true;
	};
}

void TurtleController::penDown()
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	bool* done = &turtle->lastPushed().done;
	turtle->lastPushed().action =
		[done](TurtleNode& node, const sf::Time& dt)
	{
		node.setPenUp(false);
		*done = true;
	};
}

void TurtleController::showTurtle()
{
	setHideTurtle command;
	command.hideFlag = false;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::hideTurtle()
{
	setHideTurtle command;
	command.hideFlag = true;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;

}

void TurtleController::setFastUpdate(const bool& flag)
{
	SetFastUpdate command;
	command.flag = flag;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::beginFill()
{
	BeginFill command;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::endFill()
{
	EndFill command;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::sleep(const float& seconds)
{
	SleepCommand command;
	command.seconds = seconds;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::logAngle(std::ostream& stream)
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	auto& done = turtle->lastPushed().done;
	turtle->lastPushed().action =
		[&stream, &done](TurtleNode& node, const sf::Time& dt)
	{
		auto angle = node.getRotation();
		stream << angle << std::endl;
		done = true;
	};
}

void TurtleController::pushState()
{
	PushStateCommand command;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::popState()
{
	PopStateCommand command;
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	command.done = &turtle->lastPushed().done;
	turtle->lastPushed().action = command;
}

void TurtleController::clearLines()
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	bool* done = &turtle->lastPushed().done;
	auto* linesList = &turtle->lines;
	turtle->lastPushed().action =
		[done, linesList](TurtleNode& node, const sf::Time& dt)
	{
		linesList->erase(std::next(linesList->begin()), linesList->end());
		*done = true;
	};
	
}

void TurtleController::setLinesColor(const unsigned char& r, const unsigned char& g, const unsigned char& b,const unsigned char& alpha )
{
	TurtleNode*& turtle = this->turtle;
	auto* arrow = &turtle->arrow;
	
	this->turtle->lineColor.r = r;
	this->turtle->lineColor.g = g;
	this->turtle->lineColor.b = b;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	auto& done = turtle->lastPushed().done;
	turtle->lastPushed().action = 
		[&done,r,g,b,alpha,arrow](TurtleNode& node,const sf::Time& dt) 
	{
		arrow->setColor(sf::Color(r, g, b, alpha));
		node.setLineColor(sf::Color(r,g,b,alpha));
		done = true;
	};

}

void TurtleController::getPosition(sf::Vector2f& out)
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	auto& done = turtle->lastPushed().done;
	turtle->lastPushed().action =
		[&out,turtle,&done](TurtleNode&, const sf::Time& dt)
	{
		out = turtle->getPosition();
		done = true;
	};
}

void TurtleController::getAngle(float& out)
{
	TurtleNode*& turtle = this->turtle;
	turtle->pushCommand(TurtleNode::TurtleCommand());
	auto& done = turtle->lastPushed().done;
	turtle->lastPushed().action =
		[&out, &turtle, &done](TurtleNode&, const sf::Time& dt)
	{
		out = turtle->getRotation();
		done = true;
	};
}
