#pragma once
#include "MovingEntity.h"

#define BARREL_TIME 700

enum BarrelStates {
	rolling1,
	rolling2,
	rolling3,
	rolling4,
	falling
};

class Barrel : public MovingEntity
{
public:
	Barrel(const sf::Texture&, sf::Vector2f);
	~Barrel();

private:
	static const float mSpriteX;
	float mSpriteY;
	bool mVisible;
	int mTime; // in ms
	float mFallingTime;

protected:
	void move(sf::Vector2f movement);
	void hitGround();

public:
	void updateAnimation(const sf::Time ellapsedTime);
	void appear();
	bool isDisplayed();
	void reset();
};

