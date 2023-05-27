#pragma once
#include <SFML/Graphics.hpp>

class FireBlast
{
private:
	sf::Texture* fireBlastTexture;
	sf::Sprite fireBlastSprite;

    void loadTexture();
	void initTexture(bool playerFacingRight, bool playerFacingLeft);
public:
	FireBlast(bool playerFacingRight, bool playerFacingLeft, sf::Vector2f weaponPosition);
	void initPosition(sf::Vector2f weaponPosition);
	void updateFireBlast(const sf::RenderTarget* target, bool playerFacingRight, bool playerFacingLeft);
	void rednerFireBlast(sf::RenderTarget* target);
};

