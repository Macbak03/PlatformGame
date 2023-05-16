#include "Weapon.h"

Weapon::Weapon()
{
	weaponTextureRight = nullptr;
	weaponTextureLeft = nullptr;
	rateOfFire = 0.f;
	damage = 0.f;
	ammoSize = 0.f;
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
	shoot(playerFacingRight, playerFacingLeft);
	bullets.updateBullets(target, playerFacingRight, playerFacingLeft, weaponPositionRight);
}

void Weapon::renderWeapon(sf::RenderTarget* target)
{
	target->draw(weaponSprite);
}

