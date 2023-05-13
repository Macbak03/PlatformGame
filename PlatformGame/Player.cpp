#include "Player.h"
#include <iostream>

Player::Player()
{
	this->playerSpeed = 7.f;
	this->onGround = false;
	this->initShape();
	this->spawnPlayer();
	this->initPhysics();
}

void Player::loadTextures()
{
	playerTextureRight = new sf::Texture;
	playerTextureLeft = new sf::Texture;
	if (!playerTextureRight->loadFromFile("Textures/player_right3.png"))
	{
		std::cerr << "Could not load player_right texture" << std::endl;
	}
	else if (!playerTextureLeft->loadFromFile("Textures/player_left3.png"))
	{
		std::cerr << "Could not load player_left texture" << std::endl;
	}
}


void Player::initShape()
{
	this-> loadTextures();
	this->playerSprite.setTexture(*playerTextureRight);
	this->playerSprite.setScale(sf::Vector2f(0.045f, 0.045f));
}

void Player::initPhysics()
{
	this->terminalVelocity = 20.f;
	this->gravity = 50.f;
	this->velocity = sf::Vector2f(this->playerSpeed, 0.f);
	this->jumpSpeed = 15.f;
}

void Player::updatePhysics(float deltaTime)
{
	this->velocity.y += this->gravity* deltaTime;
	if (this->velocity.y >= terminalVelocity)
	{
		velocity.y = terminalVelocity;
	}
}

void Player::spawnPlayer()
{
	this->playerSprite.setPosition(sf::Vector2f(600.f, 0.f));
}

void Player::movePlayer()
{
	
	//move left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->playerSprite.setTexture(*playerTextureLeft);
		this->velocity.x = -7.f;
		this->playerSprite.move(this->velocity.x, 0.f);
	}
	//move right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->playerSprite.setTexture(*playerTextureRight);
		this->velocity.x = 7.f;
		this->playerSprite.move(this->velocity.x, 0.f);
	}
	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround)
	{
		onGround = false;
		velocity.y = -jumpSpeed;
	}
	//gravity
	if (!onGround)
	{
		this->playerSprite.move(0.f, velocity.y);
	}
}

sf::Sprite Player::getShape()
{
	return playerSprite;
}

sf::Vector2f Player::getPosition()
{
	return playerSprite.getPosition();
}

void Player::updateBounceCollision(const sf::RenderTarget* target, std::vector<Platform> platforms)
{
	float playerTop = this->playerSprite.getGlobalBounds().top;
	float playerBottom = playerTop + this->playerSprite.getGlobalBounds().height;
	float playerLeft = this->playerSprite.getGlobalBounds().left;
	float playerRight = playerLeft + this->playerSprite.getGlobalBounds().width;
	//left
	if (playerLeft <= 0.f)
	{
		this->playerSprite.setPosition(0.f, playerTop);
	}
	//right
	if (playerRight >= target->getSize().x)
	{
		this->playerSprite.setPosition(target->getSize().x - this->playerSprite.getGlobalBounds().width, playerTop);
	}
	//bottom
	float floorHeight = 90.f;
	if (playerBottom + floorHeight >= target->getSize().y)
	{
		this->playerSprite.setPosition(this->playerSprite.getGlobalBounds().left, target->getSize().y - this->playerSprite.getGlobalBounds().height -floorHeight);
		onGround = true;
	}
	else 
	{ 
		onGround = false;
	}
	//collision with platforms
	bool playerBottomCollision = false;
	bool playerTopCollision = false;
	bool playerLeftCollision = false;
	bool playerRightCollision = false;
	for (auto& element : platforms)
	{
		//player bottom with platform top
		/*if (playerSprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds()) 
			&& playerBottom >= element.getShape().getGlobalBounds().top - 17.f 
			&& playerBottom <= element.getShape().getGlobalBounds().top + 17.f)
		{
			this->playerSprite.setPosition(this->playerSprite.getGlobalBounds().left, element.getShape().getGlobalBounds().top -this->playerSprite.getGlobalBounds().height);
			onGround = true;
			velocity.y = 0.f;
		}*/
		
		
		//player left with platform right
		if (playerSprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds()) 
			&& playerLeft <= element.getShape().getGlobalBounds().left + element.getShape().getGlobalBounds().width + 10.f 
			&& playerLeft >= element.getShape().getGlobalBounds().left + element.getShape().getGlobalBounds().width - 10.f)
		{
			playerLeftCollision = true;
			this->playerSprite.setPosition(element.getShape().getGlobalBounds().left + element.getShape().getGlobalBounds().width, playerTop);
			velocity.x = 0.f;
		}
		//player right with platform left
		if (playerSprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds()) 
			&& playerRight >= element.getShape().getGlobalBounds().left - 10.f 
			&& playerRight <= element.getShape().getGlobalBounds().left + 10.f)
		{
			playerRightCollision;
			this->playerSprite.setPosition(element.getShape().getGlobalBounds().left - element.getShape().getGlobalBounds().width, playerTop);
			velocity.x = 0.f;
		}
		//player top with platform bottom
		if (playerSprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds())
			&& playerTop <= element.getShape().getGlobalBounds().top + element.getShape().getGlobalBounds().height + 30.f
			&& playerTop >= element.getShape().getGlobalBounds().top + element.getShape().getGlobalBounds().height - 30.f)
		{
			playerTopCollision = true;
			velocity.y = 0.f;
		}
		if (playerSprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds()) && velocity.y > 0 
			&& !playerTopCollision && !playerLeftCollision && !playerRightCollision)
		{
			this->playerSprite.setPosition(this->playerSprite.getGlobalBounds().left, element.getShape().getGlobalBounds().top - this->playerSprite.getGlobalBounds().height + 5.f);
			onGround = true;
			velocity.y = 0.f;
		}
		
	}
}


void Player::updatePlayer(const sf::RenderTarget* target, float deltaTime, std::vector<Platform> platforms)
{	
	//std::cout << playerSprite.getGlobalBounds().top + this->playerSprite.getGlobalBounds().height << "        "<< platforms[1].getShape().getGlobalBounds().top<<std::endl;
	//std::cout << playerSprite.getGlobalBounds().top << "        " << platforms[2].getShape().getGlobalBounds().top + platforms[2].getShape().getGlobalBounds().height << std::endl;
	this->movePlayer();
	this->updateBounceCollision(target, platforms);
	this->updatePhysics(deltaTime);
	
}

void Player::renderPlayer(sf::RenderTarget* target)
{
	target->draw(this->playerSprite);
}
