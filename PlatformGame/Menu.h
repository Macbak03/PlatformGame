#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Menu
{
private:
	sf::Font font;
	sf::Text titleText;
	sf::Text returnText;
	sf::Text cashText;
	sf::Text pistolText;
	sf::Text rifleText;
	sf::Text shotgunText;
	sf::Text sniperRifleText;
	sf::Text pistolPriceText, riflePriceText, shotgunPriceText, sniperRiflePriceText;
	sf::Text currentWeaponText;
	sf::Text healText;
	
	unsigned int pistolPrice, riflePrice, shotgunPrice, sniperRiflePrice;
	unsigned int healPrice;

	sf::Texture* menuTexture;
	sf::Sprite menuSprite;
	std::vector<sf::Text*> menuOptions;
	std::vector<sf::Text*> clikableOptions;
	Player& player;
public:
	Menu(sf::VideoMode size, Player& player);
	void loadTexture();
	void initBackground(sf::VideoMode size);
	void loadFont();
	void initText(sf::VideoMode size);
	void updateText();
	void updateMenuOptions(sf::Window* target, bool& pauseGame, sf::Event& event);
	void updateMenu(sf::Window* target, bool& pauseGame, sf::Event& event);
	void drawMenu(sf::RenderTarget* target);
};

