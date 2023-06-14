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

	void initTexture(sf::Vector2u imageCount);
	void loadTexture();
	void initAnimation();
public:
	HealthBar();
	//virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
	void updateHealthBarAnimation(float weaponDamage, bool hit, sf::Vector2f position, float maxHealth);
	void drawHealthBar(sf::RenderTarget* target);
	sf::Sprite getSprite();
};

