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
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setSize(sf::Vector2f(56.f, 6.f));
	loadTexture();
	healthBarSprite.setTexture(*healthBarTexture);
	healthBarSprite.setScale(sf::Vector2f((healthBarSize.x * imageCount.x) / healthBarTexture->getSize().x, (healthBarSize.y * imageCount.y) / healthBarTexture->getSize().y));
}


void HealthBar::initAnimation()
{
	animation = new Animation(healthBarTexture, sf::Vector2u(12, 1), 0.5f);
}

void HealthBar::updateHealthBarAnimation(sf::Vector2f position, float maxHealth, float health)
{
	healthBarSprite.setTextureRect(animation->uvRec);
	healthBarSprite.setPosition(sf::Vector2f(position.x - 30.f, position.y - 10.f));
	healthBar.setPosition(sf::Vector2f(position.x - 28.f, position.y + 4.35f));
	healthBar.setScale(sf::Vector2f(health / maxHealth, 1.f));
}

void HealthBar::drawHealthBar(sf::RenderTarget* target)
{
	target->draw(healthBarSprite);
	target->draw(healthBar);
}

sf::Sprite HealthBar::getSprite()
{
	return healthBarSprite;
}



