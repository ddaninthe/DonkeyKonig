#include "pch.h"
#include "Lady.h"


Lady::Lady(const sf::Texture& texture, sf::Vector2f position) : Entity(texture, position, EntityType::lady)
{
	mTextures.push_back(make_shared<sf::Texture>(sf::Texture()));
	mTextures.back()->loadFromFile("Media/Textures/lady_l_love.png");
}


// Update lady's sprite
void Lady::ladySaved() {
	mSprite.setTexture(*mTextures.back());
}