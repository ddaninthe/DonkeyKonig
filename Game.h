#pragma once

#define LADDER_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f
#define BARREL_TEXTURE_COUNT 5
#define MIN_X 165
#define MAX_X 700

#include "Entity.h"

using namespace std;

class Game
{
public:
	Game();
	~Game() { };
	void run();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();
	void addBarrel();
	void updateStatistics(sf::Time elapsedTime);

public:
	static const float		PlayerSpeed;

private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;

	std::size_t	mStatisticsNumFrames;

	sf::Texture _TextureBarrel[BARREL_TEXTURE_COUNT];
	vector<sf::Sprite> _Barrels;
	sf::Texture	_TextureBlock;
	sf::Sprite	_Block[BLOCK_COUNT_X][BLOCK_COUNT_Y];
	sf::Texture	_TextureWeapon;
	sf::Sprite	_Weapon;
	sf::Vector2u _sizeBlock;
	sf::Vector2u _sizeDk;
};

