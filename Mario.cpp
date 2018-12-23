#include "pch.h"
#include "Mario.h"
#include "EntityManager.h"


Mario::Mario(const sf::Texture& texture, sf::Vector2f position) : Entity(texture, position, EntityType::player)
{
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

bool Mario::isOnBlock() {
	sf::FloatRect currentArea = mSprite.getGlobalBounds();

	sf::Vector2f bottomLeft = mSprite.getPosition();
	bottomLeft.y += currentArea.height;

	sf::Vector2f bottomRight(bottomLeft);
	bottomRight.x += MARIO_WIDTH;

	for (shared_ptr<Block> block : EntityManager::getBlocks()) {
		sf::FloatRect blockArea = block->mSprite.getGlobalBounds();

		if (blockArea.contains(bottomLeft) || blockArea.contains(bottomRight)) {
			return true;
		}
	}

	return false;
}

void Mario::move(sf::Vector2f movement) {
	// TODO
}
