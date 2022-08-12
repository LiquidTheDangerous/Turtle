#include <SFML/Graphics.hpp>
#include "SceneNode.h"
#include <queue>
#include "UserInputController.h"
#include "TurtleNode.h"
#ifndef _CANVAS_H_
#define _CANVAS_H_
class TurtleController;
class Canvas
{
public:
	Canvas(const int& w, const int& h, const std::string& title = "Turlte");
	void run();
	void setBackgroundColor(const unsigned char& r = 255U, const unsigned char& g = 255U, const unsigned char& b = 255U, const unsigned char& alpha = 255U);
	void saveToFile(const std::string& fileName);
	TurtleController newTurtle(const std::string& name);
	TurtleController getTurtle(const std::string& name);
	bool isExistTurtle(const std::string& name);
private:
	void render();
	void processInput( sf::Event& event,const sf::Time& dt);
	void update(const sf::Time& dt);
	enum Layers 
	{
		background,
		front,
		layersCount
	};
	void buildCanvas();
	static const sf::Time TimePerFrame;
	std::list<TurtleNode*> turtles;
	std::queue<Command> commandQueue;
	std::vector<SceneNode*> layers;
	SceneNode root;
	sf::RenderWindow window;
	sf::View view;
	sf::Color bgColor;
	UserInputController userInputController;
};


#endif // !_CANVAS_H_