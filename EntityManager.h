#pragma once
#include "Mario.h"
#include "Lady.h"
#include "Donkey.h"
#include "Block.h"
#include "Ladder.h"
#include "Game.h"

using namespace std;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

private: 
	static shared_ptr<Mario> mPlayer;
	static shared_ptr<Donkey> mDonkey;
	static shared_ptr<Lady> mLady;
	static vector<shared_ptr<Block>> mBlocks;
	static vector<shared_ptr<Ladder>> mLadders;

public:
	static void draw(sf::RenderWindow& window);
	static void updateMovingEntities(sf::Time elapsedTime);

	static shared_ptr<Mario> getPlayer();
	static shared_ptr<Donkey> getDonkey();
	static shared_ptr<Lady> getLady();
	static vector<shared_ptr<Block>> getBlocks();
	static vector<shared_ptr<Ladder>> getLadders();
	//static vector<shared_ptr<Barrel>> getBarrels();

	static void addEntity(const EntityType, sf::Vector2f position = sf::Vector2f(0, 0));
};

