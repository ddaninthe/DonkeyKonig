#pragma once
#include "MovingEntity.h"

class Barrel : public MovingEntity
{
public:
	Barrel(const sf::Texture&, sf::Vector2f);
	~Barrel();

public:

protected:
	void hitGround();
	void updateAnimation();
};

