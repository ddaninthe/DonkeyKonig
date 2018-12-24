#pragma once
#include "Entity.h"

class Barrel : public Entity
{
public:
	Barrel(const sf::Texture&, sf::Vector2f);
	~Barrel();
};

