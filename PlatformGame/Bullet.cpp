#include "Bullet.h"
#include <iostream>


Bullet::Bullet(bool playerFacingRight, bool playerFacingLeft)
{
	velocity = sf::Vector2f(15.f, 0.f);
	initTexture(playerFacingRight, playerFacingLeft);
}

void Bullet::loadTexture()
{
	bulletTextureRight = new sf::Texture;
	if (!bulletTextureRight->loadFromFile("Textures/bullet_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
	bulletTextureLeft = new sf::Texture;
	if (!bulletTextureLeft->loadFromFile("Textures/bullet_left.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Bullet::initTexture(bool playerFacingRight, bool playerFacingLeft)
{
	loadTexture();
	if (playerFacingLeft)
	{
		bulletSprite.setTexture(*bulletTextureLeft);
	}
	if (playerFacingRight)
	{
		bulletSprite.setTexture(*bulletTextureRight);
	}
}

void Bullet::initPosition(sf::Vector2f weaponPosition)
{
	float x = weaponPosition.x;
	float y = weaponPosition.y;
	bulletSprite.setPosition(sf::Vector2f(x, y));
}

const sf::Sprite& Bullet::getShape() const
{
	return bulletSprite;
}

void Bullet::moveBullet(bool playerFacingRight, bool playerFacingLeft)
{
	if (playerFacingLeft)
	{
		bulletSprite.move(-velocity);
	}
	else if (playerFacingRight)
	{
		bulletSprite.move(velocity);
	}
}


void Bullet::renderBullet(sf::RenderTarget* target)
{
	target->draw(bulletSprite);
}
