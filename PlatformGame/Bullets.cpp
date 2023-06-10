#include "Bullets.h"
#include <iostream>


Bullets::Bullets() : maxBullets(1000)
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

void Bullets::updateCollsion(const sf::RenderTarget* target, Node* playerNode, Collider playerCollider)
{
	std::vector<Bullet*> deletedBullets;
	bullets.erase(std::remove_if(
		bullets.begin(),
		bullets.end(),
		[target, playerNode, &playerCollider, &deletedBullets](Bullet* bullet) {
			bool windowCollision = bullet->getGlobalPosition().x <= 0 || bullet->getGlobalPosition().x + bullet->getCollider().size.x >= target->getSize().x;
			bool playerCollision = bullet->getCollider().intersects(bullet->getGlobalPosition(), playerNode->getGlobalPosition(), playerCollider);
			if (windowCollision || playerCollision)
			{
				deletedBullets.push_back(bullet);
			}
			return windowCollision || playerCollision;
		}),
		bullets.end()
			);
	for (auto& element : deletedBullets)
	{
		delete(element);
	}
}

void Bullets::updateBullets(const sf::RenderTarget* target, Node* playerNode, Collider playerCollider)
{
	moveBullets();
	updateCollsion(target, playerNode, playerCollider);
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
