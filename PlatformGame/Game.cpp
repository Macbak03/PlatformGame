#include "Game.h"
#include <iostream>
#include <sstream>

void Game::initVariables()
{
	window = nullptr;
	deltaTime = 0.f;
}

void Game::initWindow()
{
	videoMode.width = 1600;
	videoMode.height = 900;
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

void Game::loadFont()
{
	if (!font.loadFromFile("Fonts/DomBold BT.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
}

void Game::initBackground()
{
	backgroundSprite.setTexture(backgroundTexture);
	float scaleX = static_cast<float>(videoMode.width) / backgroundTexture.getSize().x;
	float scaleY = static_cast<float>(videoMode.height) / backgroundTexture.getSize().y;
	backgroundSprite.setScale(sf::Vector2f(scaleX, scaleY));
}

void Game::initText()
{
	loadFont();
	//Points
	pointsText.setFont(font);
	pointsText.setCharacterSize(24);
	pointsText.setFillColor(sf::Color::White);
	pointsText.setOutlineColor(sf::Color::Black);
	pointsText.setOutlineThickness(2);
	pointsText.setPosition(sf::Vector2f(3.f, 0.f));
	//Cash
	cashText.setFont(font);
	cashText.setCharacterSize(24);
	cashText.setFillColor(sf::Color::White);
	cashText.setOutlineColor(sf::Color::Black);
	cashText.setOutlineThickness(2);
	cashText.setPosition(sf::Vector2f(3.f, 56.f));
	//Ammo
	ammoText.setFont(font);
	ammoText.setCharacterSize(24);
	ammoText.setFillColor(sf::Color::White);
	ammoText.setOutlineColor(sf::Color::Black);
	ammoText.setOutlineThickness(2);
	ammoText.setPosition(sf::Vector2f(3.f, 28.f));
	//Game Over
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(2);
	gameOverText.setString("GAME OVER. PRESS ESC");
	gameOverText.setPosition(sf::Vector2f(300.f, 400.f));
}

void Game::updateGui()
{
	std::stringstream points_ss;
	std::stringstream cash_ss;
	std::stringstream ammo_ss;

	points_ss << "Points: " << player.points;
	pointsText.setString(points_ss.str());

	cash_ss << "Cash: " << player.cash;
	cashText.setString(cash_ss.str());

	ammo_ss << "Ammo: " << player.getWeapon()->getAmmo() << "/" << player.getWeapon()->getMagazineSize();
	ammoText.setString(ammo_ss.str());
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(pointsText);
	target->draw(cashText);
	target->draw(ammoText);
	if (endGame())
	{
		target->draw(gameOverText);
	}
}

bool Game::endGame()
{
	if (player.playerHealth < 0) {
		return true;
	}
	else
	{
		return false;
	}
}

void Game::initLevel()
{
	
	//spawn platforms
	Platform* platform1 = level.addPlatform(sf::Vector2f(50, 750.f), &level);
	Platform* platform2 = level.addPlatform(sf::Vector2f(70.f, 200.f), &level);
	Platform* platform3 = level.addPlatform(sf::Vector2f(330.f, 300.f), &level);
	Platform* platform4 = level.addPlatform(sf::Vector2f(350.f, 650.f), &level);
	Platform* platform5 = level.addPlatform(sf::Vector2f(625.f, 180.f), &level);
	Platform* platform6 = level.addPlatform(sf::Vector2f(650.f, 370.f), &level);
	Platform* platform7 = level.addPlatform(sf::Vector2f(670, 550.f), &level);
	Platform* platform8 = level.addPlatform(sf::Vector2f(700.f, 720.f), &level);
	Platform* platform9 = level.addPlatform(sf::Vector2f(920.f, 125.f), &level);
	Platform* platform10 = level.addPlatform(sf::Vector2f(930.f, 470.f), &level);
	Platform* platform11 = level.addPlatform(sf::Vector2f(1100.f, 330.f), &level);
	Platform* platform12 = level.addPlatform(sf::Vector2f(1200.f, 600.f), &level);
	Platform* platform13 = level.addPlatform(sf::Vector2f(1300.f, 100.f), &level);
	Platform* platform14 = level.addPlatform(sf::Vector2f(1450.f, 470.f), &level);
	
	Enemy* bandit1 = new Bandit(platform2, &level);
	bandit1->spawnEnemy();
	enemies.addEnemy(bandit1);
	Enemy* bandit2 = new Bandit(platform14, &level);
	bandit2->spawnEnemy();
	enemies.addEnemy(bandit2);
	Enemy* bandit3 = new Bandit(platform10, &level);
	bandit3->spawnEnemy();
	enemies.addEnemy(bandit3);
	Enemy* bandit4 = new Bandit(platform4, &level);
	bandit4->spawnEnemy();
	enemies.addEnemy(bandit4);
	Enemy* marauder1 = new Marauder(platform3, &level);
	marauder1->spawnEnemy();
	enemies.addEnemy(marauder1);
	Enemy* marauder2 = new Marauder(platform12, &level);
	marauder2->spawnEnemy();
	enemies.addEnemy(marauder2);
	Enemy* marauder3 = new Marauder(platform9, &level);
	marauder3->spawnEnemy();
	enemies.addEnemy(marauder3);
	Enemy* boss = new Thug(platform13, &level);
	boss->spawnEnemy();
	enemies.addEnemy(boss);
}



Game::Game() : player(&level)
{
	initVariables();
	initWindow();
	loadTexture();
	initBackground();
	initLevel();
	initText();
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
	if (!endGame())
	{
		player.updatePlayer(window, deltaTime, level.getPlatforms(), &level, enemies.getBullets());
		for (auto& element : enemies.getEnemies())
		{
			element->updateEnemy(window, deltaTime, &level);
		}
		enemies.updateCollisions(player.getBullets(), player.getWeapon(), player.cash, player.points);
		enemies.update(window, deltaTime);
		updateGui();
	}
}

void Game::renderBackground(sf::RenderTarget* target)
{
	target->draw(backgroundSprite);
}

void Game::render()
{
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
	renderGui(window);
	window->display();
}