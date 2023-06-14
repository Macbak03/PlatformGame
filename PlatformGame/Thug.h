#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Thug : public Enemy
{
private:

	Animation* animation;
	void initTexture(sf::Vector2u imageCount) override;
	void loadTexture() override;
	void initAnimation() override;
	void initCollider() override;

public:
	Thug(Platform* platform, Node* parentNode);
	void updateEnemyAnimation(float& deltaTime) override;

};

