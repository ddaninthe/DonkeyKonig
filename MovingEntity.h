#pragma once
#include "Entity.h"

// Class for Barrels And Mario (And DK?)
class MovingEntity :
	public Entity
{
public:
	MovingEntity(const sf::Texture& texture, sf::Vector2f position, EntityType type, float const &entityWidth);
	virtual ~MovingEntity() { };

private:
	const float mEntityWidth;

protected:
	bool checkBlocksCollision();
	// Whether Entity should go to right or left
	bool mStateRight; // true => right, false => left
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;

	int mAnimationState;

	virtual void hitGround() = 0;

	virtual void move(sf::Vector2f movement) = 0;
	bool isOnBlock();

public:
	virtual void updateAnimation(const sf::Time elapsedTime) = 0;

};

