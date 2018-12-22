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
	sf::Sprite m_sprite;
	sf::Vector2u m_size;
	EntityType m_type;
	bool m_enabled = true;

	// Enemy only
	bool m_bLeftToRight = true;
	int m_times = 0;
};

