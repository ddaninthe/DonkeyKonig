#include "pch.h"
#include "MovingEntity.h"
#include "EntityManager.h"


MovingEntity::MovingEntity(const sf::Texture& texture, sf::Vector2f position, EntityType type, float const &entityWidth) :
	mIsMovingLeft(false), mIsMovingRight(false), 
	mIsMovingDown(false),
	mEntityWidth(entityWidth)
	, Entity(texture, position, type) 
{
}


// True if Entity steps on a block
bool MovingEntity::isOnBlock() {
	sf::FloatRect currentArea = mSprite.getGlobalBounds();

	sf::Vector2f bottomLeft = mSprite.getPosition();
	bottomLeft.y += currentArea.height;
	bottomLeft.x += currentArea.width - mEntityWidth;

	sf::Vector2f bottomRight(bottomLeft);
	bottomRight.x += mEntityWidth;

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