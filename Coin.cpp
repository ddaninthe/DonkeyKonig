#include "pch.h"
#include "Coin.h"


Coin::Coin(const sf::Texture& texture, sf::Vector2f position) : Entity(texture, position, EntityType::coin)
{
}


Coin::~Coin()
{
}
