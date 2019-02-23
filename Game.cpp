#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"

#include <SFML/Audio.hpp>


const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
int Game::Score;
int Game::Life;
bool Game::GameFinished;
bool Game::Restart;

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mFont()
	, mStatisticsText()
	, mScoreText()
	, mLifeText()
	, mGameText()
	, mCheatCode()
	, mRetryText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mInput("")
{
	mWindow.setFramerateLimit(160);

	// Initialize static values
	Game::Score = 0;
	Game::Life = 3;
	Game::GameFinished = false;
	Game::Restart = false;

	// Draw blocks

	sf::Vector2f position;
	for (int i = 0; i < BLOCK_COUNT_X; i++)
	{
		for (int j = 0; j < BLOCK_COUNT_Y; j++)
		{
			if (j == 0 && i != 0) {
				// Upper plateform
				position = sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));
				
			} else if (j % 2 == 0) {
				// Don't draw first block
				if (i == 0 && j != BLOCK_COUNT_Y - 1) { 
					continue;
				}

				position = sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1) - i);
			}
			else {
				// Don't draw last block
				if (i == BLOCK_COUNT_X - 1) {
					continue;
				}
				position = sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1) + i);
			}

			EntityManager::addEntity(EntityType::block, position);
		}
	}

	// Draw Echelles
	float sizeBlock = EntityManager::getBlocks().front()->mSprite.getGlobalBounds().height;
	for (int i = 0; i < LADDER_COUNT; i++)
	{
		sf::Vector2f position(110.f + 70.f * (i % 2 == 0 ? 2 : BLOCK_COUNT_X - 1), 0.f + BLOCK_SPACE * (i + 1) + sizeBlock);
		EntityManager::addEntity(EntityType::ladder, position);
	}

	//Draw Coins
	for (int i = 0; i < COIN_COUNT; i++)
	{
		sf::Vector2f position(110.f + 70.f * (i % 2 == 0 ? 3 : BLOCK_COUNT_X - 2), 30.f + BLOCK_SPACE * (i + 1) + sizeBlock);
		EntityManager::addEntity(EntityType::coin, position);
	}
	
	// Draw Mario
	EntityManager::addEntity(EntityType::player);

	// Draw Lady
	EntityManager::addEntity(EntityType::lady);

	// Draw Donkey Kong
	EntityManager::addEntity(EntityType::donkey);

	// Draw barrels
	for (int i = 0; i < MAX_BARREL; i++) {
		EntityManager::addEntity(EntityType::barrel);
	}


	// Standing barrel
	sf::Texture texture;
	texture.loadFromFile("Media/Textures/barrel_standing.png");
	position = sf::Vector2f(610.f, BLOCK_SPACE - texture.getSize().y);
	decorations.push_back(make_shared<Entity>(texture, position, EntityType::barrel));

	// Barrel Destructor
	sf::Texture textureDestructor;
	textureDestructor.loadFromFile("Media/Textures/barrel_destructor.png");
	position = sf::Vector2f(170.f, BLOCK_SPACE * 5 - textureDestructor.getSize().y);
	EntityManager::barrelDestructor = make_shared<Entity>(textureDestructor, position, EntityType::barrel);


	mFont.loadFromFile("Media/Sansation.ttf");
	// Draw Statistic Font 
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	// Draw Score
	mScoreText.setString("Score: 0");
	mScoreText.setFont(mFont);
	mScoreText.setPosition(210.f, 10.f);
	mScoreText.setCharacterSize(30);

	// Draw Life
	mLifeText.setString("Life: 3");
	mLifeText.setFont(mFont);
	mLifeText.setPosition(365.f, 10.f);
	mLifeText.setCharacterSize(30);

	// Cheat code ON or OFF
	mCheatCode.setString("Cheat Code OFF");
	mCheatCode.setFont(mFont);
	mCheatCode.setPosition(620.f, 20.f);
	mCheatCode.setCharacterSize(15);
	mCheatCode.setFillColor(sf::Color(255, 16, 0));

	// Victory or Game Over
	mGameText.setFont(mFont);
	mGameText.setPosition(230.f, 230.f);
	mGameText.setCharacterSize(100);
	mGameText.setFillColor(sf::Color(255, 16, 0));

	// Retry Game
	mRetryText.setFont(mFont);
	mRetryText.setPosition(300.f, 400.f);
	mRetryText.setCharacterSize(30);

	// Sound
	sf::SoundBuffer buffer;
	buffer.loadFromFile("Media/Sounds/Music.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.setVolume(50);
	sound.play();
	
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	const sf::Time ellapsedTime;

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		shared_ptr<Mario> player = EntityManager::getPlayer();
		switch (event.type)
		{
		case sf::Event::KeyPressed:				
			switch (event.key.code)
			{
			case sf::Keyboard::M: 
				mInput += 'M';
				break;
			case sf::Keyboard::A:
				if (mInput.length() == 1) {
					mInput += 'A';
				}
				else mInput = "";
				break;
			case sf::Keyboard::R:
				if (mInput.length() == 2) {
					mInput += 'A';
				}
				else mInput = "";
				break;				
			case sf::Keyboard::I:
				if (mInput.length() == 3) {
					mInput += 'A';
				}
				else mInput = "";
				break;				
			case sf::Keyboard::O:
				
				if (mInput.length() == 4) {
					if (EntityManager::cheatCodeEnabled == false) {
						EntityManager::cheatCodeEnabled = true;
						mCheatCode.setFillColor(sf::Color(17, 255, 73));
						mCheatCode.setString("Cheat Code ON");
					}
					else {
						EntityManager::cheatCodeEnabled = false;
						mCheatCode.setFillColor(sf::Color(255, 16, 0));
						mCheatCode.setString("Cheat Code OFF");

					}
					mInput = "";
				}
				else mInput = "";
				break;
			case sf::Keyboard::Enter:
				if (isFinished()) {
					Game::Restart = true;
					mWindow.close();
				}
				break;
			default:
				mInput = "";
			}
			if (Score >= 0) {
				player->handlePlayerInput(event.key.code, true);
			}
			break;
		case sf::Event::KeyReleased:
			if (Score >= 0) {
				player->handlePlayerInput(event.key.code, false);
			}
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	EntityManager::updateMovingEntities(elapsedTime);
}

void Game::render()
{
	mWindow.clear();

	for (shared_ptr<Entity> decoration : decorations) {
		mWindow.draw(decoration->mSprite);
	}

	EntityManager::draw(mWindow);

	mWindow.draw(mStatisticsText);
	mWindow.draw(mScoreText);
	mWindow.draw(mLifeText);
	mWindow.draw(mGameText);
	mWindow.draw(mCheatCode);
	mWindow.draw(mRetryText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (Game::Life == 0) {
		mGameText.setString("GAME OVER");
		mLifeText.setString("Life: 0");
		mRetryText.setString("Press 'Enter' to Retry");
		GameFinished = true;
	}
	else if (Score >= 100000) {
		mGameText.setString("VICTORY");
		mRetryText.setString("Press 'Enter' to Retry");
		mGameText.setFillColor(sf::Color(17, 255, 73));
		GameFinished = true;
	}
	else {
		mScoreText.setString("Score: " + to_string(Game::Score));
		mLifeText.setString("Life: " + to_string(Game::Life));
	}

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

bool Game::isFinished() {
	return GameFinished;
}