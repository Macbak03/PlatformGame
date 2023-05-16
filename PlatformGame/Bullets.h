#pragma once
#include "Bullet.h"
#include <vector>

class Bullets
{
private:
	std::vector<Bullet> bullets;
	const int bulletMaxAmmount;
public:
	Bullets();
	void spawnBullet(bool playerFacingRight, bool playerFacingLeft, sf::Vector2f& weaponPosition);
	void renderBullets(sf::RenderTarget* target);
	void updateBullets(const sf::RenderTarget* target, bool playerFacingRight, bool playerFacingLeft, sf::Vector2f& weaponPosition);
	void updateWindowCollsion(const sf::RenderTarget* target);
	void moveBullets(bool playerFacingRight, bool playerFacingLeft);
};

