#pragma once
#include "Entity.h"

class Mario :
	public Entity
{
public:
	Mario(const sf::Texture&, sf::Vector2f);
	~Mario();
};

