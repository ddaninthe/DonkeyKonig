#pragma once
#include "Entity.h"

class Ladder : public Entity
{
public:
	Ladder(const sf::Texture&, sf::Vector2f);
	~Ladder();
};

