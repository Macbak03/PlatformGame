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

void Weapon::shoot()
{
}


void Weapon::rotateWeapon(bool playerFacingRight, bool playerFacingLeft)
{
	if(playerFacingLeft)
	{
		this->weaponSprite.setTexture(*weaponTextureLeft);
		weaponSprite.setPosition(weaponPositionLeft);
	}
	else if (playerFacingRight)
	{
		this->weaponSprite.setTexture(*weaponTextureRight);
		weaponSprite.setPosition(weaponPositionRight);
	}
}

void Weapon::updateWeapon(const sf::RenderTarget* target, sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft)
{
	initWeaponPosition(playerPosition, playerFacingRight, playerFacingLeft);
	rotateWeapon(playerFacingRight, playerFacingLeft);
}

void Weapon::renderWeapon(sf::RenderTarget* target)
{
	target->draw(weaponSprite);
}

