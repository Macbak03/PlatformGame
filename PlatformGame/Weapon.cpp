#include "Weapon.h"

Weapon::Weapon()
{
	weaponTextureRight = nullptr;
	weaponTextureLeft = nullptr;
	rateOfFire = 0.f;
	damage = 0.f;
	ammoSize = 0.f;
}


void Weapon::initWeaponPosition(sf::Vector2f playerPosition)
{
	weaponPositionRight = sf::Vector2f(playerPosition.x + 45.f, playerPosition.y + 37.f);
	weaponSprite.setPosition(weaponPositionRight);
	weaponPositionLeft = sf::Vector2f(playerPosition.x - 15.f, playerPosition.y + 37.f);
}


void Weapon::rotateWeapon()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		right = false;
		this->weaponSprite.setTexture(*weaponTextureLeft);
		weaponSprite.setPosition(weaponPositionLeft);
		left = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		left = false;
		this->weaponSprite.setTexture(*weaponTextureRight);
		weaponSprite.setPosition(weaponPositionRight);
		right = true;
	}
	if(left)
	{
		weaponSprite.setPosition(weaponPositionLeft);
	}
	if (right)
	{
		weaponSprite.setPosition(weaponPositionRight);
	}
}

void Weapon::updateWeapon(const sf::RenderTarget* target, sf::Vector2f playerPosition)
{
	initWeaponPosition(playerPosition);
	rotateWeapon();
}

void Weapon::renderWeapon(sf::RenderTarget* target)
{
	target->draw(weaponSprite);
}

