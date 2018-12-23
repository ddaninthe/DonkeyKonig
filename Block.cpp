#include "pch.h"
#include "Block.h"


Block::Block(const sf::Texture& texture, sf::Vector2f position) : Entity(texture, position, EntityType::block)
{
}


Block::~Block()
{
}
