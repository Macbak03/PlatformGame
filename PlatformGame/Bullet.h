#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class Bullet
{
private:
	sf::Texture* bulletTextureLeft;
	sf::Texture* bulletTextureRight;
	sf::Sprite bulletSprite;

	sf::Vector2f velocity;

	bool bulletFacingLeft;
	bool bulletFacingRight;

	void loadTexture();
	void initTexture(bool playerFacingRight, bool playerFacingLeft);
public:
	Bullet(bool playerFacingRight, bool playerFacingLeft);
	void initPosition(sf::Vector2f weaponPosition);
	const sf::Sprite& getShape() const;
	void moveBullet();
	void renderBullet(sf::RenderTarget* target);
};

