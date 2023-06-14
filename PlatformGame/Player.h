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
class Player : public Node
{
private:
	//Textures
	sf::Texture* playerTexture;
	sf::Texture* playerTextureLeft;
	sf::Sprite playerSprite;
	void initShape();
	void loadTextures();
	sf::Vector2f playerSize;

	//3 bule
	bool spaceHold;
	bool facingRight, facingLeft;
	bool hit;

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

	HealthBar healthBar;
	float playerMaxHealth;
	
public:
	float playerHealth;
	Player(Node* parentNode);
	void spawnPlayer();
	void movePlayer(float deltaTime);
	Weapon* getWeapon();
	Collider& getCollider();
	sf::Vector2f getPosition();
	void changeWeapon();
	void updateBounceCollision(sf::RenderTarget* target, std::vector<Platform*> platforms);
	void updateBulletCollision(Bullets& enemyBullets, float enemyDamage);
	void updatePlayer(sf::RenderTarget* target, float deltaTime, std::vector<Platform*> platforms, Node* parentNode, Bullets& enemyBullets, float enemyDamage);
	void drawCollider(sf::RenderTarget* target);
	void renderHealthBar(sf::RenderTarget* target);
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;

};

