#include "Level.h"


Level::Level()
{
}

Platform* Level::addPlatform(sf::Vector2f position)
{
	Platform* platform = new Platform(position);
	platforms.push_back(platform);
	return platform;
}

std::vector<Platform*> Level::getPlatforms()
{
	return platforms;
}


void Level::renderLevel(sf::RenderTarget* target)
{
	for (auto& element : platforms)
	{
		element->renderPlatform(target);
	}
}
