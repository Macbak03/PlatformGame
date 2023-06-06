#include "Bullets.h"
#include <iostream>


Bullets::Bullets()
{
}

void Bullets::spawnBullet(bool playerFacingLeft, sf::Vector2f weaponPosition, Node* parentNode)
{
	Bullet* bullet = new Bullet(playerFacingLeft, parentNode);
	bullet->initPosition(weaponPosition);
	bullets.push_back(bullet);
}

void Bullets::moveBullets()
{
	for (auto& element : bullets)
	{
		element->moveBullet();
	}
}

void Bullets::updateWindowCollsion(const sf::RenderTarget* target)
{
	std::vector<Bullet*> deletedBullets;
	bullets.erase(std::remove_if(
		bullets.begin(),
		bullets.end(),
		[target, &deletedBullets](Bullet* bullet) {
			bool windowCollision = bullet->getGlobalPosition().x <= 0 || bullet->getGlobalPosition().x + bullet->getCollider().size.x >= target->getSize().x;
			if (windowCollision)
			{
				deletedBullets.push_back(bullet);
			}
			return windowCollision;
		}),
		bullets.end()
			);
	for (auto& element : deletedBullets)
	{
		delete(element);
	}
}

void Bullets::updateBullets(const sf::RenderTarget* target)
{
	moveBullets();
	updateWindowCollsion(target);
	//std::cout << bullets.size() << std::endl;

}

void Bullets::renderCollider(sf::RenderTarget* target) {
	for (auto& element : bullets)
	{
		element->drawCollider(target);
	}
}

std::vector<Bullet*>& Bullets::getBullets() 
{
	return bullets;
}
