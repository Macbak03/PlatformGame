#pragma once
#include <vector>
#include "Platform.h"
class Level
{
private:
	std::vector<Platform*> platforms;

public:
	Level();
	Platform* addPlatform(sf::Vector2f position);
	std::vector<Platform*> getPlatforms();
	void renderLevel(sf::RenderTarget* target);
};

