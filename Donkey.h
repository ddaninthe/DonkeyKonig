#pragma once
#include "Entity.h"

#define TIME_PER_ANIMATION 800

using namespace std;

enum DonkeyStates {
	front,
	takeRight,
	handBarrel,
	throwLeft
};

class Donkey :
	public Entity
{
public:
	Donkey(const sf::Texture&, sf::Vector2f);
	~Donkey();

private:
	bool mThrowBarrel;
	int mAnimationState;
	float mAnimationTime;

	void addBarrel();

public:
	void updateAnimation(sf::Time elapsedTime);
};