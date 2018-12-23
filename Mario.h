#pragma once
#include "Entity.h"

#define MARIO_WIDTH 27
#define ANIMATIONS_COUNT 3

enum MarioStates {
	standing, // 0
	running1,
	running2
};

using namespace std;

class Mario :
	public Entity
{
public:
	Mario(const sf::Texture&, sf::Vector2f);
	~Mario();

private:
	// Whether mario should look to right or left
	bool mStateRight; // true => right, false => left
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	bool mJumping;
	int mAnimationState;

	void updateAnimation();
	void hitGround();

public: 
	float mTimeInAir;

	static const float maxTimeInAir;

	static void updatePlayer(const sf::Time elapsedTime);
	void move(sf::Vector2f movement);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	bool checkBlocksCollision();
	bool isOnBlock();
};

