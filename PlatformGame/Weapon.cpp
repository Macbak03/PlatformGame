#include "Weapon.h"
#include <iostream>

Weapon::Weapon(Node* parentNode, Bullets& bullets) : Node(parentNode), bullets(bullets), fireBlast(this)
{
	weaponTexture = nullptr;
	rateOfFire = 0.f;
	damage = 0;
	magazineSize = 0;
	reloadTime = 0.f;
	reloadTimer = 0.f;
	bulletSpawnTimer = 0.f;
	ammo = 0;
	startReloadTimer = false;
}

void Weapon::scale()
{
	weaponSprite.setScale(sf::Vector2f(weaponSize.x / weaponTexture->getSize().x, weaponSize.y / weaponTexture->getSize().y));
}

void Weapon::initWeaponPosition(sf::Vector2f playerPosition)
{
	weaponPosition = sf::Vector2f(playerPosition.x + 30.f, playerPosition.y + 80.f);
	this->setLocalPosition(weaponPosition);
	fireBlast.initPosition(sf::Vector2f(weaponSize.x, -10.f));
}

void Weapon::shoot(bool playerFacingRight, bool playerFacingLeft, Node* parentNode)
{
	sf::Vector2f spawnPosition = getGlobalPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (ammo > 0) {
			if (playerFacingRight)
			{
				bullets.spawnBullet(playerFacingLeft, sf::Vector2f(spawnPosition.x + weaponSize.x, spawnPosition.y), parentNode, damage);
			}
			else if (playerFacingLeft)
			{
				bullets.spawnBullet(playerFacingLeft, sf::Vector2f(spawnPosition.x - weaponSize.x, spawnPosition.y), parentNode, damage);
			}
			ammo --;
			bulletSpawnTimer = 0.f;
			fireBlast.setDrawTimer(0.1f);
		}
	}
	
}

sf::Vector2f& Weapon::getSize()
{
	return weaponSize;
}
unsigned int Weapon::getAmmo()
{
	return ammo;
}

unsigned int Weapon::getMagazineSize()
{
	return magazineSize;
}

void Weapon::updateShooting(bool playerFacingRight, bool playerFacingLeft, float deltaTime, Node* parentNode)
{
	if (bullets.getBullets().size() < bullets.maxBullets)
	{
		if (bulletSpawnTimer >= rateOfFire && startReloadTimer == false)
		{
			shoot(playerFacingRight, playerFacingLeft, parentNode);

		}
		else
		{
			bulletSpawnTimer += deltaTime;
		}
	}
	reload(deltaTime);
	fireBlast.updateDrawTimer(deltaTime);
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
	if (reloadTimer >= reloadTime)
	{
		ammo = magazineSize;
		reloadTimer = 0.f;
		startReloadTimer = false;
	}
}

bool& Weapon::getWeaponReloadTimer()
{
	return startReloadTimer;
}

void Weapon::updateWeapon(const sf::RenderTarget* target, sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft, float deltaTime, Node* parentNode)
{
	initWeaponPosition(playerPosition);
	//std::cout << magazineSize << "      " << ammo << "      "<<reloadTimer<<std::endl;
	updateShooting(playerFacingRight, playerFacingLeft, deltaTime, parentNode);
	bullets.updateBullets(target, deltaTime);
}



void Weapon::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(weaponSprite, transform);
}
