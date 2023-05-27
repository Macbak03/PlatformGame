#include "Game.h"
#include <iostream>

void Game::initVariables()
{
	window = nullptr;
	endGame = false;
	deltaTime = 0.f;
}

void Game::initWindow()
{
	videoMode.width = 1280;
	videoMode.height = 720;
	window = new sf::RenderWindow(videoMode, "The Game", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
}

void Game::loadTexture()
{
	if (!backgroundTexture.loadFromFile("Textures/desert_BG.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Game::initBackground()
{
	backgroundSprite.setTexture(backgroundTexture);
	float scaleX = static_cast<float>(videoMode.width) / backgroundTexture.getSize().x;
	float scaleY = static_cast<float>(videoMode.height) / backgroundTexture.getSize().y;
	backgroundSprite.setScale(sf::Vector2f(scaleX, scaleY));
}

void Game::initLevel()
{
	//spawn platforms
	level.addPlatform(sf::Vector2f(450, 550.f));
	level.addPlatform(sf::Vector2f(600.f, 500.f));
	level.addPlatform(sf::Vector2f(200.f, 450.f));
	level.addPlatform(sf::Vector2f(1000.f, 525.f));
}

void Game::initEnemies()
{
	enemy = new Bandit;
	enemyScale = enemy->getEnemyScale();
	enemy->spawnEnemy(sf::Vector2f(450.f, 480.f));
}


Game::Game()
{
	initVariables();
	initWindow();
	loadTexture();
	initBackground();
	initLevel();
	initEnemies();
}

Game::~Game()
{
	delete window;
}

//Accessors
const bool Game::getWindowIsOpen()
{
	return window->isOpen();
}


void Game::pollEvents()
{
	deltaTime = clock.restart().asSeconds();
	//Event polling
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->close();
				break;
			}
		}
	}
}


void Game::update()
{
	pollEvents();
	player.updatePlayer(window, deltaTime, level.getPlatforms());
	enemy->updateEnemy(window, deltaTime, level.getPlatforms(), enemyScale);
	enemy->updateEnemyAnimation(deltaTime);
}

void Game::renderBackground(sf::RenderTarget* target)
{
	target->draw(backgroundSprite);
}

void Game::render()
{
	/*
		-clear all frame
		-render objects
		-display frame in window

		Renders the game objects
	*/
	window->clear();
	//Draw background
	renderBackground(window);
	//Draw level
	level.renderLevel(window);
	//Draw player
	player.renderPlayer(window);
	enemy->renderEnemy(window);
	window->display();
}