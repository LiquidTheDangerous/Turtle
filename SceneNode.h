#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Command.h"

class SceneNode:
	public sf::Drawable,
	public sf::Transformable,
	public sf::NonCopyable
{
public:
	using SceneNodePtr = std::unique_ptr<SceneNode>;
	using container_t = std::list<SceneNodePtr>;
	using categoryType = unsigned int;
	using CommandType = Command;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final override;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	void attachChild(SceneNodePtr child);

	SceneNodePtr detachChild(SceneNode& node);

	int getSize() const;

	void setName(const std::string& name);

	void setName(std::string&& name);

	std::string getName() const;

	categoryType getCategory() const;

	void setCategory(const categoryType& category);

	sf::Transform getWorldTransform() const;

	sf::Vector2f getWorldPosition() const;

	sf::Transform getParentTransform() const;

	void onCommand(const CommandType& command, const sf::Time& dt);

	void update(const sf::Time& dt);
	virtual void updateCurrent(const sf::Time& dt);

protected:
	SceneNode* parent;
	container_t childs;
	categoryType category;
	std::string name;
};

