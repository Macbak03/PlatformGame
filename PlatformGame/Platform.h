#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class Platform
{
private:
	sf::Texture* platformTexture;
	sf::Sprite platformSprite;

	void loadTexture();
	void initTexture();
public:
	Platform(sf::Vector2f position);
	void setPosition(sf::Vector2f position);
	sf::Sprite getShape();
	//void updatePlatformCollision(Player* player);
	//void updatePlatform();
	void renderPlatform(sf::RenderTarget* target);
};

