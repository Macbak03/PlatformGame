#include "Player.h"
#include <iostream>

Player::Player(Node* parentNode) : Node(parentNode)
{
	playerSize = sf::Vector2f(85.f, 85.f);
	facingRight = true;
	facingLeft = false;
	playerSpeed = 7.f;
	onGround = false;
	startJumpTimer = false;
	jumpTimer = 0.5f;
	healthBar.getSprite().scale(5.f, 3.f);
	initShape();
	spawnPlayer();
	initPhysics();
	initWeapon();
}


//SHAPE
void Player::loadTextures()
{
	playerTexture = new sf::Texture;
	if (!playerTexture->loadFromFile("Textures/player_right.png"))
	{
		std::cerr << "Could not load player_right texture" << std::endl;
	}
}


void Player::initShape()
{
	loadTextures();
	playerSprite.setTexture(*playerTexture);
	playerSprite.setScale(sf::Vector2f(playerSize.x/playerTexture->getSize().x, playerSize.y/playerTexture->getSize().y));
}
 
//END SHAPE

//PHYSICS
void Player::initPhysics()
{
	terminalVelocity = 20.f;
	gravity = 50.f;
	velocity = sf::Vector2f(playerSpeed, 0.f);
	jumpSpeed = 15.f;
	//colider
	collider.size = sf::Vector2f(playerSize.x - 35.f, playerSize.y -15.f);
	collider.offset.x = - collider.size.x / 2 ;
	collider.offset.y = 10.f;
}

void Player::updatePhysics(float deltaTime)
{
	velocity.y += gravity* deltaTime;
	if (velocity.y >= terminalVelocity)
	{
		velocity.y = terminalVelocity;
	}
}
Collider& Player::getCollider()
{
	return collider;
}
//END PHYSICS

//WEAPON STUFF
void Player::initWeapon()
{
	weapon = new Pistol(this, bullets);
}

void Player::changeWeapon()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		delete weapon;
		weapon = new Rifle(this, bullets);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		delete weapon;
		weapon = new SniperRifle(this, bullets);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		delete weapon;
		weapon = new Shotgun(this, bullets);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		delete weapon;
		weapon = new Pistol(this, bullets);
	}
}
Weapon* Player::getWeapon()
{
	return weapon;
}
//END WEAPON STUFF


//PLAYER POSITIONING
void Player::spawnPlayer()
{
	sf::Vector2f playerSpawn = sf::Vector2f(600.f, 0.f);
	setLocalPosition(playerSpawn);
}

void Player::movePlayer(float deltaTime)
{
	
	//move left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -playerSpeed;
		auto horizontalVelocity = sf::Vector2f(velocity.x, 0.f);
		move(horizontalVelocity);
		if (facingRight)
		{
			facingRight = false;
			flipX();
			facingLeft = true;
		}
	}
	//move right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = playerSpeed;
		auto horizontalVelocity = sf::Vector2f(velocity.x, 0.f);
		move(horizontalVelocity);
		if (facingLeft)
		{
			facingRight = true;
			flipX();
			facingLeft = false;
		}
	}
	//jump
	float jumpDeload = 0.5f;
	jumpTimer += deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround)
	{
		if (jumpTimer >= jumpDeload)
		{
			onGround = false;
			velocity.y = -jumpSpeed;
			jumpTimer = 0.f;
			startJumpTimer = false;
		}
	}
	//gravity
	if (!onGround)
	{
		auto verticalVelocity = sf::Vector2f(0.f, velocity.y);
		move(verticalVelocity);
	}
}

sf::Vector2f Player::getPosition()
{
	return playerSprite.getPosition();
}
//END PLAYER POSITIONING



//PLAYER COLLISION
void Player::updateBounceCollision(sf::RenderTarget* target, std::vector<Platform*> platforms)
{
	sf::Vector2f playerGlobalPosition = getGlobalPosition();
	this->setOrigin(playerSize.x / 2.f, 0.f);
	float playerTop = playerGlobalPosition.y + collider.offset.y;
	float playerBottom = playerTop + collider.size.y;
	float playerLeft = playerGlobalPosition.x + collider.offset.x;
	float playerRight = playerLeft + collider.size.x;
	float floorHeight = 90.f;
	
	//left
	if (playerLeft <= 0.f)
	{
		playerGlobalPosition.x = - collider.offset.x;
	}
	//right
	if (playerRight >= target->getSize().x)
	{
		playerGlobalPosition.x = target->getSize().x + collider.offset.x;
	}
	//bottom
	
	if (playerBottom + floorHeight >= target->getSize().y)
	{
		playerGlobalPosition.y = target->getSize().y - collider.size.y -floorHeight;
		onGround = true;
	}
	else 
	{ 
		onGround = false;
	}
	//collision with platforms
	Collider groundCollider = Collider(collider);
	groundCollider.offset.y += 2.f;
	Collider topCollider = Collider(collider);
	topCollider.offset.y -= 2.f;
	for (auto& element : platforms)
	{	
		sf::Vector2f platformGlobalPosition = element->getGlobalPosition();
		Collider platformCollider = element->getCollider();
		while (collider.xCausesCollision(playerGlobalPosition, platformGlobalPosition, platformCollider, velocity.x))
		{
			playerGlobalPosition.x -= Utils::sgn(velocity.x);
		}
		while (collider.yCausesCollision(playerGlobalPosition, platformGlobalPosition, platformCollider, velocity.y))
		{
			playerGlobalPosition.y -= Utils::sgn(velocity.y);
		}
		if (groundCollider.yCausesCollision(playerGlobalPosition, platformGlobalPosition, platformCollider, velocity.y +1.f))
		{
			onGround = true;
		}
		if (topCollider.yCausesCollision(playerGlobalPosition, platformGlobalPosition, platformCollider, velocity.y + 1.f))
		{
			velocity.y = 0;
		}
	}
	if (onGround)
	{
		velocity.y = 0.f;
	}
	setLocalPosition(playerGlobalPosition);
}
//END PLAYER COLLISION


//UPDATE AND RENDER
void Player::updatePlayer(sf::RenderTarget* target, float deltaTime, std::vector<Platform*> platforms, Node* parentNode)
{	
	movePlayer(deltaTime);
	updateBounceCollision(target, platforms);
	updatePhysics(deltaTime);
	changeWeapon();
	weapon->updateWeapon(target, getPosition(), facingRight, facingLeft, deltaTime, parentNode, this, collider);
	healthBar.updateHealthBarAnimation(0, false, sf::Vector2f(getGlobalPosition().x, getGlobalPosition().y - 10.f));
	//std::cout << getLocalPosition().x << "        " << getLocalPosition().y << std::endl
}

void Player::drawCollider(sf::RenderTarget* target)
{
	sf::RectangleShape colliderShape;
	colliderShape.setSize(collider.size);
	colliderShape.setPosition(getGlobalPosition() + collider.offset);
	target->draw(colliderShape);
}

void Player::renderHealthBar(sf::RenderTarget* target)
{
	healthBar.drawHealthBar(target);
}

void Player::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(playerSprite, transform);
}
//END UPDATE AND RENDER	