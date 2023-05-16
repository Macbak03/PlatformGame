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
	if (playerFacingRight)
	{
		bulletFacingLeft = false;
		bulletSprite.setTexture(*bulletTextureRight);
		bulletFacingRight = true;
	}
	if (playerFacingLeft)
	{
		bulletFacingRight = false;
		bulletSprite.setTexture(*bulletTextureLeft);
		bulletFacingLeft = true;
	}
	bulletSprite.setScale(sf::Vector2f(0.1f, 0.1f));
}

void Bullet::initPosition(sf::Vector2f weaponPosition)
{
	float x = weaponPosition.x;
	float y = weaponPosition.y + 10.f;
	bulletSprite.setPosition(sf::Vector2f(x, y));
}

const sf::Sprite& Bullet::getShape() const
{
	return bulletSprite;
}

void Bullet::moveBullet()
{
	if (bulletFacingRight)
	{
		bulletSprite.move(velocity);
	}
	else if (bulletFacingLeft)
	{
		bulletSprite.move(-velocity);
	}
}


void Bullet::renderBullet(sf::RenderTarget* target)
{
	target->draw(bulletSprite);
}
