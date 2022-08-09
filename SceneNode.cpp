#include "SceneNode.h"
#include <algorithm>
#include <assert.h>
void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	this->drawCurrent(target, states);
	for (auto &child : this->childs)
	{
		child->draw(target, states);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SceneNode::attachChild(SceneNodePtr child)
{
	child->parent = this;
	this->childs.push_back(std::move(child));
}

SceneNode::SceneNodePtr SceneNode::detachChild(SceneNode& childNode)
{
	auto iter = std::find_if(this->childs.begin(), this->childs.end(),
		[&childNode](SceneNodePtr& node)
		{
			return node.get() == &childNode;
		});
	assert(iter != this->childs.end());
	SceneNodePtr res = std::move(*iter);
	res->parent = nullptr;
	this->childs.erase(iter);
	return res;

}

int SceneNode::getSize() const
{
	return this->childs.size();
}

void SceneNode::setName(const std::string& name)
{
	this->name = name;
}

void SceneNode::setName(std::string&& name)
{
	this->name = std::move(name);
}

std::string SceneNode::getName() const
{
	return this->name;
}

SceneNode::categoryType SceneNode::getCategory() const
{
	return this->category;
}

void SceneNode::setCategory(const categoryType& category)
{
	this->category = category;
}

sf::Transform SceneNode::getWorldTransform() const
{
	auto result = sf::Transform::Identity;

	const SceneNode* current = this;

	while (current) 
	{
		result *= current->getTransform();
		current = current->parent;
	}

	return result;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	//this->get
	return this->getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getParentTransform() const
{
	if (!this->parent) 
	{
		throw std::logic_error("Node has not parent");
	}
	return this->parent->getTransform();
}

void SceneNode::onCommand(const CommandType& command, const sf::Time& dt)
{
	if (this->getCategory() & command.getCategory()) 
	{
		command(*this, dt);
	}
	else if (this->name == command.getName()) 
	{
		command(*this, dt);
	}
	for (auto& child : this->childs) 
	{
		child->onCommand(command, dt);
	}
}

void SceneNode::update(const sf::Time& dt)
{
	this->updateCurrent(dt);
	for (auto& child : this->childs) 
	{
		child->update(dt);
	}
}

void SceneNode::updateCurrent(const sf::Time& dt)
{
}
