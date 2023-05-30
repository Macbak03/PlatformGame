#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Node.h"
#include "Collider.h"
class Platform : public Node
{
private:
	sf::Texture* platformTexture;
	sf::Sprite platformSprite;
	Collider collider;
	sf::Vector2f platformSize;
	void loadTexture();
	void initTexture();
	void initColider();
public:
	Platform(sf::Vector2f position, Node* parentNode);
	sf::Sprite getShape();
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
	Collider& getCollider();
};

