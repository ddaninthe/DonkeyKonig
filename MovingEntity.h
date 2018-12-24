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
	// Whether Entity should go to right or left
	bool mStateRight; // true => right, false => left
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;

	int mAnimationState;

	virtual void updateAnimation();

	bool isOnBlock();
};

