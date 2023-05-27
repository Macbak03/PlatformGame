#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Bandit : public Enemy
{
private:

	Animation* animation;
	void initTexture() override;
	void loadTexture() override;
	void initAnimation() override;

public:
	Bandit();
	void updateEnemyAnimation(float& deltaTime) override;
	sf::Vector2f getEnemyScale() override;
	
};

