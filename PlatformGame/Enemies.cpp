#include "Enemies.h"
#include <iostream>

Enemies::Enemies()
{
}

void Enemies::addEnemy(Enemy* enemy)
{
	enemies.push_back(enemy);
	enemy->setBullets(&bullets);
}

std::vector<Enemy*> Enemies::getEnemies()
{
	return enemies;
}

void Enemies::updateCollisions(Bullets& bullets, Weapon* weapon, unsigned int& cash, unsigned int& points)
{
	std::vector<Bullet*> deletedBullets;
	std::vector<Enemy*> deletedEnemies;
	enemies.erase(std::remove_if(
		enemies.begin(),
		enemies.end(),
		[&bullets, weapon, &deletedEnemies, &deletedBullets, &cash, &points](Enemy* enemy) {
			//erasing enemy while hit
			bool enemyCollison = false;
			bool enemyDead = false;
			for (auto& element : bullets.getBullets()) {
				enemyCollison |= element->getCollider().intersects(element->getGlobalPosition(), enemy->getGlobalPosition(), enemy->getCollider());
			}
			//erasing bullets while hit
			auto& bulletsVector = bullets.getBullets();
			bulletsVector.erase(std::remove_if(bulletsVector.begin(), bulletsVector.end(), [enemy, &deletedBullets, &enemyCollison](Bullet* bullet) {
			bool bulletCollision = bullet->getCollider().intersects(bullet->getGlobalPosition(), enemy->getGlobalPosition(), enemy->getCollider());
			
			if (bulletCollision)
			{
				deletedBullets.push_back(bullet);
			}
			if (enemyCollison)
			{
				enemy->enemyHealth -= bullet->bulletDamage;
				enemy->setColorTimer(0.15f);
				enemy->changeColor();
			}
			return bulletCollision;
				}),
				bulletsVector.end()
			);
			
			if (enemy->enemyHealth <= 0)
			{
				deletedEnemies.push_back(enemy);
				cash += enemy->cashValue;
				points++;
				enemyDead = true;
			}
			return enemyDead;
		}),
	enemies.end());
	for (auto& element : deletedBullets)
	{
		delete(element);
	}
	for (auto& element : deletedEnemies)
	{
		delete(element);
	}
}


Bullets& Enemies::getBullets()
{
	return bullets;
}


void Enemies::update(sf::RenderTarget* target, float deltaTime)
{
	bullets.updateBullets(target, deltaTime);
}





