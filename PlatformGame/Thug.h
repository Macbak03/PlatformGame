#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Thug : public Enemy
{
private:

	void initTexture(sf::Vector2u imageCount) override;
	void loadTexture() override;
	void initCollider() override;

public:
	Thug(Platform* platform, Node* parentNode);

};

