#pragma once
#include <SFML/Graphics.hpp>
#include "Bullets.h"
#include "FireBlast.h"
#include "Node.h"
class Weapon : public Node
{
private:
	float reloadTimer;
	
protected:
	float rateOfFire;
	float damage;
	float magazineSize;
	float reloadSpeed;
	const int maxBullets;
	float bulletSpawnTimer;
	float ammo;

	bool startReloadTimer;
	bool keyHold;

	sf::Vector2f weaponPositionRight;
	sf::Vector2f weaponPositionLeft;
	
	sf::Texture* weaponTextureRight;
	sf::Texture* weaponTextureLeft;
	sf::Sprite weaponSprite;
	

	Bullets bullets;

	virtual void loadTexture() = 0;
	virtual void initTexture() = 0;

public:
	Weapon(Node* parentNode);
	void initWeaponPosition(sf::Vector2f playerPosition);
	void shoot(bool playerFacingRight, bool playerFacingLeft, Node* parentNode);
	void reload(float deltaTime);
	void updateShooting(bool playerFacingRight, bool playerFacingLeft, float deltaTime,  Node* parentNode);
	void updateWeapon(const sf::RenderTarget* target, sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft, float deltaTime, Node* parentNode);
	void renderWeapon(sf::RenderTarget* target);
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
};

