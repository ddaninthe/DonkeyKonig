#include "pch.h"
#include "Ladder.h"


Ladder::Ladder(const sf::Texture& texture, sf::Vector2f position): Entity(texture, position, EntityType::ladder)
{
}


Ladder::~Ladder()
{
}
