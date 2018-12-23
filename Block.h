#pragma once
#include "Entity.h"

class Block : public Entity
{
public:
	Block(const sf::Texture&, sf::Vector2f);
	~Block();
};

