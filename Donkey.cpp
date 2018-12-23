#include "pch.h"
#include "Donkey.h"


Donkey::Donkey(const sf::Texture& texture, sf::Vector2f position) : Entity(texture, position, EntityType::donkey)
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