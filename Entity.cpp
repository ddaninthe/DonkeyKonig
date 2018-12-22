#include "pch.h"
#include "Entity.h"

Entity::Entity(const sf::Texture& texture, sf::Vector2f position, const EntityType type) {
	mTexture = texture;
	mSprite = sf::Sprite(mTexture);
	mSprite.setPosition(position);
	mSize = mTexture.getSize();
	mType = type;
}