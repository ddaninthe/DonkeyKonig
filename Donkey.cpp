#include "pch.h"
#include "Donkey.h"


Donkey::Donkey(const sf::Texture& texture, sf::Vector2f position) : Entity(texture, position, EntityType::donkey)
{
}


Donkey::~Donkey()
{
}