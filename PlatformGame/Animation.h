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
	int updateAnimation(int row, float deltaTime, bool isMoving);
	void setCurrentImageX(unsigned int value);
};

