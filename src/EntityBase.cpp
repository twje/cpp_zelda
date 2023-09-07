#include "EntityBase.h"

EntityBase::EntityBase(GroupManager& groupManager)
	: Sprite(groupManager)
{
}

EntityBase::EntityBase(GroupManager& groupManager, const std::shared_ptr<sf::Texture>& texture)
	: Sprite(groupManager, texture)
{
}