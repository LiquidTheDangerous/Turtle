#include "Canvas.h"
#include <iostream>
const sf::Time Canvas::TimePerFrame = sf::seconds(1.f / 60.f);
Canvas::Canvas(const int& w, const int& h, const std::string &title):
	window(sf::VideoMode(w,h),title),
	layers(this->layersCount),
	view(window.getDefaultView()),
	userInputController(&this->commandQueue)
{
	this->turlte = new TurtleNode();
	this->buildCanvas();
	//this->view.move(-w / 2, -h / 2);
	
	//this->view.rotate(180);
	//this->view.zoom(-1);
	//this->view.setCenter(w / 2, h / 2);
	sf::FloatRect viewport = this->view.getViewport();
	//viewport.height = -viewport.height;
	//this->view.setViewport(viewport);
	//std::cout << viewport.left << ' ' << viewport.top;
	//this->view.rotate(180);
}

void Canvas::render()
{
	this->window.clear(this->bgColor);

	this->window.setView(this->view);
	this->window.draw(this->root);

	this->window.display();
}

void Canvas::processInput( sf::Event& event,const sf::Time& dt)
{
	while (this->window.pollEvent(event)) 
	{
		if (event.type == sf::Event::Closed)
		{
			this->window.close();
		}
		this->userInputController.handleEvent(event, dt);
	}
	this->userInputController.handleInput(dt);

}

void Canvas::update(const sf::Time& dt)
{
	this->root.update(dt);
}

void Canvas::setBackgroundColor(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& alpha)
{
	this->bgColor = sf::Color(r, g, b, alpha);
}

void Canvas::run()
{
	sf::Clock clock;
	sf::Time time = sf::Time::Zero;
	sf::Event event;
	while (window.isOpen()) 
	{
		time += clock.restart();;
		while (time > Canvas::TimePerFrame) 
		{
			time -= Canvas::TimePerFrame;
			this->processInput(event, Canvas::TimePerFrame);
			this->update(Canvas::TimePerFrame);
		}
		this->render();
	}
}

void Canvas::buildCanvas()
{
	for (int i = 0; i < this->layersCount; ++i) 
	{
		SceneNode::SceneNodePtr newNode(new SceneNode());
		layers[i] = newNode.get();
		this->root.attachChild(std::move(newNode));
	}
	//Normalization coordinat system.
	layers[Layers::front]->setPosition(this->window.getSize().x / 2.f, this->window.getSize().y / 2.f);
	this->layers[Layers::front]->setScale(1, -1);

	SceneNode::SceneNodePtr t(this->turlte);
	this->layers[Layers::front]->attachChild(std::move(t));

}
