#include "Player.h"
#include <iostream>

Player::Player(Node* parentNode) : Node(parentNode)
{
	playerSize = sf::Vector2f(105.f, 140.f);
	facingRight = true;
	facingLeft = false;
	playerSpeed = 420.f;
	onGround = false;
	startJumpTimer = false;
	jumpTimer = 0.5f;
	playerMaxHealth = 100;
	cash = 11110;
	points = 0;
	playerHealth = playerMaxHealth;
	playerColor = playerSprite.getColor();
	healthBar.getSprite().scale(5.f, 3.f);
	initShape(sf::Vector2u(6,2));
	spawnPlayer();
	initPhysics();
	initWeapon();
	initAnimation();
}


//SHAPE
void Player::loadTextures()
{
	playerTexture = new sf::Texture;
	if (!playerTexture->loadFromFile("Textures/animated_player1.png"))
	{
		std::cerr << "Could not load player_right texture" << std::endl;
	}
}


void Player::initShape(sf::Vector2u imageCount)
{
	loadTextures();
	playerSprite.setTexture(*playerTexture);
	//playerSprite.setScale(sf::Vector2f(playerSize.x/playerTexture->getSize().x, playerSize.y/playerTexture->getSize().y));
	playerSprite.setScale(sf::Vector2f((playerSize.x * imageCount.x) / playerTexture->getSize().x, (playerSize.y * imageCount.y) / playerTexture->getSize().y));
}
 
//END SHAPE

//PHYSICS
void Player::initPhysics()
{
	terminalVelocity = 1200.f;
	gravity = 3000.f;
	velocity = sf::Vector2f(playerSpeed, 0.f);
	jumpSpeed = 900.f;
	//colider
	collider.size = sf::Vector2f(playerSize.x - 55.f, playerSize.y -65.f);
	collider.offset.x = - collider.size.x / 2;
	collider.offset.y = 50.f;
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
Bullets& Player::getBullets()
{
	return bullets;
}
//END PHYSICS

//WEAPON STUFF
void Player::initWeapon()
{
	weapon = new Pistol(this, bullets);
	currentWeapon = "Current weapon: Pistol";
}

void Player::initAnimation()
{
	animation = new Animation(playerTexture, sf::Vector2u(6, 2), 0.3f);
}


void Player::changeToPistol()
{
	delete weapon;
	weapon = new Pistol(this, bullets);
	currentWeapon = "Current weapon: Pistol";
}

void Player::changeToRifle()
{
	delete weapon;
	weapon = new Rifle(this, bullets);
	currentWeapon = "Current weapon: Rifle";
}

void Player::changeToShotgun()
{
	delete weapon;
	weapon = new Shotgun(this, bullets);
	currentWeapon = "Current weapon: Shotgun";
}

void Player::changeToSniperRifle()
{
	delete weapon;
	weapon = new SniperRifle(this, bullets);
	currentWeapon = "Current weapon: Snper rifle";
}

void Player::updatePlayerAnimation(float deltaTime)
{
	setOrigin(playerSize.x / 4.f, 0.f);
	playerSprite.setTextureRect(animation->uvRec);
	currentAnimationFrame = animation->updateAnimation(1, deltaTime, isMoving);
	if (!isMoving)
	{
		animation->setCurrentImageX(0);
	}
	if (onGround)
	{
		if (currentAnimationFrame >= 3)
		{
			animation->setCurrentImageX(0);
		}
	}
	std::cout << currentAnimationFrame << std::endl;
}

Weapon* Player::getWeapon()
{
	return weapon;
}
//END WEAPON STUFF


//PLAYER POSITIONING
void Player::spawnPlayer()
{
	sf::Vector2f playerSpawn = sf::Vector2f(900.f,300.f);
	setLocalPosition(playerSpawn);
}

void Player::movePlayer(float deltaTime)
{
	isMoving = false;
	//move left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -playerSpeed;
		auto horizontalVelocity = sf::Vector2f(velocity.x, 0.f);
		move(horizontalVelocity.x * deltaTime, 0.f);
		isMoving = true;
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
		move(horizontalVelocity.x * deltaTime, 0.f);
		isMoving = true;
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
		isMoving = true;
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
		move(0.f, verticalVelocity.y * deltaTime);
		animation->setCurrentImageX(4);
		isMoving = true;
	}
}

sf::Vector2f Player::getPosition()
{
	return playerSprite.getPosition();
}
void Player::changeColor()
{
	if (hitColorTimer > 0)
	{
		playerSprite.setColor(sf::Color::Red);
	}
}
void Player::updateColor(float deltaTime)
{
	hitColorTimer -= deltaTime;
	if (hitColorTimer < 0)
	{
		playerSprite.setColor(playerColor);
	}
}
//END PLAYER POSITIONING



//PLAYER COLLISION
void Player::updateBounceCollision(sf::RenderTarget* target, std::vector<Platform*> platforms, float deltaTime)
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
		playerGlobalPosition.y = target->getSize().y - collider.size.y - collider.offset.y -floorHeight;
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
		while (collider.xCausesCollision(playerGlobalPosition, platformGlobalPosition, platformCollider, velocity.x * deltaTime))
		{
			playerGlobalPosition.x -= Utils::sgn(velocity.x);
		}
		while (collider.yCausesCollision(playerGlobalPosition, platformGlobalPosition, platformCollider, velocity.y * deltaTime))
		{
			playerGlobalPosition.y -= Utils::sgn(velocity.y);
		}
		if (groundCollider.yCausesCollision(playerGlobalPosition, platformGlobalPosition, platformCollider, velocity.y * deltaTime +1.f))
		{
			onGround = true;
		}
		if (topCollider.yCausesCollision(playerGlobalPosition, platformGlobalPosition, platformCollider, velocity.y * deltaTime + 1.f))
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
void Player::updateBulletCollision(Bullets& enemyBullets)
{
	hit = false;
	std::vector<Bullet*> deletedBullets;
	std::vector<Bullet*>& bullets = enemyBullets.getBullets();
	bullets.erase(std::remove_if(
		bullets.begin(),
		bullets.end(),
		[&deletedBullets, this](Bullet* bullet) {
			bool playerCollision = bullet->getCollider().intersects(bullet->getGlobalPosition(), getGlobalPosition(), collider);
			if (playerCollision)
			{
				hit = true;
				hitColorTimer = 0.15f;
				changeColor();
				playerHealth -= bullet->bulletDamage;
				deletedBullets.push_back(bullet);
			}
		return playerCollision;
		}),
		bullets.end()
	);
	for (auto& element : deletedBullets)
	{
		delete(element);
	}
}
//END PLAYER COLLISION


//UPDATE AND RENDER
void Player::updatePlayer(sf::RenderTarget* target, float deltaTime, std::vector<Platform*> platforms, Node* parentNode, Bullets& enemyBullets)
{	
	movePlayer(deltaTime);
	updateBounceCollision(target, platforms, deltaTime);
	updatePhysics(deltaTime);
	updateBulletCollision(enemyBullets);
	weapon->updateWeapon(target, getPosition(), facingRight, facingLeft, deltaTime, parentNode);
	healthBar.updateHealthBarAnimation(sf::Vector2f(getGlobalPosition().x, getGlobalPosition().y + 20.f), playerMaxHealth, playerHealth);
	updateColor(deltaTime);
	updatePlayerAnimation(deltaTime);
	//std::cout << playerHealth << std::endl;
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