#pragma once
#include<SFML/Graphics.hpp>
#include "Level.h"
#include "Animation.h"
class Enemy : public Node
{
private:
	void flip();
protected:
	sf::Texture* enemyTextrue;
	sf::Sprite enemySprite;
	Platform* platform;
	Collider collider;

	float enemySpeed;
	float enemyDamage;
	float enemyRateOfFire;

	sf::Vector2f enemySize;

	virtual void loadTexture() = 0;
	virtual void initTexture(sf::Vector2u imageCount) = 0;
	virtual void initAnimation() = 0;
	virtual void initCollider() = 0;

public:
	float enemyHealth;
	Enemy(Platform* platform, Node* parentNode);
	~Enemy();
	virtual void updateEnemyAnimation(float& deltaTime) = 0;
	void spawnEnemy();
	void moveEnemy();
	void updateBounceCollision();
	void updateEnemy(const sf::RenderTarget* target, float deltaTime);
	void drawCollider(sf::RenderTarget* target);
	Collider& getCollider();
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
};

