#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(160);

	sf::Texture test;

	// Draw blocks

	_TextureBlock.loadFromFile("Media/Textures/Block.png");
	_sizeBlock = _TextureBlock.getSize();

	for (int i = 0; i < BLOCK_COUNT_X; i++)
	{
		for (int j = 0; j < BLOCK_COUNT_Y; j++)
		{
			_Block[i][j].setTexture(_TextureBlock);
			if (j == 0) {
				// Upper plateform
				_Block[i][j].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));
				
			} else if (j % 2 == 0) {
				// Don't draw first block
				if (i == 0 && j != BLOCK_COUNT_Y - 1) { 
					continue;
				}

				_Block[i][j].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1) - i);
			}
			else {
				// Don't draw last block
				if (i == BLOCK_COUNT_X - 1) {
					continue;
				}
				_Block[i][j].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1) + i);
			}

			std::shared_ptr<Entity> se = std::make_shared<Entity>();
			se->mSprite = _Block[i][j];
			se->mType = EntityType::block;
			se->mSize = _TextureBlock.getSize();
			EntityManager::mEntities.push_back(se);
		}
	}

	// Draw Echelles

	_TextureEchelle.loadFromFile("Media/Textures/Echelle.png");

	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		_Echelle[i].setTexture(_TextureEchelle);
		_Echelle[i].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + _sizeBlock.y);

		std::shared_ptr<Entity> se = std::make_shared<Entity>();
		se->mSprite = _Echelle[i];
		se->mType = EntityType::ladder;
		se->mSize = _TextureEchelle.getSize();
		EntityManager::mEntities.push_back(se);
	}


	// Draw Mario
	/*shared_ptr<Entity> player = make_shared<Entity>();
	player->mTexture = sf::Texture();

	sf::Sprite spriteMario;
	sf::Vector2f posMario;

	player->mTexture.loadFromFile("Media/Textures/mario_r_1.png");
	spriteMario.setTexture(player->mTexture);

	posMario.x = 100.f + 70.f;
	posMario.y = BLOCK_SPACE * 5 - player->mTexture.getSize().y;

	spriteMario.setPosition(posMario);

	player->mSprite = spriteMario;
	player->mType = EntityType::player;
	player->mSize = player->mTexture.getSize();
	EntityManager::mEntities.push_back(player);*/

	EntityManager::addEntity(EntityType::player);


	// Draw Donkey Kong

	EntityManager::addEntity(EntityType::donkey);
	_TextureDonkey[0].loadFromFile("Media/Textures/dk.png");
	_TextureDonkey[1].loadFromFile("Media/Textures/dk_throw_right.png");
	_TextureDonkey[2].loadFromFile("Media/Textures/dk_barrel.png");
	_TextureDonkey[3].loadFromFile("Media/Textures/dk_throw_left.png");
	_TextureDonkey[4].loadFromFile("Media/Textures/dk_happy_1.png");
	_TextureDonkey[5].loadFromFile("Media/Textures/dk_happy_2.png");
	_TextureDonkey[6].loadFromFile("Media/Textures/dk_loss.png");
	/*
	dkTexture.loadFromFile("Media/Textures/dk.png");
	_sizeDk = dkTexture.getSize();
	_DonkeyKong.setTexture(dkTexture);
	sf::Vector2f posDk;
	posDk.x = 580.f;
	posDk.y = BLOCK_SPACE * 1 - _sizeDk.y;

	_DonkeyKong.setPosition(posDk);

	std::shared_ptr<Entity> dk = std::make_shared<Entity>();
	dk->mSprite = _DonkeyKong;
	dk->mType = EntityType::donkey;
	dk->mSize = dkTexture.getSize();
	EntityManager::mEntities.push_back(dk);
	*/

	// Draw Lady
	// TODO


	// Initialize barrels
	_TextureBarrel[0].loadFromFile("Media/Textures/barrel_front.png");
	for (int i = 1; i < 5; i++) {
		_TextureBarrel[i].loadFromFile("Media/Textures/barrel_rolling_" + to_string(i) + ".png");
	}
	

	// Draw Statistic Font 

	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
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
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f playerPosition = EntityManager::getPlayer()->mSprite.getPosition();

	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp) {
		movement.y -= PlayerSpeed;
	}
	if (mIsMovingDown) {
		movement.y += PlayerSpeed;
	}
	if (mIsMovingLeft) {
		// Avoid exiting from screen
		if (playerPosition.x < MIN_X) {
			return;
		}
		else {
			movement.x -= PlayerSpeed;
		}
	}
	if (mIsMovingRight) {
		// Avoid exiting from screen
		if (playerPosition.x > MAX_X) {
			return;
		}
		else {
			movement.x += PlayerSpeed;
		}
	}

	for (std::shared_ptr<Entity> entity : EntityManager::mEntities)
	{
		if (entity->mEnabled == false)
		{
			continue;
		}

		if (entity->mType != EntityType::player)
		{
			continue;
		}

		entity->mSprite.move(movement * elapsedTime.asSeconds());
	}
}

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : EntityManager::mEntities)
	{
		if (entity->mEnabled == false)
		{
			continue;
		}

		mWindow.draw(entity->mSprite);
	}

	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}

	//
	// Handle collision
	//

	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{
		// Handle collision weapon enemies
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::Down)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::Left)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;

	if (key == sf::Keyboard::Space)
	{

	}
}

void Game::addBarrel() {
	// TODO
	/*
	sf::Sprite sprite;
	sprite.setTexture(_TextureBarrel[1]);
	sprite.setPosition(100.f, 100.f);

	_Barrels.push_back(sprite);*/
}