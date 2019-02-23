#pragma once

#define MAX_BARREL 15
#define LADDER_COUNT 4
#define COIN_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f
#define MIN_X 165
#define MAX_X 700
#define CHEAT_CODE "MARIO"

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
	static int Life;
	static bool isFinished();
	static bool Restart;

private:
	static bool GameFinished;
	static const sf::Time	TimePerFrame;
	string mInput;

	sf::RenderWindow	mWindow;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;
	sf::Text	mScoreText;
	sf::Text	mLifeText;
	sf::Text	mGameText; // Lost or won
	sf::Text	mRetryText;
	sf::Text	mCheatCode; // ON or OFF

	std::size_t	mStatisticsNumFrames;

	vector<shared_ptr<Entity>> decorations;
	sf::Texture	mTextureWeapon;
	sf::Sprite	mWeapon;
};