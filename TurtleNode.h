#pragma once
#include "SceneNode.h"
#include "TurtleArrow.h"
#include "TurtleDot.h"
#include <stack>
#include <queue>


class TurtleNode : public SceneNode
{
public:
	TurtleNode();
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateCurrent(const sf::Time& dt)  override;
	void fastUpdate(const sf::Time& dt);
	float getSpeed() const;
	void setSpeed(const float& speed);
	struct TurtleCommand 
	{
		bool done;
		bool init;
		TurtleCommand() :
			done(false),
			init(true)
		{
			initFunc = [](TurtleNode&, const sf::Time& dt) {};
			pred = [](TurtleNode&, const sf::Time& dt) {return false; };
			exitFunc = pred;
			onExit = initFunc;
			actionIfPred = initFunc;
		}
		std::function<void(TurtleNode&, const sf::Time&)> initFunc;
		std::function<void(TurtleNode&, const sf::Time&)> action;
		std::function<bool(TurtleNode&, const sf::Time&)> pred;
		std::function<void(TurtleNode&, const sf::Time&)> actionIfPred;
		std::function<bool(TurtleNode&, const sf::Time&)> exitFunc;
		std::function<void(TurtleNode&, const sf::Time&)> onExit;
		void operator()(TurtleNode& node, const sf::Time& dt) 
		{

			if (!init) 
			{
				this->initFunc(node, dt);
				this->init = true;
			}
			if (exitFunc(node, dt)) 
			{
				onExit(node, dt);
				done = true;
				return;
			}
			if (!done) 
			{
				this->action(node, dt);
			}
			if (pred(node, dt)) 
			{
				actionIfPred(node, dt);
			}
		};
	};
	void pushCommand(const TurtleCommand& command);
	TurtleCommand& lastPushed();
	static float constexpr PI = 3.141592653589f;
	void setBody(sf::Drawable* body);
	sf::Drawable* getBody();
	void setLineColor(const sf::Color& color);
	sf::Color getLineColor();
	void setPenUp(const bool& flag);
private:
	TurtleArrow arrow;
	std::list<sf::VertexArray> lines;
	std::list<sf::VertexArray> fillZones;
	std::list<TurtleDot> dots;
	sf::Drawable* body;
	std::list<sf::VertexArray>::iterator start_fill_iter;
	std::list<TurtleCommand> commands;
	bool isPenUp;
	bool isHide;
	bool fastUpdateFlag;
	float speed;
	sf::Color lineColor;

	friend class TurtleController;
	struct TurtleState
	{
		float angle;
		float x;
		float y;
	};
	std::stack<TurtleState> states;
	
};

