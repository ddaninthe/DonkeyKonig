#include "pch.h"
#include "Donkey.h"
#include "EntityManager.h"


Donkey::Donkey(const sf::Texture& texture, sf::Vector2f position) :
	mThrowBarrel(false), mAnimationState(DonkeyStates::front), mAnimationTime(0)
	, Entity(texture, position, EntityType::donkey)
{
	mTextures.push_back(make_shared<sf::Texture>());
	mTextures.back()->loadFromFile("Media/Textures/dk_throw_right.png");
	mTextures.push_back(make_shared<sf::Texture>());
	mTextures.back()->loadFromFile("Media/Textures/dk_barrel.png");
	mTextures.push_back(make_shared<sf::Texture>());
	mTextures.back()->loadFromFile("Media/Textures/dk_throw_left.png");
	mTextures.push_back(make_shared<sf::Texture>());
	mTextures.back()->loadFromFile("Media/Textures/dk_happy_1.png");
	mTextures.push_back(make_shared<sf::Texture>());
	mTextures.back()->loadFromFile("Media/Textures/dk_happy_2.png");
	mTextures.push_back(make_shared<sf::Texture>());
	mTextures.back()->loadFromFile("Media/Textures/dk_loss.png");
}


Donkey::~Donkey()
{
}

void Donkey::updateAnimation(sf::Time elapsedTime) {
	mAnimationTime += elapsedTime.asMilliseconds();

	if (mAnimationTime > TIME_PER_ANIMATION) {
		if (mAnimationState == DonkeyStates::throwLeft) {
			mAnimationState = DonkeyStates::front;
			mAnimationTime = 0;
		}
		else {
			mAnimationState++;
		}
		mAnimationTime -= TIME_PER_ANIMATION;
	}

	mSprite.setTexture(*mTextures.at(mAnimationState));

	if (mAnimationState == DonkeyStates::throwLeft) {
		if (mThrowBarrel) {
			addBarrel();
		}
	}
	else {
		mThrowBarrel = true;
	}
}

void Donkey::addBarrel() {
	mThrowBarrel = false;
	cout << "Roll Roll Roll" << endl;
	//EntityManager::addEntity(EntityType::barrel);
}