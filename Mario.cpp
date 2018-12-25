#include "pch.h"
#include "Mario.h"
#include "EntityManager.h"

Mario::Mario(const sf::Texture& texture, sf::Vector2f position) : mJumping(false), mIsMovingUp(false), mTimeInAir(0)
	, MovingEntity(texture, position, EntityType::player, MARIO_WIDTH)
{
	mStateRight = true;
	mAnimationState = MarioStates::standing;
	
	// Right animations
	mTextures.push_back(make_shared<sf::Texture>());
	mTextures.back()->loadFromFile("Media/Textures/mario_r_2.png");
	mTextures.push_back(make_shared<sf::Texture>());
	mTextures.back()->loadFromFile("Media/Textures/mario_r_3.png");

	// Left animations
	for (int i = 0; i < ANIMATIONS_COUNT; i++) {
		mTextures.push_back(make_shared<sf::Texture>());
		mTextures.back()->loadFromFile("Media/Textures/mario_l_" + to_string(i + 1) + ".png");
	}
}


Mario::~Mario()
{
}

void Mario::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up || key == sf::Keyboard::Space) {
		mAnimationState = MarioStates::running1;
		if (!mIsMovingDown) {
			mIsMovingUp = isPressed;
		}
	}
	if (key == sf::Keyboard::Left) {
		mIsMovingLeft = isPressed;
		if (mStateRight && isPressed) {
			mStateRight = !mStateRight;
		}
	}
	else if (key == sf::Keyboard::Right) {
		mIsMovingRight = isPressed;
		if (!mStateRight && isPressed) {
			mStateRight = !mStateRight;
		}
	}

	updateAnimation();
}

void Mario::updatePlayer(const sf::Time elapsedTime) {
	shared_ptr<Mario> player = EntityManager::getPlayer();

	sf::Vector2f playerPosition = player->mSprite.getPosition();
	sf::Vector2f movement(0.f, 0.f);

	if (player->mJumping) {
		player->mTimeInAir++;
		player->mAnimationState = MarioStates::running1; // Jump animation
	} 
	// Gravity
	else if (!player->isOnBlock()) {
		movement.y += Game::PlayerSpeed;
	}

	// Ladder
	if (player->mIsMovingUp && isOnLadder()) {
		movement.y = 0 - Game::PlayerSpeed;
		player->mJumping = false;
		player->mTimeInAir = 0;
	}
	else if (player->mTimeInAir < MAX_AIR_TIME && (player->mIsMovingUp || player->mJumping)) {
		player->mJumping = true;
		movement.y -= Game::PlayerSpeed;
	}
	if (player->mIsMovingDown || player->mTimeInAir > MAX_AIR_TIME) {
		// Can't go through bottom block
		if (player->isOnBlock()) {
			hitGround();
			return;
		}
		movement.y += Game::PlayerSpeed;
	}
	if (player->mIsMovingLeft) {
		// Avoid exiting from screen
		if (playerPosition.x < MIN_X) {
			if (movement.x < 0) movement.x = 0.f;
		}
		else {
			movement.x -= Game::PlayerSpeed;
		}
	}
	if (player->mIsMovingRight) {
		// Avoid exiting from screen
		if (playerPosition.x > MAX_X) {
			if (movement.x > 0) movement.x = 0.f;
		}
		else {
			movement.x += Game::PlayerSpeed;
		}
	}
	this->move(movement * elapsedTime.asSeconds());
}

// Parameter not used here
void Mario::updateAnimation(const sf::Time ellapsedTime) {
	int indexTexture = mStateRight ? 0 : ANIMATIONS_COUNT;
	indexTexture += mAnimationState;
	mSprite.setTexture(*mTextures.at(indexTexture));
}

// Reset parameters when Mario hits/touches the ground
void Mario::hitGround() {
	mAnimationState = MarioStates::standing;
	mTimeInAir = 0;
	mJumping = false;

	updateAnimation();
}

bool Mario::isOnLadder() {
	for (shared_ptr<Ladder> ladder : EntityManager::getLadders()) {
		if (Entity::checkCollision(*this, *ladder)) {
			return true;
		}
	}
	return false;
}

void Mario::move(sf::Vector2f movement) {
	mSprite.move(movement);

	// TODO: fix shivers
	if (movement.y == 0 && movement.x != 0) {
		if (checkBlocksCollision() && isOnBlock()) {
			mSprite.move(sf::Vector2f(0.f, -1.2f));
		}
	}
}