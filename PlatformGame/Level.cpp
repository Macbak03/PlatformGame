#include "Level.h"

Level::Level() : Node(nullptr)
{
}

Platform* Level::addPlatform(sf::Vector2f position, Node* parentNode)
{
	Platform* platform = new Platform(position, parentNode);
	platforms.push_back(platform);
	return platform;
}


std::vector<Platform*> Level::getPlatforms()
{
	return platforms;
}

void Level::renderLevel(sf::RenderTarget& target)
{
	draw(target, sf::Transform::Identity);
}


void Level::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
}