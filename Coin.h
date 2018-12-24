#pragma once
#include "Entity.h"

class Coin : public Entity
{
public:
	Coin(const sf::Texture&, sf::Vector2f);
	~Coin();
};

