#include "Bullet.h"
#include <iostream>


Bullet::Bullet(bool playerFacingLeft, Node* parentNode) : Node(parentNode)
{
	bulletSize = sf::Vector2f(15.f, 5.f);
	velocity = sf::Vector2f(700.f, 0.f);
	initCollider(playerFacingLeft);
	initTexture(playerFacingLeft);
}

void Bullet::loadTexture()
{
	bulletTextureRight = new sf::Texture;
	if (!bulletTextureRight->loadFromFile("Textures/bullet_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Bullet::initTexture(bool playerFacingLeft)
{
	loadTexture();
	bulletSprite.setTexture(*bulletTextureRight);
	if (playerFacingLeft)
	{
		flipX();
		velocity.x = -velocity.x;
	}
	bulletSprite.setScale(sf::Vector2f(bulletSize.x / bulletTextureRight->getSize().x, bulletSize.y / bulletTextureRight->getSize().y));
}

void Bullet::initCollider(bool playerFacingLeft)
{
	collider.size = bulletSize;
	if (playerFacingLeft) {
		collider.offset.x -= bulletSize.x;
	}
}
	

void Bullet::initPosition(sf::Vector2f weaponPosition)
{
	float x = weaponPosition.x;
	float y = weaponPosition.y + 10.f;
	setLocalPosition(x,y);
}

const sf::Sprite& Bullet::getShape() const
{
	return bulletSprite;
}

Collider& Bullet::getCollider()
{
	return collider;
}

void Bullet::moveBullet(float deltaTime)
{
	move(velocity.x * deltaTime, velocity.y* deltaTime);
}

void Bullet::drawCollider(sf::RenderTarget* target)
{
	sf::RectangleShape colliderShape;
	colliderShape.setSize(collider.size);
	colliderShape.setPosition(getGlobalPosition() + collider.offset);
	target->draw(colliderShape);
}

void Bullet::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(bulletSprite, transform);
}