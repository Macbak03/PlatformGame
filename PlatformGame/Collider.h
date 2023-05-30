#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"
class Collider
{
public:
	sf::Vector2f offset;
	sf::Vector2f size;
	bool xCausesCollision(sf::Vector2f thisGlobalPosition, sf::Vector2f otherGlobalPosition, Collider& otherCollider, float speedX);
	bool yCausesCollision(sf::Vector2f thisGlobalPosition, sf::Vector2f otherGlobalPosition, Collider& otherCollider, float speedY);
	bool intersects(sf::Vector2f thisGlobalPosition, sf::Vector2f otherGlobalPosition, Collider& otherCollider);
};

