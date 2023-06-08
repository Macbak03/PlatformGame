#pragma once
#include <SFML/Graphics.hpp>
#include "Node.h"

class FireBlast : public Node
{
private:
	sf::Texture* fireBlastTexture;
	sf::Sprite fireBlastSprite;
	sf::Vector2f fireBlastSize;

	float drawTimer;

    void loadTexture();
	void initTexture();
	
public:
	FireBlast(Node* parentNode);
	void initPosition(sf::Vector2f weaponPosition);
	void setDrawTimer(float value);
	void updateDrawTimer(float deltaTime);
	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;

};

