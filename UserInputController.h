#pragma once
#include <queue>
#include "Command.h"
class UserInputController
{
public:
	UserInputController(std::queue<Command>*);

	void handleEvent(const sf::Event& event, const sf::Time& dt);
	void handleInput(const sf::Time& dt);

private:
	std::queue<Command> * commads;
};

