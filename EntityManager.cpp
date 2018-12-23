#include "pch.h"
#include "EntityManager.h"

std::vector<std::shared_ptr<Entity>> EntityManager::mEntities;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

std::shared_ptr<Entity> EntityManager::GetPlayer()
{
	for (std::shared_ptr<Entity> entity : EntityManager::mEntities)
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
