#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"

class Bullet : public Node
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
	Bullet(bool playerFacingRight, bool playerFacingLeft, Node* parentNode);
	void initPosition(sf::Vector2f weaponPosition);
	const sf::Sprite& getShape() const;
	void moveBullet();
	void renderBullet(sf::RenderTarget* target);
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
};

