#include "pch.h"
#include "Entity.h"

Entity::Entity(const sf::Texture& texture, sf::Vector2f position, const EntityType type) {
	mTexture = texture;
	mSprite = sf::Sprite(mTexture);
	mSprite.setPosition(position);
	mSize = mTexture.getSize();
	mType = type;
}

bool Entity::checkCollision(const Entity e1, const Entity e2) {
		sf::FloatRect areaE1 = e1.mSprite.getGlobalBounds();
	sf::FloatRect areaE2 = e2.mSprite.getGlobalBounds();

	return areaE1.intersects(areaE2);
}