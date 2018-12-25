#include "pch.h"
#include "Barrel.h"
#include "Game.h"

const float Barrel::mSpriteX = 505.f;

Barrel::Barrel(const sf::Texture& texture, sf::Vector2f position) :
	mSpriteY(BLOCK_SPACE - texture.getSize().y)
	, mVisible(false)
	, mTime(0)
	, mFallingTime(0)
	, MovingEntity(texture, sf::Vector2f(1000.f, 1000.f), EntityType::barrel, round(texture.getSize().y))
{
	mStateRight = false;
	mAnimationState = BarrelStates::rolling1;

	// Load textures
	for (int i = 1; i < 4; i++) { // 4 = amount of rolling images
		mTextures.push_back(make_shared<sf::Texture>());
		mTextures.back()->loadFromFile("Media/Textures/barrel_rolling_" + to_string(i + 1) + ".png");
	}

	mTextures.push_back(make_shared<sf::Texture>());
	mTextures.back()->loadFromFile("Media/Textures/barrel_front.png");
}


Barrel::~Barrel()
{
}


void Barrel::updateAnimation(const sf::Time ellapsedTime) {
	if (mVisible) {
		sf::Vector2f movement(0.f, 0.f);

		mTime += ellapsedTime.asMilliseconds();

		if (!isOnBlock()) {
			mFallingTime += ellapsedTime.asMilliseconds();
			movement.y += 1.f * Game::PlayerSpeed;
			if (mFallingTime < 200) movement.x = (mStateRight ? 1.f : -1.f) * Game::PlayerSpeed;
			move(movement * ellapsedTime.asSeconds());

			if (mFallingTime > 200) {
				//mSprite.setTexture(*mTextures.at(BarrelStates::falling));
				mAnimationState = BarrelStates::falling;

				if (isOnBlock()) {
					hitGround();
				}
			}
		}
		else {
			movement.x = (mStateRight ? 1.f : -1.f) * Game::PlayerSpeed;

			if (mTime > BARREL_TIME) {
				if (mStateRight) {
					mAnimationState++;
					if (mAnimationState > BarrelStates::rolling4) {
						mAnimationState = BarrelStates::rolling1;
					}
				}
				else {
					mAnimationState--;
					if (mAnimationState < BarrelStates::rolling1) {
						mAnimationState = BarrelStates::rolling4;
					}
				}
				mSprite.setTexture(*mTextures.at(mAnimationState));
			}
			move(movement * ellapsedTime.asSeconds());
		}
		mTime %= BARREL_TIME;
	}
}

void Barrel::hitGround() {
	mStateRight = !mStateRight;
	mAnimationState = BarrelStates::rolling1;
	mSprite.setTexture(*mTextures.at(mAnimationState));
	mTime = 0;
	mFallingTime = 0;
}

bool Barrel::isDisplayed() {
	return mVisible;
}

// Called when barrel reach the end
void Barrel::reset() {
	mStateRight = false;
	mVisible = false;
	mSprite.setPosition(1000.f, 1000.f); // Out of window
	mTime = 0;
	mFallingTime = 0;
}

void Barrel::appear() {
	mSprite.setPosition(mSpriteX, mSpriteY);
	mVisible = true;
}

void Barrel::move(sf::Vector2f movement) {
	mSprite.move(movement);

	// TODO: fix shivers
	if (movement.y == 0 && movement.x != 0) {
		if (checkBlocksCollision() && isOnBlock()) {
			mSprite.move(sf::Vector2f(0.f, -1.2f));
		}
		mFallingTime = 0;
	}
}