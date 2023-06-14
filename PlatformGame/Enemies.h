#pragma once
#include "Enemy.h"
#include <vector>
#include "Bullets.h"
#include "Weapon.h"
class Enemies
{
private:
	std::vector<Enemy*> enemies;
	float hitColorTimer;
	Bullets bullets;
public:
	
	Enemies();
	void addEnemy(Enemy* enemy);
	std::vector<Enemy*> getEnemies();
	void updateCollisions(Bullets& bullets, Weapon* weapon);
	Bullets& getBullets();
	float getDamage(Enemy* enemy);
	void update(sf::RenderTarget* target,  float deltaTime);
};

