#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Pistol.h"
#include "Rifle.h"
#include "SniperRifle.h"
#include "Shotgun.h"
#include "Node.h"
#include "Collider.h"
#include "Utils.h"
#include "HealthBar.h"
#include "Animation.h"
class Player : public Node
{
private:
	//Textures
	sf::Texture* playerTexture;
	sf::Texture* playerTextureLeft;
	sf::Sprite playerSprite;
	void initShape(sf::Vector2u imageCount);
	void loadTextures();
	sf::Vector2f playerSize;
	sf::Color playerColor;
	float hitColorTimer;

	//3 bule
	bool spaceHold;
	bool facingRight, facingLeft;
	bool hit;
	bool isMoving;

	//Physics
	Collider collider;
	float playerSpeed;
	sf::Vector2f velocity;
	float gravity;
	bool onGround;
	bool startJumpTimer;
	float terminalVelocity;
	float jumpSpeed;
	float jumpTimer;
	void initPhysics();
	void updatePhysics(float deltaTime);

	//Weapon
	Bullets bullets;
	Weapon* weapon;
	void initWeapon();

	Animation* animation;
	void initAnimation();
	int currentAnimationFrame;


	HealthBar healthBar;
	
	
public:
	unsigned int points;
	unsigned int cash;
	float playerHealth;
	float playerMaxHealth;
	std::string currentWeapon;
	Player(Node* parentNode);
	void spawnPlayer();
	void movePlayer(float deltaTime);
	Weapon* getWeapon();
	Collider& getCollider();
	Bullets& getBullets();
	sf::Vector2f getPosition();
	void changeColor();
	void updateColor(float deltaTime);
	void changeToPistol();
	void changeToRifle();
	void changeToShotgun();
	void changeToSniperRifle();
	void updatePlayerAnimation(float deltaTime);
	void updateBounceCollision(sf::RenderTarget* target, std::vector<Platform*> platforms, float deltaTime);
	void updateBulletCollision(Bullets& enemyBullets);
	void updatePlayer(sf::RenderTarget* target, float deltaTime, std::vector<Platform*> platforms, Node* parentNode, Bullets& enemyBullets);
	void drawCollider(sf::RenderTarget* target);
	void renderHealthBar(sf::RenderTarget* target);
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
};

