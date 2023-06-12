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
	Platform* platfromGrass1 = level.addPlatform(sf::Vector2f(450, 550.f), &level);
	Platform* platfromGrass2 = level.addPlatform(sf::Vector2f(600.f, 500.f), &level);
	Platform* platfromGrass3 = level.addPlatform(sf::Vector2f(200.f, 450.f), &level);
	Platform* platfromGrass4 = level.addPlatform(sf::Vector2f(1000.f, 525.f), &level);
	Enemy* enemy1 = new Bandit(platfromGrass1, &level);
	enemy1->spawnEnemy();
	enemies.addEnemy(enemy1);
	Enemy* enemy2 = new Bandit(platfromGrass4, &level);
	enemy2->spawnEnemy();
	enemies.addEnemy(enemy2);
	Enemy* enemy3 = new Marauder(platfromGrass3, &level);
	enemy3->spawnEnemy();
	enemies.addEnemy(enemy3);
}

void Game::initEnemies()
{

}


Game::Game() : player(&level)
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
	player.updatePlayer(window, deltaTime, level.getPlatforms(), &level);
	for (auto& element : enemies.getEnemies())
	{
		element->updateEnemy(window, deltaTime, player.getWeapon()->damage, &level);
	}
	enemies.updateCollisions(player.getWeapon()->getBullets(), player.getWeapon());
	enemies.update(window, &player, player.getCollider(), deltaTime);
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
	//for (auto& element : enemies.getEnemies())
	//{
	//	element->drawCollider(window);
	//}
	//player.getWeapon()->getBullets().renderCollider(window);
	//player.drawCollider(window);
	level.renderLevel(*window);
	for (auto& element : enemies.getEnemies())
	{
		element->renderHealthBar(window);
	}
	player.renderHealthBar(window);
	window->display();
}