#include "pch.h"
#include "Mario.h"
#include "EntityManager.h"

const float Mario::maxTimeInAir = 30;

Mario::Mario(const sf::Texture& texture, sf::Vector2f position) :
	mIsMovingLeft(false), mIsMovingRight(false), mIsMovingDown(false), mIsMovingUp(false), mJumping(false), mTimeInAir(0)
	, Entity(texture, position, EntityType::player)
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

bool Mario::checkBlocksCollision() {
	for (shared_ptr<Block> block : EntityManager::getBlocks()) {
		if (Entity::checkCollision(*this, *block)) {
			return true;
		}
	}

	return false;
}

// True if mario steps on a block
bool Mario::isOnBlock() {
	sf::FloatRect currentArea = mSprite.getGlobalBounds();

	sf::Vector2f bottomLeft = mSprite.getPosition();
	bottomLeft.y += currentArea.height;
	bottomLeft.x += currentArea.width - MARIO_WIDTH;

	sf::Vector2f bottomRight(bottomLeft);
	bottomRight.x += MARIO_WIDTH;

	for (shared_ptr<Block> block : EntityManager::getBlocks()) {
		sf::Sprite blockSprite = block->mSprite;
		sf::FloatRect blockArea = blockSprite.getGlobalBounds();
		
		// Mario is on block
		if (blockArea.contains(bottomLeft) || blockArea.contains(bottomRight)) {
			float yBlock = blockSprite.getPosition().y;
			// Avoid Mario steps within the block
			return yBlock + 2 > bottomLeft.y;
		}
	}

	return false;
}

void Mario::move(sf::Vector2f movement) {
	// TODO
}

void Mario::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	cout << (key == sf::Keyboard::Left ? "left" : "right") << ": " << isPressed << endl;

	if (!mIsMovingDown && (key == sf::Keyboard::Up || key == sf::Keyboard::Space)) {
		mIsMovingUp = isPressed;
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

	if (player->mJumping) {
		player->mTimeInAir++;
		player->mAnimationState = MarioStates::running1; // Jump animation
	}

	sf::Vector2f movement(0.f, 0.f);
	if (player->mTimeInAir < Mario::maxTimeInAir && (player->mIsMovingUp || player->mJumping)) {
		player->mJumping = true;
		movement.y -= Game::PlayerSpeed;
	}
	if (player->mIsMovingDown || player->mTimeInAir > Mario::maxTimeInAir) {
		// Can't go through bottom block
		if (player->isOnBlock()) {
			player->hitGround();
			cout << "Hitting: " << player->mAnimationState << endl;
			return;
		}
		movement.y += Game::PlayerSpeed;
	}
	if (player->mIsMovingLeft) {
		// Avoid exiting from screen
		if (playerPosition.x < MIN_X) {
			return;
		}
		else {
			movement.x -= Game::PlayerSpeed;
		}
	}
	if (player->mIsMovingRight) {
		// Avoid exiting from screen
		if (playerPosition.x > MAX_X) {
			return;
		}
		else {
			movement.x += Game::PlayerSpeed;
		}
	}
	player->mSprite.move(movement * elapsedTime.asSeconds());
}

void Mario::updateAnimation() {
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