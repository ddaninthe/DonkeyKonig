#include "pch.h"
#include "Donkey.h"


Donkey::Donkey(const sf::Texture& texture, sf::Vector2f position) : mOtherTextures(), Entity(texture, position, EntityType::donkey)
{
	mOtherTextures.push_back(sf::Texture());
	mOtherTextures.back().loadFromFile("Media/Textures/dk_throw_right.png");
	mOtherTextures.push_back(sf::Texture());
	mOtherTextures.back().loadFromFile("Media/Textures/dk_barrel.png");
	mOtherTextures.push_back(sf::Texture());
	mOtherTextures.back().loadFromFile("Media/Textures/dk_throw_left.png");
	mOtherTextures.push_back(sf::Texture());
	mOtherTextures.back().loadFromFile("Media/Textures/dk_happy_1.png");
	mOtherTextures.push_back(sf::Texture());
	mOtherTextures.back().loadFromFile("Media/Textures/dk_happy_2.png");
	mOtherTextures.push_back(sf::Texture());
	mOtherTextures.back().loadFromFile("Media/Textures/dk_loss.png");
}


Donkey::~Donkey()
{
}