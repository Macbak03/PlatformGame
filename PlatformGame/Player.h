#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Pistol.h"
#include "Rifle.h"
#include "SniperRifle.h"
#include "Shotgun.h"
class Player
{
private:
	//Textures
	sf::Texture* playerTextureRight;
	sf::Texture* playerTextureLeft;
	sf::Sprite playerSprite;
	void initShape();
	void loadTextures();

	bool spaceHold;
	bool onGround;
	bool facingRight, facingLeft;

	//Physics
	float playerSpeed;
	sf::Vector2f velocity;
	float gravity;
	float terminalVelocity;
	float jumpSpeed;
	void initPhysics();
	void updatePhysics(float deltaTime);

	//Weapon
	Weapon* weapon;
	void initWeapon();
	
public:
	Player();
	void spawnPlayer();
	void movePlayer();
	const sf::Sprite& getShape() const;
	const sf::Vector2f& getPosition() const;
	void changeWeapon();
	void updateBounceCollision(const sf::RenderTarget* target, std::vector<Platform> platforms);
	void updatePlayer(const sf::RenderTarget* target, float deltaTime, std::vector<Platform> platforms);
	void renderPlayer(sf::RenderTarget* target);

};

