#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Level.h"
#include "Pistol.h"
class Player
{
private:
	sf::Texture* playerTextureRight;
	sf::Texture* playerTextureLeft;
	sf::Sprite playerSprite;

	bool spaceHold;

	Weapon* weapon;

	//Physics
	float playerSpeed;
	sf::Vector2f velocity;
	float gravity;
	float terminalVelocity;
	float jumpSpeed;
	void initPhysics();
	void updatePhysics(float deltaTime);
	void initWeapon();

	void initShape();
	void loadTextures();
public:
	bool onGround;
	Player();
	void spawnPlayer();
	void movePlayer();
	sf::Sprite getShape();
	sf::Vector2f getPosition();
	void updateBounceCollision(const sf::RenderTarget* target, std::vector<Platform> platforms);
	void updatePlayer(const sf::RenderTarget* target, float deltaTime, std::vector<Platform> platforms);
	void renderPlayer(sf::RenderTarget* target);

};

