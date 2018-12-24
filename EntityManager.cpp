#include "pch.h"
#include "EntityManager.h"

using namespace std;

shared_ptr<Mario> EntityManager::mPlayer;
shared_ptr<Donkey> EntityManager::mDonkey;
shared_ptr<Lady> EntityManager::mLady;
vector<shared_ptr<Block>> EntityManager::mBlocks;
vector<shared_ptr<Ladder>> EntityManager::mLadders;
vector<shared_ptr<Barrel>> EntityManager::mBarrels;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::draw(sf::RenderWindow& window) {
	
	window.draw(mLady->mSprite);
	window.draw(mDonkey->mSprite);

	for (shared_ptr<Block> entity : EntityManager::mBlocks)
	{
		if (entity->mEnabled == false)
		{
			continue;
		}

		window.draw(entity->mSprite);
	}

	for (shared_ptr<Ladder> entity : EntityManager::mLadders)
	{
		if (entity->mEnabled == false)
		{
			continue;
		}

		window.draw(entity->mSprite);
	}
	for (shared_ptr<Barrel> entity : EntityManager::mBarrels)
	{
		if (entity->mEnabled == false)
		{
			continue;
		}

		window.draw(entity->mSprite);
	}
	window.draw(mPlayer->mSprite);
}

shared_ptr<Mario> EntityManager::getPlayer() {
	return EntityManager::mPlayer;
}

shared_ptr<Lady> EntityManager::getLady() {
	return EntityManager::mLady;
}

shared_ptr<Donkey> EntityManager::getDonkey() {
	return EntityManager::mDonkey;
}

vector<shared_ptr<Block>> EntityManager::getBlocks()
{
	return EntityManager::mBlocks;
}

vector<shared_ptr<Ladder>> EntityManager::getLadders()
{
	return EntityManager::mLadders;
}

vector<shared_ptr<Barrel>> EntityManager::getBarrels()
{
	return EntityManager::mBarrels;
}


// Factory Pattern
void EntityManager::addEntity(const EntityType type, sf::Vector2f position) 
{
	sf::Texture texture;

	switch (type) {
	case EntityType::barrel: {
		texture.loadFromFile("Media/Textures/barrel_rolling_1.png");
		position.x = 500.f;
		position.y = BLOCK_SPACE - texture.getSize().y;
		shared_ptr<Barrel> ptr = make_shared<Barrel>(texture, position);
		EntityManager::mBarrels.push_back(ptr);
	}
		break;
	case EntityType::block: {
		texture.loadFromFile("Media/Textures/block.png");
		shared_ptr<Block> ptr = make_shared<Block>(texture, position);
		EntityManager::mBlocks.push_back(ptr);
		break;
	}
	case EntityType::donkey: {
		texture.loadFromFile("Media/Textures/dk.png");
		position.x = 530.f;
		position.y = BLOCK_SPACE - texture.getSize().y;
		shared_ptr<Donkey> ptr = make_shared<Donkey>(texture, position);
		EntityManager::mDonkey = ptr;
		break;
	}
	case EntityType::ladder: {
		texture.loadFromFile("Media/Textures/ladder.png");
		shared_ptr<Ladder> ptr = make_shared<Ladder>(texture, position);
		EntityManager::mLadders.push_back(ptr);
		break;
	}
	case EntityType::lady: {
		texture.loadFromFile("Media/Textures/lade_l_help.png");
		position.x = 100.f + 560.f;
		position.y = BLOCK_SPACE - texture.getSize().y;
		shared_ptr<Lady> ptr = make_shared<Lady>(texture, position);
		EntityManager::mLady = ptr;
		break;
	}
	case EntityType::player: {
		texture.loadFromFile("Media/Textures/mario_r_1.png");
		position.x = 100.f + 70.f;
		position.y = BLOCK_SPACE * 5 - texture.getSize().y;
		shared_ptr<Mario> ptr = make_shared<Mario>(texture, position);
		EntityManager::mPlayer = ptr;
		break;
	}
	default : 
		throw invalid_argument("Bad argument : " + type);
	}
}

void EntityManager::updateMovingEntities(sf::Time elapsedTime) {
	shared_ptr<Mario> player = EntityManager::getPlayer();
	player->updatePlayer(elapsedTime);

	/*for (shared_ptr<Barrel> barrel : EntityManager::getBarrels()) {
		barrel->updateBarrel(elapsedTime);

		if (Entity::checkCollison(*player, *barrel)) {
			// Game lost
			// TODO
		}
	}*/

	shared_ptr<Lady> lady = EntityManager::getLady();
	if (Entity::checkCollision(*player, *lady)) {
		// Game won
		lady->ladySaved();
		// TODO
	}
}