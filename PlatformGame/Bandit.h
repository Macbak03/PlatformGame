#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Bandit : public Enemy
{
private:

	void initTexture(sf::Vector2u imageCount) override;
	void loadTexture() override;
	void initCollider() override;

public:
	Bandit(Platform* platform, Node* parentNode);
	
};

