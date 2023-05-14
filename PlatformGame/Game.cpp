#include "Game.h"
#include <iostream>

void Game::initVariables()
{
	this->window = nullptr;
	this->endGame = false;
	this->deltaTime = 0.f;
}

void Game::initWindow()
{
	this->videoMode.width = 1280;
	this->videoMode.height = 720;
	this->window = new sf::RenderWindow(this->videoMode, "The Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::loadTexture()
{
	if (!this->backgroundTexture.loadFromFile("Textures/desert_BG.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Game::initBackground()
{
	this->backgroundSprite.setTexture(backgroundTexture);
	float scaleX = static_cast<float>(this->videoMode.width) / backgroundTexture.getSize().x;
	float scaleY = static_cast<float>(this->videoMode.height) / backgroundTexture.getSize().y;
	this->backgroundSprite.setScale(sf::Vector2f(scaleX, scaleY));
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
	this->initLevel();
	this->initVariables();
	this->initWindow();
	this->loadTexture();
	this->initBackground();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::getWindowIsOpen()
{
	return this->window->isOpen();
}


void Game::pollEvents()
{
	deltaTime = clock.restart().asSeconds();
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				break;
			}
		}
	}
}


void Game::update()
{
	this->pollEvents();
	this->player.updatePlayer(this->window, deltaTime, level.getPlatforms());
	
	//std::cout << player.getShape().getGlobalBounds().top << std::endl;
	
}

void Game::renderBackground(sf::RenderTarget* target)
{
	target->draw(this->backgroundSprite);
}

void Game::render()
{
	/*
		-clear all frame
		-render objects
		-display frame in window

		Renders the game objects
	*/
	this->window->clear();
	//Draw background
	this->renderBackground(this->window);
	//Draw player
	this->player.renderPlayer(this->window);
	//Draw level
	this->level.renderLevel(this->window);
	//Draw Weapons

	this->window->display();
}