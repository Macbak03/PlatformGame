#pragma once
#include "Bullet.h"
#include <vector>

class Bullets
{
private:
	std::vector<Bullet> bullets;
public:
	Bullets();
	void spawnBullet(bool playerFacingRight, bool playerFacingLeft, sf::Vector2f& weaponPosition);
	void renderBullets(sf::RenderTarget* target);
	void updateBullets(const sf::RenderTarget* target);
	const std::vector<Bullet>& getBullets() const;
	void updateWindowCollsion(const sf::RenderTarget* target);
	void moveBullets();
};

