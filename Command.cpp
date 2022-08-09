#include "Command.h"

Command::Command(actionType action, const categoryType& category): 
	action(action),
	category(category)
{
}

Command::Command(actionType action, const std::string& name):
	action(action),
	name(name)
	
{
}

Command::Command(actionType action, const std::string&& name):
	action(action),
	name(std::move(name))
{
}

void Command::operator=(const actionType& action)
{
	this->action = action;
}

void Command::setAction(actionType& action)
{
	this->action = action;
}

Command::actionType Command::getAction() const
{
	return this->action;
}

void Command::setCategory(const categoryType& category)
{
	this->category = category;
}

Command::categoryType Command::getCategory() const
{
	return this->category;
}

void Command::setName(const std::string& name)
{
	this->name = name;
}

void Command::setName(std::string&& name)
{
	this->name = std::move(name);
}

std::string Command::getName() const
{
	return this->name;
}

void Command::operator()(SceneNode& node, const sf::Time& dt) const
{
	this->action(node, dt);
}
