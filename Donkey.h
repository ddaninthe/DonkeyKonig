#pragma once
#include "Entity.h"

using namespace std;

class Donkey :
	public Entity
{
public:
	Donkey(const sf::Texture&, sf::Vector2f);
	~Donkey();

public:
	vector<sf::Texture> mOtherTextures;
};