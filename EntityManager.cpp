#include "pch.h"
#include "EntityManager.h"

using namespace std;

vector<shared_ptr<Entity>> EntityManager::mEntities;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

shared_ptr<Entity> EntityManager::getPlayer()
{
	for (shared_ptr<Entity> entity : EntityManager::mEntities)
	{
		if (entity->mEnabled == false)
		{
			continue;
		}

		if (entity->mType == EntityType::player)
		{
			return entity;
		}
	}

	return nullptr;
}

void EntityManager::addEntity(const EntityType type, sf::Vector2f position) 
{
	sf::Texture texture;

	cout << type << endl;

	switch (type) {
	case EntityType::barrel : 
		break;
	case EntityType::block :
		break;
	case EntityType::donkey :
		break;
	case EntityType::ladder :
		break;
	case EntityType::lady: {
		texture.loadFromFile("Media/Textures/lade_l_help.png");
		position.x = 100.f + 560.f;
		position.y = BLOCK_SPACE * 1 - texture.getSize().y;
		shared_ptr<Entity> ptr = make_shared<Lady>(texture, position);
		EntityManager::mEntities.push_back(ptr);
		break;
	}
	case EntityType::player: {
		texture.loadFromFile("Media/Textures/mario_r_1.png");
		position.x = 100.f + 70.f;
		position.y = BLOCK_SPACE * 5 - texture.getSize().y;
		shared_ptr<Entity> ptr = make_shared<Mario>(texture, position);
		EntityManager::mEntities.push_back(ptr);
		break;
	}
	default : 
		throw invalid_argument("Bad argument : " + type);
	}
}