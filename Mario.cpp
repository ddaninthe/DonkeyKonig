#include "pch.h"
#include "Mario.h"


Mario::Mario(const sf::Texture& texture, sf::Vector2f position) : Entity(texture, position, EntityType::player)
{
}


Mario::~Mario()
{
}
