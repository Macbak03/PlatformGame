#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
	float imageChangeValue;
public:
	sf::IntRect uvRec;
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();
	void updateAnimation(int row, float deltaTime);
	void updateHealthAnimation(float weaponDamage, bool hit, float maxHealth);
	void setCurrentImageX(unsigned int value);
};

