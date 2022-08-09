#include "UserInputController.h"

UserInputController::UserInputController(std::queue<Command>* commands):
	commads(commands)
{
}

void UserInputController::handleEvent(const sf::Event& event, const sf::Time& dt)
{
}

void UserInputController::handleInput(const sf::Time& dt)
{
}
