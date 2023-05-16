#include "Bullets.h"


Bullets::Bullets() 
{
}

void Bullets::spawnBullet(bool playerFacingRight, bool playerFacingLeft, sf::Vector2f& weaponPosition)
{
	Bullet bullet(playerFacingRight, playerFacingLeft);
	bullet.initPosition(weaponPosition);
	bullets.push_back(bullet);
}

void Bullets::moveBullets()
{
	for (auto& element : bullets)
	{
		element.moveBullet();
	}
}

void Bullets::updateWindowCollsion(const sf::RenderTarget* target)
{
	bullets.erase(std::remove_if(
		bullets.begin(),
		bullets.end(),
		[target](Bullet const& bullet) {
			bool window_collision = bullet.getShape().getGlobalBounds().left <= 0 || bullet.getShape().getGlobalBounds().left + bullet.getShape().getGlobalBounds().width >= target->getSize().x;
	return window_collision;
		}),
		bullets.end()
			);
}

void Bullets::updateBullets(const sf::RenderTarget* target)
{
	moveBullets();
	updateWindowCollsion(target);
}

const std::vector<Bullet>& Bullets::getBullets() const
{
	return bullets;
}

void Bullets::renderBullets(sf::RenderTarget* target)
{
	for (auto& element : bullets)
	{
		element.renderBullet(target);
	}
}

