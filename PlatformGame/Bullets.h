#pragma once
#include "Bullet.h"
#include <vector>

class Bullets
{
private:
	std::vector<Bullet*> bullets;
public:
	Bullets();
	void spawnBullet(bool playerFacingLeft, sf::Vector2f weaponPosition, Node* parentNode);
	void updateBullets(const sf::RenderTarget* target);
	std::vector<Bullet*>& getBullets();
	void updateWindowCollsion(const sf::RenderTarget* target);
	void renderCollider(sf::RenderTarget* target);
	void moveBullets();
};

