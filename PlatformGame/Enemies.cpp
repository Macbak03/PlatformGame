#include "Enemies.h"
#include <iostream>

Enemies::Enemies()
{
}

void Enemies::addEnemy(Enemy* enemy)
{
	enemies.push_back(enemy);
}

std::vector<Enemy*> Enemies::getEnemies()
{
	return enemies;
}

void Enemies::updateCollisions(Bullets& bullets, Weapon* weapon)
{
	std::vector<Enemy*> deletedEnemies;
	enemies.erase(std::remove_if(
		enemies.begin(),
		enemies.end(),
		[bullets, weapon, &deletedEnemies](Enemy* enemy) {
			bool bulletCollison = false;
			bool enemyDead = false;
			for (auto& element : bullets.getBullets()) {
				bulletCollison = element->getCollider().intersects(enemy->getGlobalPosition(), element->getGlobalPosition(), element->getCollider());
			}
			if (bulletCollison)
			{
				enemy->enemyHealth -= weapon->damage;
			}
			if (enemy->enemyHealth <= 0.f)
			{
				enemyDead = true;
				deletedEnemies.push_back(enemy);
			}
			return enemyDead;
		}),
	enemies.end());
	for (auto& element : deletedEnemies)
	{
		delete(element);
	}
	std::cout << enemies[0]->enemyHealth << "         " <<enemies[1]->enemyHealth << std::endl;
}



