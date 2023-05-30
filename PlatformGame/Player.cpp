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
}


void Player::initShape()
{
	loadTextures();
	playerSprite.setTexture(*playerTextureRight);
	playerSprite.setScale(sf::Vector2f(playerSize.x/playerTextureRight->getSize().x, playerSize.y/playerTextureRight->getSize().y));
}
 
const sf::Sprite& Player::getShape() const
{
	return playerSprite;
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
	collider.size = playerSize;
	collider.offset.x = - collider.size.x / 2;
}

void Player::updatePhysics(float deltaTime)
{
	velocity.y += gravity* deltaTime;
	if (velocity.y >= terminalVelocity)
	{
		velocity.y = terminalVelocity;
	}
}
//END PHYSICS

//WEAPON STUFF
void Player::initWeapon()
{
	weapon = new Pistol(this);
}

void Player::changeWeapon()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		delete weapon;
		weapon = new Rifle(this);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		delete weapon;
		weapon = new SniperRifle(this);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		delete weapon;
		weapon = new Shotgun(this);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		delete weapon;
		weapon = new Pistol(this);
	}
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

const sf::Vector2f& Player::getPosition() const
{
	return playerSprite.getPosition();
}
//END PLAYER POSITIONING



//PLAYER COLLISION
void Player::updateBounceCollision(sf::RenderTarget* target, std::vector<Platform*> platforms)
{
	sf::Vector2f playerGlobalPosition = getGlobalPosition();
	this->setOrigin(collider.size.x / 2.f, 0.f);
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
			onGround = true;
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
	weapon->updateWeapon(target, getPosition(), facingRight, facingLeft, deltaTime, parentNode);
	//std::cout << getLocalPosition().x << "        " << getLocalPosition().y << std::endl;
}


void Player::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(playerSprite, transform);

}
//END UPDATE AND RENDER	