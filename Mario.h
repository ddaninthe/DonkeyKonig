#pragma once
#include "MovingEntity.h"

#define MARIO_WIDTH 27
#define ANIMATIONS_COUNT 3
#define MAX_AIR_TIME 30

enum MarioStates {
	standing,
	running1,
	running2
};

using namespace std;

class Mario :
	public MovingEntity
{
public:
	Mario(const sf::Texture&, sf::Vector2f);
	~Mario();

private:
	float mTimeInAir;
	bool mJumping;
	bool mIsMovingUp;

public:
	void updatePlayer(const sf::Time elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	bool isOnLadder();

	// Inherited methods
	void hitGround();
	void updateAnimation(const sf::Time ellapsedTime = sf::Time());
	void move(sf::Vector2f movement);
};

