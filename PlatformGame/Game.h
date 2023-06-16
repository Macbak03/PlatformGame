#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Level.h"
#include "Bandit.h"
#include "Marauder.h"
#include "Thug.h"
#include "Enemies.h"
#include "Menu.h"

class Game
{
private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	std::vector<sf::Event> events;
	sf::Clock clock;
	float deltaTime;
	Menu* menu;
	
	sf::Texture menuTexture;
	sf::Sprite menuSprite;

	sf::Font font;
	sf::Text pointsText;
	sf::Text ammoText;
	sf::Text cashText;
	sf::Text gameOverText;
	sf::Text winText;
	sf::Text reloadText;

	float* bossHealth;

	Level level;
	Player player;
	Enemies enemies;
	void initVariables();
	void initWindow();
	bool pauseGame;

public:
	Game();
	virtual ~Game();
	const bool getWindowIsOpen();
	void loadFont();
	void loadTexture();
	void initBackground();
	void initText();
	void updateGui();
	void renderGui(sf::RenderTarget* target);
	bool endGame();
	void initLevel();
	void pollEvents();
	void renderBackground(sf::RenderTarget* target);
	void update();
	void render();
	void handleMenu();
};

