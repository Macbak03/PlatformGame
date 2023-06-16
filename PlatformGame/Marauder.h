#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Marauder : public Enemy
{
private:
	void initTexture(sf::Vector2u imageCount) override;
	void loadTexture() override;
	void initCollider() override;

public:
	Marauder(Platform* platform, Node* parentNode);

};

