#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
class HealthBar
{
private:
	Animation* animation;
	sf::Texture* healthBarTexture;
	sf::Sprite healthBarSprite;
	sf::Vector2f healthBarSize;

	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarOutline;

	void initTexture(sf::Vector2u imageCount);
	void loadTexture();
	void initAnimation();
public:
	HealthBar();
	void updateHealthBarAnimation(sf::Vector2f position, float maxHealth, float health);
	void drawHealthBar(sf::RenderTarget* target);
	sf::Sprite getSprite();
};

