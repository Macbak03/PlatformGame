#include "Weapon.h"
#include <iostream>

Weapon::Weapon() : maxBullets(1000)
{
	weaponTextureRight = nullptr;
	weaponTextureLeft = nullptr;
	rateOfFire = 0.f;
	damage = 0.f;
	ammoSize = 0.f;
	bulletSpawnTimer = 0.f;
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
		bullets.spawnBullet(playerFacingRight, playerFacingLeft, weaponPositionRight);
		bulletSpawnTimer = 0.f;
	}
}

void Weapon::updateShooting(bool playerFacingRight, bool playerFacingLeft)
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

void Weapon::updateWeapon(const sf::RenderTarget* target, sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft)
{
	initWeaponPosition(playerPosition, playerFacingRight, playerFacingLeft);
	rotateWeapon(playerFacingRight, playerFacingLeft);
	std::cout << bulletSpawnTimer << std::endl;
	updateShooting(playerFacingRight, playerFacingLeft);
	bullets.updateBullets(target);
}

void Weapon::renderWeapon(sf::RenderTarget* target)
{
	bullets.renderBullets(target);
	target->draw(weaponSprite);
}

