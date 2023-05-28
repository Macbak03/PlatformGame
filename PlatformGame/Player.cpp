#include "Player.h"
#include <iostream>

Player::Player()
{
	facingRight = true;
	facingLeft = false;
	playerSpeed = 7.f;
	onGround = false;
	initShape();
	spawnPlayer();
	initPhysics();
	initWeapon();
}


//SHAPE
void Player::loadTextures()
{
	playerTextureRight = new sf::Texture;
	playerTextureLeft = new sf::Texture;
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
	loadTextures();
	playerSprite.setTexture(*playerTextureRight);
	playerSprite.setScale(sf::Vector2f(0.1f, 0.1f));
}

const sf::Sprite& Player::getShape() const
{
	return playerSprite;
}
//SHAPE

//PHYSICS
void Player::initPhysics()
{
	terminalVelocity = 20.f;
	gravity = 50.f;
	velocity = sf::Vector2f(playerSpeed, 0.f);
	jumpSpeed = 15.f;
}

void Player::updatePhysics(float deltaTime)
{
	velocity.y += gravity* deltaTime;
	if (velocity.y >= terminalVelocity)
	{
		velocity.y = terminalVelocity;
	}
}
//PHYSICS

//WEAPON STUFF
void Player::initWeapon()
{
	weapon = new Pistol;
}

void Player::changeWeapon()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		delete weapon;
		weapon = new Rifle;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		delete weapon;
		weapon = new SniperRifle;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		delete weapon;
		weapon = new Shotgun;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		delete weapon;
		weapon = new Pistol;
	}
}
//WEAPON STUFF


//PLAYER POSITIONING
void Player::spawnPlayer()
{
	playerSprite.setPosition(sf::Vector2f(600.f, 0.f));
}

void Player::movePlayer()
{
	
	//move left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		facingRight = false;
		playerSprite.setTexture(*playerTextureLeft);
		velocity.x = -7.f;
		playerSprite.move(velocity.x, 0.f);
		facingLeft = true;
	}
	//move right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		facingLeft = false;
		playerSprite.setTexture(*playerTextureRight);
		velocity.x = 7.f;
		playerSprite.move(velocity.x, 0.f);
		facingRight = true;
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
		playerSprite.move(0.f, velocity.y);
	}
}

const sf::Vector2f& Player::getPosition() const
{
	return playerSprite.getPosition();
}
//PLAYER POSITIONING



//PLAYER COLLISION
void Player::updateBounceCollision(const sf::RenderTarget* target, std::vector<Platform*> platforms)
{
	float playerTop = playerSprite.getGlobalBounds().top;
	float playerBottom = playerTop + playerSprite.getGlobalBounds().height;
	float playerLeft = playerSprite.getGlobalBounds().left;
	float playerRight = playerLeft + playerSprite.getGlobalBounds().width;
	//left
	if (playerLeft <= 0.f)
	{
		playerSprite.setPosition(0.f, playerTop);
	}
	//right
	if (playerRight >= target->getSize().x)
	{
		playerSprite.setPosition(target->getSize().x - playerSprite.getGlobalBounds().width, playerTop);
	}
	//bottom
	float floorHeight = 90.f;
	if (playerBottom + floorHeight >= target->getSize().y)
	{
		playerSprite.setPosition(playerSprite.getGlobalBounds().left, target->getSize().y - playerSprite.getGlobalBounds().height -floorHeight);
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
		if (playerSprite.getGlobalBounds().intersects(element->getShape().getGlobalBounds()) 
			&& playerLeft <= element->getShape().getGlobalBounds().left + element->getShape().getGlobalBounds().width + 10.f
			&& playerLeft >= element->getShape().getGlobalBounds().left + element->getShape().getGlobalBounds().width - 10.f)
		{
			playerSprite.setPosition(element->getShape().getGlobalBounds().left + element->getShape().getGlobalBounds().width, playerTop);
		}
		//player right with platform left
		if (playerSprite.getGlobalBounds().intersects(element->getShape().getGlobalBounds())
			&& playerRight >= element->getShape().getGlobalBounds().left - 10.f
			&& playerRight <= element->getShape().getGlobalBounds().left + 10.f)
		{
			playerSprite.setPosition(element->getShape().getGlobalBounds().left - playerSprite.getGlobalBounds().width, playerTop);
		}
		//player top with platform bottom
		if (playerSprite.getGlobalBounds().intersects(element->getShape().getGlobalBounds())
			&& playerTop <= element->getShape().getGlobalBounds().top + element->getShape().getGlobalBounds().height + 30.f
			&& playerTop >= element->getShape().getGlobalBounds().top + element->getShape().getGlobalBounds().height - 30.f)
		{
			velocity.y = 0.f;
		}
		//player bottom with platform top
		if (playerSprite.getGlobalBounds().intersects(element->getShape().getGlobalBounds()) && velocity.y > 0)
		{
			playerSprite.setPosition(playerSprite.getGlobalBounds().left, element->getShape().getGlobalBounds().top - playerSprite.getGlobalBounds().height + 5.f);
			onGround = true;
			velocity.y = 0.f;
		}
		
	}
}
//PLAYER COLLISION


//UPDATE AND RENDER
void Player::updatePlayer(const sf::RenderTarget* target, float deltaTime, std::vector<Platform*> platforms)
{	
	movePlayer();
	updateBounceCollision(target, platforms);
	updatePhysics(deltaTime);
	changeWeapon();
	weapon->updateWeapon(target, getPosition(), facingRight, facingLeft, deltaTime);
}

void Player::renderPlayer(sf::RenderTarget* target)
{
	target->draw(playerSprite);
	weapon->renderWeapon(target);
}
//UPDATE AND RENDER	