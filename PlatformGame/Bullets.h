#pragma once
#include "Bullet.h"
#include <vector>

class Bullets
{
private:
	std::vector<Bullet*> bullets;
public:
	const int maxBullets;
	Bullets();
	void spawnBullet(bool playerFacingLeft, sf::Vector2f weaponPosition, Node* parentNode);
	void updateBullets(const sf::RenderTarget* target, Node* playerNode, Collider playerCollider);
	std::vector<Bullet*>& getBullets();
	void updateCollsion(const sf::RenderTarget* target, Node* playerNode, Collider playerCollider);
	void renderCollider(sf::RenderTarget* target);
	void moveBullets();
};

