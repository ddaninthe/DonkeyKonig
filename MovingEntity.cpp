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


bool MovingEntity::checkBlocksCollision() {
	for (shared_ptr<Block> block : EntityManager::getBlocks()) {
		if (Entity::checkCollision(*this, *block)) {
			return true;
		}
	}

	return false;
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
			return yBlock + 3 > bottomLeft.y;
		}
	}

	return false;
}

void MovingEntity::hitGround() {
	switch (mType) {
	case EntityType::player: {
		Mario & player = static_cast<Mario&>(*this);
		Mario::hitGround(make_shared<Mario>(player));
		break;
	}
	case EntityType::barrel:
		cout << "Not yet implemented" << endl;
		break;
	default:
		cout << "Unknown MovingEntity: " << mType << endl;
	}
}

void MovingEntity::move(sf::Vector2f movement) {
	mSprite.move(movement);

	// TODO: fix shivers
	if (movement.y == 0 && movement.x != 0) {
		if (checkBlocksCollision() && isOnBlock()) {
			mSprite.move(sf::Vector2f(0.f, -1.2f));
			hitGround();
		}
	}
}