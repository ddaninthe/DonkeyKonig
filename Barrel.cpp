#include "pch.h"
#include "Barrel.h"


Barrel::Barrel(const sf::Texture& texture, sf::Vector2f position) : Entity(texture, position, EntityType::barrel)
{
}


Barrel::~Barrel()
{
}
