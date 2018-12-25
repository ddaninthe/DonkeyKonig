#include "pch.h"
#include "EntityManager.h"

using namespace std;

shared_ptr<Entity> EntityManager::barrelDestructor;
shared_ptr<Mario> EntityManager::mPlayer;
shared_ptr<Donkey> EntityManager::mDonkey;
shared_ptr<Lady> EntityManager::mLady;
vector<shared_ptr<Block>> EntityManager::mBlocks;
vector<shared_ptr<Ladder>> EntityManager::mLadders;
vector<shared_ptr<Barrel>> EntityManager::mBarrels;
vector<shared_ptr<Coin>> EntityManager::mCoins;


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::draw(sf::RenderWindow & window) 
{
	window.draw(mLady->mSprite);
	window.draw(barrelDestructor->mSprite);

	for (shared_ptr<Entity> entity : EntityManager::mBlocks) {
		if (entity->mEnabled == false) {
			continue;
		}
		window.draw(entity->mSprite);
	}

	for (shared_ptr<Entity> entity : EntityManager::mLadders) {
		if (entity->mEnabled == false) {
			continue;
		}
		window.draw(entity->mSprite);
	}

	for (shared_ptr<Entity> entity : EntityManager::mCoins)	{
		if (entity->mEnabled == false) {
			continue;
		}
		window.draw(entity->mSprite);
	}

	for (shared_ptr<Entity> entity : EntityManager::mCoins) {
		if (entity->mEnabled == false) {
			continue;
		}
		window.draw(entity->mSprite);
	}

	for (shared_ptr<Entity> entity : EntityManager::mBarrels) {
		if (entity->mEnabled == false) {
			continue;
		}
		window.draw(entity->mSprite);
	}
	window.draw(mDonkey->mSprite);
	window.draw(mPlayer->mSprite);
}


// Factory Pattern
void EntityManager::addEntity(const EntityType type, sf::Vector2f position) 
{
	sf::Texture texture;

	switch (type) {
	case EntityType::coin: {
		texture.loadFromFile("Media/Textures/coin.png");
		shared_ptr<Coin> ptr = make_shared<Coin>(texture, position);
		EntityManager::mCoins.push_back(ptr);
		break;
	}
	case EntityType::barrel: {
		texture.loadFromFile("Media/Textures/barrel_rolling_1.png");
		shared_ptr<Barrel> ptr = make_shared<Barrel>(texture, position);
		EntityManager::mBarrels.push_back(ptr);
		break;
	}
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
		position.x = 205.f;
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
	if (!Game::isFinished()) player->updatePlayer(elapsedTime);

	EntityManager::mDonkey->updateAnimation(elapsedTime);

	for (shared_ptr<Barrel> barrel : EntityManager::getBarrels()) {
		barrel->updateAnimation(elapsedTime);

		if (Entity::checkCollision(*player, *barrel)) {
			// Game lost
			mDonkey->finish(false);
			Game::Score = -1;
		}

		if (Entity::checkCollision(*barrel, *barrelDestructor)) {
			barrel->reset();
		}
	}

	for (shared_ptr<Coin> coin : EntityManager::mCoins) {
		if (Entity::checkCollision(*player, *coin)) {
			coin->mSprite.setPosition(1000, 1000); // out of map
			Game::Score += 300;
		}
	}

	if (Entity::checkCollision(*player, *EntityManager::mLady)) {
		// Game won
		mDonkey->finish(true);
		EntityManager::mLady->ladySaved();
		Game::Score = 100000;
	}
}

void EntityManager::addRollingBarrel() {
	for (shared_ptr<Barrel> barrel : mBarrels) {
		if (!barrel->isDisplayed()) {
			barrel->appear();
			break;
		}
	}
}


// Getters
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

vector<shared_ptr<Coin>> EntityManager::getCoins()
{
	return EntityManager::mCoins;
}
