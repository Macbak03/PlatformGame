#include "Level.h"


Level::Level()
{
}

void Level::addPlatform(sf::Vector2f position)
{
	Platform platform(position);
	platforms.push_back(platform);
}

std::vector<Platform> Level::getPlatforms()
{
	return this->platforms;
}


void Level::renderLevel(sf::RenderTarget* target)
{
	for (auto& element : platforms)
	{
		element.renderPlatform(target);
	}
}
