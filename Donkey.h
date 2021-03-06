#pragma once
#include "Entity.h"

#define TIME_PER_ANIMATION 800

using namespace std;

enum DonkeyStates {
	front,
	takeRight,
	handBarrel,
	throwLeft,
	happy1,
	happy2,
	lose
};

class Donkey :
	public Entity
{
public:
	Donkey(const sf::Texture&, sf::Vector2f);
	~Donkey();

private:
	bool mThrowBarrel;
	bool mHappy;
	int mAnimationState;
	float mAnimationTime;

	void addBarrel();

public:
	void finish(bool playerWon);
	void updateAnimation(sf::Time elapsedTime);
};