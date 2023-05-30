#include "Weapon.h"
#include <iostream>

Weapon::Weapon(Node* parentNode) : maxBullets(1000), Node(parentNode)
{
	weaponTextureRight = nullptr;
	weaponTextureLeft = nullptr;
	rateOfFire = 0.f;
	damage = 0.f;
	magazineSize = 0.f;
	reloadSpeed = 0.f;
	reloadTimer = 0.f;
	bulletSpawnTimer = 0.f;
	ammo = 0.f;
	startReloadTimer = false;
	keyHold = false;
}


void Weapon::initWeaponPosition(sf::Vector2f playerPosition)
{
	weaponPositionRight = sf::Vector2f(playerPosition.x + 40.f, playerPosition.y + 37.f);
	this->setLocalPosition(weaponPositionRight);
}

void Weapon::shoot(bool playerFacingRight, bool playerFacingLeft, Node* parentNode)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (ammo > 0) {
			if (playerFacingRight)
			{
				bullets.spawnBullet(playerFacingRight, playerFacingLeft, sf::Vector2f(weaponPositionRight.x + 40.f, weaponPositionRight.y), parentNode);
				ammo -= 1.f;
				bulletSpawnTimer = 0.f;
			}
			else if (playerFacingLeft)
			{
				bullets.spawnBullet(playerFacingRight, playerFacingLeft, weaponPositionLeft, parentNode);
				ammo -= 1.f;
				bulletSpawnTimer = 0.f;
			}
		}
	}
}

void Weapon::updateShooting(bool playerFacingRight, bool playerFacingLeft, float deltaTime, Node* parentNode)
{
	if (bullets.getBullets().size() < maxBullets)
	{
		if (bulletSpawnTimer >= rateOfFire)
		{
			shoot(playerFacingRight, playerFacingLeft, parentNode);

		}
		else
		{
			bulletSpawnTimer += 1.f;
		}
	}
	reload(deltaTime);
}

void Weapon::reload(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		startReloadTimer = true;
	}
	if (startReloadTimer)
	{
		reloadTimer += deltaTime;
	}
	if (reloadTimer >= reloadSpeed)
	{
		ammo = magazineSize;
		reloadTimer = 0.f;
		startReloadTimer = false;
	}
}


void Weapon::updateWeapon(const sf::RenderTarget* target, sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft, float deltaTime, Node* parentNode)
{
	initWeaponPosition(playerPosition);
	//std::cout << magazineSize << "      " << ammo << "      "<<reloadTimer<<std::endl;
	updateShooting(playerFacingRight, playerFacingLeft, deltaTime, parentNode);
	bullets.updateBullets(target);
}

void Weapon::renderWeapon(sf::RenderTarget* target)
{
	//bullets.renderBullets(target);
}

void Weapon::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(weaponSprite, transform);
}
