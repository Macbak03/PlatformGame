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
	level.addPlatform(sf::Vector2f(400.f, 550.f));
	level.addPlatform(sf::Vector2f(600.f, 500.f));
	level.addPlatform(sf::Vector2f(200.f, 450.f));
	level.addPlatform(sf::Vector2f(1000.f, 525.f));
}

Game::Game()
{
	initLevel();
	initVariables();
	initWindow();
	loadTexture();
	initBackground();
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
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
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
	//Draw player
	player.renderPlayer(window);
	//Draw level
	level.renderLevel(window);
	//Draw bullets
	bullets.renderBullets(window);
	window->display();
}