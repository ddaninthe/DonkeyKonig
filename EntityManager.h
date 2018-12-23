#pragma once
#include "Mario.h"
#include "Lady.h"
#include "Game.h"

using namespace std;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

public:
	static vector<shared_ptr<Entity>> mEntities;
	static shared_ptr<Entity> getPlayer();
	static void addEntity(const EntityType, sf::Vector2f position = sf::Vector2f(0, 0));
};

