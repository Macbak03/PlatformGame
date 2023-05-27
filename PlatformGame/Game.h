#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Platform.h"
#include "Level.h"
#include "Pistol.h"
#include "Enemy.h"
#include "Bandit.h"

class Game
{
private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	bool endGame;
	sf::Clock clock;
	float deltaTime;
	
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;


	Player player;
	Level level;
	Enemy* enemy;
	sf::Vector2f enemyScale;
	void initVariables();
	void initWindow();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();
	//Accessors
	const bool getWindowIsOpen();
	//Functions
	void loadTexture();
	void initBackground();
	void initLevel();
	void initEnemies();
	void pollEvents();
	void renderBackground(sf::RenderTarget* target);
	void update();
	void render();
};

