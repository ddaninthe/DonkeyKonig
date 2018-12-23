#pragma once
#include "Entity.h"

#define MARIO_WIDTH 30

class Mario :
	public Entity
{
public:
	Mario(const sf::Texture&, sf::Vector2f);
	~Mario();

public: 
	bool checkBlocksCollision();
	bool isOnBlock();
	void move(sf::Vector2f movement);
};

