#pragma once

using namespace std;

enum EntityType
{
	player,
	block,
	echelle,
	barrel,
	lady,
	donkey
};

class Entity
{
public:
	Entity() { };
	~Entity() { };
	
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

