#pragma once
#include <SFML/Graphics.hpp>
#include "SceneNode.h"
#include <queue>
#include "UserInputController.h"
#include "TurtleNode.h"
class Canvas
{
public:
	Canvas(const int& w, const int& h, const std::string& title = "Turlte");
	void run();
	void setBackgroundColor(const unsigned char& r = 255U, const unsigned char& g = 255U, const unsigned char& b = 255U, const unsigned char& alpha = 255U);
	TurtleNode* turlte;
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

	std::queue<Command> commandQueue;
	std::vector<SceneNode*> layers;
	SceneNode root;
	sf::RenderWindow window;
	sf::View view;
	sf::Color bgColor;
	UserInputController userInputController;
};

