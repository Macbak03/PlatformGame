#pragma once
#include<SFML/Graphics.hpp>
#include "Level.h"
#include "Animation.h"
#include "HealthBar.h"
#include "Bullets.h"
class Enemy : public Node
{
private:
	void flip();
	float hitColorTimer;
	bool hit;
	bool enemyFacingRight;
	bool enemyFacingLeft;
	sf::Color enemyColor;
	float bulletSpawnTimer;
	
protected:
	sf::Texture* enemyTexture;
	sf::Sprite enemySprite;
	Platform* platform;
	Collider collider;
	HealthBar healthBar;
	Bullets* bullets;


	float enemySpeed;
	float enemyDamage;
	float enemyRateOfFire;

	sf::Vector2f enemySize;

	virtual void loadTexture() = 0;
	virtual void initTexture(sf::Vector2u imageCount) = 0;
	virtual void initAnimation() = 0;
	virtual void initCollider() = 0;

public:
	int enemyHealth;
	Enemy(Platform* platform, Node* parentNode);
	~Enemy();
	virtual void updateEnemyAnimation(float& deltaTime) = 0;
	void spawnEnemy();
	void moveEnemy();
	void updateBounceCollision();
	void updateEnemy(const sf::RenderTarget* target, float deltaTime, unsigned int weaponDamage, Node* parentNode);
	void drawCollider(sf::RenderTarget* target);
	void changeColor();
	void setColorTimer(float value);
	void updateColorTimer(float deltaTime);
	Collider& getCollider();
	void shoot(Node* parentNode);
	void updateShooting(float deltaTime, Node* parentNode);
	void renderHealthBar(sf::RenderTarget* target);
	void setBullets(Bullets* bullets);
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
};

