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
	static bool checkCollision(const Entity e1, const Entity e2);

	// Storing Textures here throws Destructor Exception when game is closed
	vector<shared_ptr<sf::Texture>> mTextures;
	sf::Sprite mSprite;
	sf::Vector2u mSize;
	EntityType mType;

	bool mEnabled = true;

	// Enemy only
	bool mBarrelLeftToRight = true;
	int mTimes = 0;
};
