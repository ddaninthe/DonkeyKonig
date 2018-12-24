#pragma once
#include "Entity.h"

class Lady :
	public Entity
{
public:
	Lady(const sf::Texture&, sf::Vector2f);
	~Lady() { };

public: 
	void ladySaved();
};
