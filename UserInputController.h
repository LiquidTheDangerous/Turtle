#include <queue>
#include "Command.h"
#ifndef _USERINPUTCONTROLLER_H_
#define _USERINPUTCONTROLLER_H_

class UserInputController
{
public:
	UserInputController(std::queue<Command>*);

	void handleEvent(const sf::Event& event, const sf::Time& dt);
	void handleInput(const sf::Time& dt);

private:
	std::queue<Command> * commads;
};


#endif // !_USERINPUTCONTROLLER_H_