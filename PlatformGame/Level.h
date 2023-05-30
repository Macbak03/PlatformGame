#pragma once
#include <vector>
#include "Platform.h"
#include "Node.h"
class Level : public Node
{
private:
	std::vector<Platform*> platforms;

public:
	Level();
	Platform* addPlatform(sf::Vector2f position, Node* parentNode);
	std::vector<Platform*> getPlatforms();
	void renderLevel(sf::RenderTarget& target);
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;
};

