#include "Menu.h"
#include <iostream>
#include <vector>
#include <sstream>

Menu::Menu(sf::VideoMode size, Player& player) : player(player)
{
	initBackground(size);
	initText(size);
	pistolPrice = 0;
	riflePrice = 30;
	shotgunPrice = 70;
	sniperRiflePrice = 150;
	healPrice = 100;
}

void Menu::loadTexture()
{
	menuTexture = new sf::Texture;
	if (!menuTexture->loadFromFile("Textures/menu.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Menu::initBackground(sf::VideoMode size)
{
	loadTexture();
	menuSprite.setTexture(*menuTexture);
	float scaleX = static_cast<float>(size.width) / menuTexture->getSize().x;
	float scaleY = static_cast<float>(size.height) / menuTexture->getSize().y;
	menuSprite.setScale(sf::Vector2f(scaleX, scaleY));
}

void Menu::loadFont()
{
	if (!font.loadFromFile("Fonts/DomBold_BT.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
}

void Menu::initText(sf::VideoMode size)
{
	loadFont();
	sf::Vector2f menuSize = sf::Vector2f(static_cast<float>(size.width), static_cast<float>(size.height));
	titleText.setFont(font);
	titleText.setCharacterSize(70);
	titleText.setFillColor(sf::Color::White);
	titleText.setOutlineColor(sf::Color::Black);
	titleText.setOutlineThickness(2);
	titleText.setString("MENU");
	titleText.setPosition(sf::Vector2f(menuSize.x/2 - 70.f, 80.f));
	menuOptions.push_back(&titleText);

	returnText.setFont(font);
	returnText.setCharacterSize(70);
	returnText.setFillColor(sf::Color::White);
	returnText.setOutlineColor(sf::Color::Black);
	returnText.setOutlineThickness(2);
	returnText.setString("RETURN");
	returnText.setPosition(sf::Vector2f(menuSize.x - 350.f, menuSize.y - 210.f));
	menuOptions.push_back(&returnText);
	clikableOptions.push_back(&returnText);
	
	cashText.setFont(font);
	cashText.setCharacterSize(70);
	cashText.setFillColor(sf::Color::White);
	cashText.setOutlineColor(sf::Color::Black);
	cashText.setOutlineThickness(2);
	cashText.setPosition(sf::Vector2f(120.f, 80.f));
	menuOptions.push_back(&cashText);
	
	pistolText.setFont(font);
	pistolText.setCharacterSize(70);
	pistolText.setFillColor(sf::Color::White);
	pistolText.setOutlineColor(sf::Color::Black);
	pistolText.setOutlineThickness(2);
	pistolText.setString("Pistol");
	pistolText.setPosition(sf::Vector2f(200.f, 250.f));
	menuOptions.push_back(&pistolText);
	clikableOptions.push_back(&pistolText);

	rifleText.setFont(font);
	rifleText.setCharacterSize(70);
	rifleText.setFillColor(sf::Color::White);
	rifleText.setOutlineColor(sf::Color::Black);
	rifleText.setOutlineThickness(2);
	rifleText.setString("Rifle");
	rifleText.setPosition(sf::Vector2f(200.f, 350.f));
	menuOptions.push_back(&rifleText);
	clikableOptions.push_back(&rifleText);

	shotgunText.setFont(font);
	shotgunText.setCharacterSize(70);
	shotgunText.setFillColor(sf::Color::White);
	shotgunText.setOutlineColor(sf::Color::Black);
	shotgunText.setOutlineThickness(2);
	shotgunText.setString("Shotgun");
	shotgunText.setPosition(sf::Vector2f(200.f, 450.f));
	menuOptions.push_back(&shotgunText);
	clikableOptions.push_back(&shotgunText);

	sniperRifleText.setFont(font);
	sniperRifleText.setCharacterSize(70);
	sniperRifleText.setFillColor(sf::Color::White);
	sniperRifleText.setOutlineColor(sf::Color::Black);
	sniperRifleText.setOutlineThickness(2);
	sniperRifleText.setString("Sniper rifle");
	sniperRifleText.setPosition(sf::Vector2f(200.f, 550.f));
	menuOptions.push_back(&sniperRifleText);
	clikableOptions.push_back(&sniperRifleText);

	pistolPriceText.setFont(font);
	pistolPriceText.setCharacterSize(55);
	pistolPriceText.setFillColor(sf::Color::White);
	pistolPriceText.setOutlineColor(sf::Color::Black);
	pistolPriceText.setOutlineThickness(2);
	pistolPriceText.setPosition(sf::Vector2f(600.f, 260.f));
	menuOptions.push_back(&pistolPriceText);

	riflePriceText.setFont(font);
	riflePriceText.setCharacterSize(55);
	riflePriceText.setFillColor(sf::Color::White);
	riflePriceText.setOutlineColor(sf::Color::Black);
	riflePriceText.setOutlineThickness(2);
	riflePriceText.setPosition(sf::Vector2f(600.f, 360.f));
	menuOptions.push_back(&riflePriceText);

	shotgunPriceText.setFont(font);
	shotgunPriceText.setCharacterSize(55);
	shotgunPriceText.setFillColor(sf::Color::White);
	shotgunPriceText.setOutlineColor(sf::Color::Black);
	shotgunPriceText.setOutlineThickness(2);
	shotgunPriceText.setPosition(sf::Vector2f(600.f, 460.f));
	menuOptions.push_back(&shotgunPriceText);

	sniperRiflePriceText.setFont(font);
	sniperRiflePriceText.setCharacterSize(55);
	sniperRiflePriceText.setFillColor(sf::Color::White);
	sniperRiflePriceText.setOutlineColor(sf::Color::Black);
	sniperRiflePriceText.setOutlineThickness(2);
	
	sniperRiflePriceText.setPosition(sf::Vector2f(600.f, 560.f));
	menuOptions.push_back(&sniperRiflePriceText);

	currentWeaponText.setFont(font);
	currentWeaponText.setCharacterSize(55);
	currentWeaponText.setFillColor(sf::Color::White);
	currentWeaponText.setOutlineColor(sf::Color::Black);
	currentWeaponText.setOutlineThickness(2);
	currentWeaponText.setPosition(sf::Vector2f(120.f, 170.f));
	menuOptions.push_back(&currentWeaponText);

	healText.setFont(font);
	healText.setCharacterSize(70);
	healText.setFillColor(sf::Color::White);
	healText.setOutlineColor(sf::Color::Black);
	healText.setOutlineThickness(2);
	healText.setPosition(sf::Vector2f(900.f, 400.f));
	menuOptions.push_back(&healText);
	clikableOptions.push_back(&healText);
}

void Menu::updateText()
{
	std::stringstream cash_ss;
	cash_ss << "Cash: " << player.cash << "$";
	cashText.setString(cash_ss.str());

	std::stringstream pistolPrice_ss;
	pistolPrice_ss << "Price: " << pistolPrice << "$";
	pistolPriceText.setString(pistolPrice_ss.str());

	std::stringstream riflePrice_ss;
	riflePrice_ss << "Price: " << riflePrice << "$";
	riflePriceText.setString(riflePrice_ss.str());

	std::stringstream shotgunPrice_ss;
	shotgunPrice_ss << "Price: " << shotgunPrice << "$";
	shotgunPriceText.setString(shotgunPrice_ss.str());

	std::stringstream sniperRiflePrice_ss;
	sniperRiflePrice_ss << "Price: " << sniperRiflePrice << "$";
	sniperRiflePriceText.setString(sniperRiflePrice_ss.str());

	std::stringstream healPrice_ss;
	healPrice_ss << "Heal to full hp - " << healPrice << "$";
	healText.setString(healPrice_ss.str());

	currentWeaponText.setString(player.currentWeapon);
}

void Menu::updateMenuOptions(sf::Window* target, bool& pauseGame, sf::Event& event)
{
	sf::Vector2i mousePositionInt = sf::Mouse::getPosition(*target);
	sf::Vector2f mousePositionFloat = static_cast<sf::Vector2f> (mousePositionInt);
	for (auto& element : clikableOptions)
	{
		if (element->getGlobalBounds().contains(mousePositionFloat))
		{
			element->setFillColor(sf::Color::Blue);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (element == &returnText)
				{
					pauseGame = false;
				}
				if (element == &pistolText)
				{
					player.changeToPistol();
				}
				if (element == &rifleText && player.cash >= riflePrice)
				{
					player.changeToRifle();
					player.cash -= riflePrice;
				}
				if (element == &shotgunText && player.cash >= shotgunPrice)
				{
					player.changeToShotgun();
					player.cash -= shotgunPrice;
				}
				if (element == &sniperRifleText && player.cash >= sniperRiflePrice)
				{
					player.changeToSniperRifle();
					player.cash -= sniperRiflePrice;
				}
				if (element == &healText && player.cash >= healPrice && player.playerHealth != player.playerMaxHealth)
				{
					player.playerHealth = player.playerMaxHealth;
					player.cash -= healPrice;
				}
			}
		}
		else
		{
			element->setFillColor(sf::Color::White);
		}
	}
	
}

void Menu::updateMenu(sf::Window* target, bool& pauseGame, sf::Event& event)
{
	updateText();
	updateMenuOptions(target, pauseGame, event);
}

void Menu::drawMenu(sf::RenderTarget* target)
{
	target->draw(menuSprite);
	for (auto& element : menuOptions)
	{
		target->draw(*element);
	}
}
