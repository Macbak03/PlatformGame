#include "Weapon.h"
#include <iostream>

Weapon::Weapon() : maxBullets(1000)
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


void Weapon::initWeaponPosition(sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft)
{
	weaponPositionRight = sf::Vector2f(playerPosition.x + 40.f, playerPosition.y + 37.f);
	if(playerFacingRight)
	{
		weaponSprite.setPosition(weaponPositionRight);
	}
	weaponPositionLeft = sf::Vector2f(playerPosition.x - 15.f, playerPosition.y + 37.f);
	if (playerFacingLeft)
	{
		weaponSprite.setPosition(weaponPositionLeft);
	    weaponSprite.setTexture(*weaponTextureLeft);
	}
}

void Weapon::shoot(bool playerFacingRight, bool playerFacingLeft)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (ammo > 0) {
			if (playerFacingRight)
			{
				bullets.spawnBullet(playerFacingRight, playerFacingLeft, sf::Vector2f(weaponPositionRight.x + 40.f, weaponPositionRight.y));
				ammo -= 1.f;
				bulletSpawnTimer = 0.f;
			}
			else if (playerFacingLeft)
			{
				bullets.spawnBullet(playerFacingRight, playerFacingLeft, weaponPositionLeft);
				ammo -= 1.f;
				bulletSpawnTimer = 0.f;
			}
		}
	}
}

void Weapon::updateShooting(bool playerFacingRight, bool playerFacingLeft, float deltaTime)
{
	if (bullets.getBullets().size() < maxBullets)
	{
		if (bulletSpawnTimer >= rateOfFire)
		{
			shoot(playerFacingRight, playerFacingLeft);

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


void Weapon::rotateWeapon(bool playerFacingRight, bool playerFacingLeft)
{
	if(playerFacingLeft)
	{
		weaponSprite.setTexture(*weaponTextureLeft);
		weaponSprite.setPosition(weaponPositionLeft);
	}
	else if (playerFacingRight)
	{
		weaponSprite.setTexture(*weaponTextureRight);
		weaponSprite.setPosition(weaponPositionRight);
	}
}

void Weapon::updateWeapon(const sf::RenderTarget* target, sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft, float deltaTime)
{
	initWeaponPosition(playerPosition, playerFacingRight, playerFacingLeft);
	rotateWeapon(playerFacingRight, playerFacingLeft);
	std::cout << magazineSize << "      " << ammo << "      "<<reloadTimer<<std::endl;
	updateShooting(playerFacingRight, playerFacingLeft, deltaTime);
	bullets.updateBullets(target);
}

void Weapon::renderWeapon(sf::RenderTarget* target)
{
	bullets.renderBullets(target);
	target->draw(weaponSprite);
}

