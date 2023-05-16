#include "Bullets.h"

Bullets::Bullets() : bulletMaxAmmount(1000)
{
}

void Bullets::spawnBullet(bool playerFacingRight, bool playerFacingLeft, sf::Vector2f& weaponPosition)
{
	Bullet bullet(playerFacingRight, playerFacingLeft);
	bullet.initPosition(weaponPosition);
	bullets.push_back(bullet);
}

void Bullets::moveBullets(bool playerFacingRight, bool playerFacingLeft)
{
	for (auto& element : bullets)
	{
		element.moveBullet(playerFacingRight, playerFacingLeft);
	}
}

void Bullets::updateWindowCollsion(const sf::RenderTarget* target)
{
	bullets.erase(std::remove_if(
		bullets.begin(),
		bullets.end(),
		[](Bullet const& bullet) {
			bool window_collision = bullet.getShape().getGlobalBounds().left <= 0 || bullet.getShape().getGlobalBounds().left + bullet.getShape().getGlobalBounds().width;
	return window_collision;
		}),
		bullets.end()
			);
}

void Bullets::updateBullets(const sf::RenderTarget* target, bool playerFacingRight, bool playerFacingLeft, sf::Vector2f& weaponPosition)
{
	if (bullets.size() < bulletMaxAmmount)
	{
		spawnBullet(playerFacingRight, playerFacingLeft, weaponPosition);
	}
	moveBullets(playerFacingRight, playerFacingLeft);
	updateWindowCollsion(target);
}

void Bullets::renderBullets(sf::RenderTarget* target)
{
	for (auto& element : bullets)
	{
		element.renderBullet(target);
	}
}

