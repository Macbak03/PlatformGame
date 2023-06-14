#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Collider.h"

class Bullet : public Node
{
private:
	sf::Texture* bulletTextureRight;
	sf::Sprite bulletSprite;

	sf::Vector2f velocity;

	Collider collider;
	sf::Vector2f bulletSize;
	

	bool bulletFacingLeft;
	bool bulletFacingRight;

	void loadTexture();
	void initTexture(bool playerFacingLeft);
	void initCollider(bool playerFacingLeft);
public:
	float bulletDamage;
	Bullet(bool playerFacingLeft, Node* parentNode, float damage);
	void initPosition(sf::Vector2f weaponPosition);
	const sf::Sprite& getShape() const;
    Collider& getCollider();
	void moveBullet(float deltaTime);
	void drawCollider(sf::RenderTarget* target);
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
};

