#pragma once

using namespace std;

enum EntityType
{
	player,
	block,
	ladder,
	barrel,
	lady,
	donkey
};

class Entity
{
public:
	Entity() { };
	Entity(const sf::Texture& texture, sf::Vector2f position, const EntityType type);
	virtual ~Entity() { };
	
public:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Vector2u mSize;
	EntityType mType;

	bool mEnabled = true;

	// Enemy only
	bool mBarrelLeftToRight = true;
	int mTimes = 0;
};

