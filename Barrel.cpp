#include "pch.h"
#include "Barrel.h"


Barrel::Barrel(const sf::Texture& texture, sf::Vector2f position) :
	MovingEntity(texture, position, EntityType::barrel, texture.getSize().y)
{
}


Barrel::~Barrel()
{
}


void Barrel::updateAnimation() {
	// TODO
}

void Barrel::hitGround() {

}