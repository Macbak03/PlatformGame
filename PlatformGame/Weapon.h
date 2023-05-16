#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Bullets.h"
class Weapon
{
protected:
	float rateOfFire;
	float damage;
	float ammoSize;

	sf::Vector2f weaponPositionRight;
	sf::Vector2f weaponPositionLeft;
	
	sf::Texture* weaponTextureRight;
	sf::Texture* weaponTextureLeft;
	sf::Sprite weaponSprite;
	
	Bullets bullets;

	virtual void loadTexture() = 0;
	virtual void initTexture() = 0;

public:
	Weapon();
	void initWeaponPosition(sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft);
	void rotateWeapon(bool playerFacingRight, bool playerFacingLeft);
	void shoot(bool playerFacingRight, bool playerFacingLeft);
	void updateWeapon(const sf::RenderTarget* target, sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft);
	void renderWeapon(sf::RenderTarget* target);
};

