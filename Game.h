#pragma once

#define MAX_BARREL 15
#define LADDER_COUNT 4
#define COIN_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f
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
	void updateStatistics(sf::Time elapsedTime);

public:
	static const float		PlayerSpeed;
	static int Score;
	static bool isFinished();

private:
	static bool GameFinished;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow	mWindow;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;
	sf::Text	mScoreText;
	sf::Text	mGameText; // Lost or won

	std::size_t	mStatisticsNumFrames;

	vector<shared_ptr<Entity>> decorations;
	sf::Texture	mTextureWeapon;
	sf::Sprite	mWeapon;
};

