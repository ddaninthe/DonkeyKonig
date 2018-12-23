#pragma once
#include "Entity.h"

class Donkey :
	public Entity
{
public:
	Donkey(const sf::Texture&, sf::Vector2f);
	~Donkey();
};