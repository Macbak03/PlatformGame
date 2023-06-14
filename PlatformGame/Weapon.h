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
	
	unsigned int magazineSize;
	float reloadTime;
	
	float bulletSpawnTimer;
	unsigned int ammo;

	bool startReloadTimer;
	bool keyHold;

	sf::Vector2f weaponPosition;
	sf::Vector2f weaponSize;
	
	sf::Texture* weaponTexture;
	sf::Sprite weaponSprite;
	

	Bullets& bullets;
	FireBlast fireBlast;
	virtual void loadTexture() = 0;
	virtual void initTexture() = 0;

public:
	float damage;
	Weapon(Node* parentNode, Bullets& bullets);
	void initWeaponPosition(sf::Vector2f playerPosition);
	void shoot(bool playerFacingRight, bool playerFacingLeft, Node* parentNode);
	void reload(float deltaTime);
	Bullets& getBullets();
	sf::Vector2f& getSize();
	void scale();
	void updateShooting(bool playerFacingRight, bool playerFacingLeft, float deltaTime,  Node* parentNode);
	void updateWeapon(const sf::RenderTarget* target, sf::Vector2f playerPosition, bool playerFacingRight, bool playerFacingLeft, float deltaTime, Node* parentNode, Node* playerNode, Collider playerCollider);
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
};

