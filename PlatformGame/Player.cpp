#include "Player.h"
#include <iostream>

Player::Player()
{
	this->facingRight = true;
	this->facingLeft = false;
	this->playerSpeed = 7.f;
	this->onGround = false;
	this->initShape();
	this->spawnPlayer();
	this->initPhysics();
	this->initWeapon();
}


//SHAPE
void Player::loadTextures()
{
	this->playerTextureRight = new sf::Texture;
	this->playerTextureLeft = new sf::Texture;
	if (!playerTextureRight->loadFromFile("Textures/player_right.png"))
	{
		std::cerr << "Could not load player_right texture" << std::endl;
	}
	else if (!playerTextureLeft->loadFromFile("Textures/player_left.png"))
	{
		std::cerr << "Could not load player_left texture" << std::endl;
	}
}


void Player::initShape()
{
	this-> loadTextures();
	//playerSprite.setOrigin((sf::Vector2f)playerTextureRight->getSize() / 2.f);
	this->playerSprite.setTexture(*playerTextureRight);
	this->playerSprite.setScale(sf::Vector2f(0.045f, 0.045f));
}

sf::Sprite Player::getShape()
{
	return this->playerSprite;
}
//SHAPE

//PHYSICS
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
//PHYSICS

//WEAPON STUFF
void Player::initWeapon()
{
	this->weapon = new Pistol;
	
}

void Player::changeWeapon()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		delete weapon;
		this->weapon = new Rifle;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		delete weapon;
		this->weapon = new SniperRifle;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		delete weapon;
		this->weapon = new Shotgun;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		delete weapon;
		this->weapon = new Pistol;
	}
}
//WEAPON STUFF


//PLAYER POSITIONING
void Player::spawnPlayer()
{
	this->playerSprite.setPosition(sf::Vector2f(600.f, 0.f));
}

void Player::movePlayer()
{
	
	//move left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		facingRight = false;
		this->playerSprite.setTexture(*playerTextureLeft);
		this->velocity.x = -7.f;
		this->playerSprite.move(this->velocity.x, 0.f);
		facingLeft = true;
	}
	//move right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		facingLeft = false;
		this->playerSprite.setTexture(*playerTextureRight);
		this->velocity.x = 7.f;
		this->playerSprite.move(this->velocity.x, 0.f);
		facingRight = true;
	}
	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround)
	{
		this->onGround = false;
		this->velocity.y = -jumpSpeed;
	}
	//gravity
	if (!onGround)
	{
		this->playerSprite.move(0.f, velocity.y);
	}
}

sf::Vector2f Player::getPosition()
{
	return this->playerSprite.getPosition();
}
//PLAYER POSITIONING



//PLAYER COLLISION
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
	for (auto& element : platforms)
	{	
		
		//player left with platform right
		if (playerSprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds()) 
			&& playerLeft <= element.getShape().getGlobalBounds().left + element.getShape().getGlobalBounds().width + 10.f 
			&& playerLeft >= element.getShape().getGlobalBounds().left + element.getShape().getGlobalBounds().width - 10.f)
		{
			this->playerSprite.setPosition(element.getShape().getGlobalBounds().left + element.getShape().getGlobalBounds().width, playerTop);
		}
		if (playerSprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds()) 
			&& playerRight >= element.getShape().getGlobalBounds().left - 10.f 
			&& playerRight <= element.getShape().getGlobalBounds().left + 10.f)
		{
			this->playerSprite.setPosition(element.getShape().getGlobalBounds().left - element.getShape().getGlobalBounds().width, playerTop);
		}
		//player top with platform bottom
		if (playerSprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds())
			&& playerTop <= element.getShape().getGlobalBounds().top + element.getShape().getGlobalBounds().height + 30.f
			&& playerTop >= element.getShape().getGlobalBounds().top + element.getShape().getGlobalBounds().height - 30.f)
		{
			velocity.y = 0.f;
		}
		//player bottom with platform top
		if (playerSprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds()) && velocity.y > 0)
		{
			this->playerSprite.setPosition(this->playerSprite.getGlobalBounds().left, element.getShape().getGlobalBounds().top - this->playerSprite.getGlobalBounds().height + 5.f);
			onGround = true;
			velocity.y = 0.f;
		}
		
	}
}
//PLAYER COLLISION


//UPDATE AND RENDER
void Player::updatePlayer(const sf::RenderTarget* target, float deltaTime, std::vector<Platform> platforms)
{	
	this->movePlayer();
	this->updateBounceCollision(target, platforms);
	this->updatePhysics(deltaTime);
	this->changeWeapon();
	this->weapon->updateWeapon(target, this->getPosition(), facingRight, facingLeft);
}

void Player::renderPlayer(sf::RenderTarget* target)
{
	target->draw(this->playerSprite);
	this->weapon->renderWeapon(target);
}
//UPDATE AND RENDER	