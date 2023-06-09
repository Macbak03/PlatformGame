#include "HealthBar.h"
#include <iostream>

HealthBar::HealthBar()
{
	healthBarSize = sf::Vector2f(60.f, 25.f);
	initTexture(sf::Vector2u(12, 1));
	initAnimation();
}

void HealthBar::loadTexture()
{
	healthBarTexture = new sf::Texture;
	if (!healthBarTexture->loadFromFile("Textures/health_bar.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}


void HealthBar::initTexture(sf::Vector2u imageCount)
{
	loadTexture();
	healthBarSprite.setTexture(*healthBarTexture);
	healthBarSprite.setScale(sf::Vector2f((healthBarSize.x * imageCount.x) / healthBarTexture->getSize().x, (healthBarSize.y * imageCount.y) / healthBarTexture->getSize().y));
}


void HealthBar::initAnimation()
{
	animation = new Animation(healthBarTexture, sf::Vector2u(12, 1), 0.5f);
	animation->setCurrentImageX(11);
}

void HealthBar::updateHealthBarAnimation(unsigned int weaponDamage, bool hit, sf::Vector2f enemyPosition)
{
	healthBarSprite.setTextureRect(animation->uvRec);
	animation->updateHealthAnimation(weaponDamage, hit);
	healthBarSprite.setPosition(sf::Vector2f(enemyPosition.x - 30.f, enemyPosition.y - 10.f));
}

void HealthBar::drawHealthBar(sf::RenderTarget* target)
{
	target->draw(healthBarSprite);
}

sf::Sprite HealthBar::getSprite()
{
	return healthBarSprite;
}



