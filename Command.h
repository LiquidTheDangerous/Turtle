
#include <string>
#include <SFML/Graphics.hpp>
#include <functional>
class SceneNode;
#ifndef _COMMAND_H_
#define _COMMAND_H_
class Command
{
public:
	using categoryType = unsigned int;
	using actionType = std::function<void(SceneNode&, const sf::Time&)>;
	
	Command(actionType action,const categoryType& category);
	Command(actionType action, const std::string& name);
	Command(actionType action, const std::string&& name);

	void operator=(const actionType& action);

	void setAction(actionType& action);
	actionType getAction() const;

	void setCategory(const categoryType& category);
	categoryType getCategory() const;

	void setName(const std::string& name);
	void setName(std::string&& name);
	std::string getName() const;

	void operator()(SceneNode& node, const sf::Time& dt) const;

private:
	actionType action;
	categoryType category;
	std::string name;
};

#endif