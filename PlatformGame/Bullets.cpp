#include "Bullets.h"
#include <iostream>


Bullets::Bullets() : maxBullets(1000)
{
}

void Bullets::spawnBullet(bool playerFacingLeft, sf::Vector2f weaponPosition, Node* parentNode, float damage)
{
	bullet = new Bullet(playerFacingLeft, parentNode, damage);
	bullet->initPosition(weaponPosition);
	bullets.push_back(bullet);
}

void Bullets::moveBullets(float deltaTime)
{
	for (auto& element : bullets)
	{
		element->moveBullet(deltaTime);
	}
}

void Bullets::updateCollsion(const sf::RenderTarget* target)
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

void Bullets::updateBullets(const sf::RenderTarget* target, float deltaTime)
{
	moveBullets(deltaTime);
	updateCollsion(target);
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

