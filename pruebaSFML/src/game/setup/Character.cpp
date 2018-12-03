#include "Character.h"

namespace Game_Namespace
{
	Character::Character()
	{
		_position = { 0,0 };
		_size = { 0,0 };
		_move = { 0,0 };
		_color = sf::Color::White;
		_alive = true;
		_speed = { 0,0 };
		_gravity = true;
		_isPlayer = false;
		_hp = 0;
		_currentlyTouchingPlayer = false;
		_canShoot = false;
		_flipLeft = false;
		_flipRight = false;
		_isJumping = false;
		_isOnGround = false;
		_isOnWhichGround = -1;
		_isDead = false;
		_moveLeft = true;
		_moveRight = true;
		_isOnWhichLeftWall = -1;
		_isOnWhichRightWall = -1;
	}

	Character::Character(float x, float y, float width, float height, sf::Color color)
	{
		_position = { x,y };
		_size = { width,height };
		_color = color;
		_alive = true;
		_move = { 0,0 };
		_speed = { 0,0 };
		_gravity = true;
		_isPlayer = false;
		_hp = 0;
		_currentlyTouchingPlayer = false;
		_canShoot = false;
		_flipLeft = false;
		_flipRight = false;
		_isJumping = false;
		_isOnGround = false;
		_isOnWhichGround = -1;
		_isDead = false;
		_moveLeft = true;
		_moveRight = true;
		_isOnWhichLeftWall = -1;
		_isOnWhichRightWall = -1;
	}

	Character::~Character()
	{

	}

	void Character::setPosition(float x, float y)
	{
		_rectangle.setPosition(sf::Vector2f(x, y));
	}

	sf::Vector2f Character::getPosition()
	{
		return _rectangle.getPosition();
	}

	void Character::setPlayerDetectionPosition(float x, float y)
	{
		_rectanglePlayerDetection.setPosition(sf::Vector2f(x, y));
	}

	sf::Vector2f Character::getPlayerDetectionPosition()
	{
		return _rectanglePlayerDetection.getPosition();
	}

	void Character::setTexture(sf::Texture& texture)
	{
		_rectangle.setTexture(&texture);
	}

	void Character::setTextureRect(sf::IntRect uvRect)
	{
		_rectangle.setTextureRect(uvRect);
	}

	void Character::setMove(float x, float y)
	{
		_rectangle.move(x, y);
	}

	sf::Vector2f Character::getMove()
	{
		return _move;
	}

	void Character::setSize(float width, float height)
	{
		_rectangle.setSize(sf::Vector2f(width, height));
	}

	sf::Vector2f Character::getSize()
	{
		return _rectangle.getSize();
	}

	void Character::setPlayerDetectionSize(float width, float height)
	{
		_rectanglePlayerDetection.setSize(sf::Vector2f(width, height));
	}

	sf::Vector2f Character::getPlayerDetectionSize()
	{
		return _rectanglePlayerDetection.getSize();
	}

	void Character::setColor(sf::Color color)
	{
		_rectangle.setFillColor(color);
	}

	sf::Color Character::getColor()
	{
		return _rectangle.getFillColor();
	}

	void Character::setPlayerDetectionColor(sf::Color color)
	{
		_rectanglePlayerDetection.setFillColor(color);
	}

	sf::Color Character::getPlayerDetectionColor()
	{
		return _rectanglePlayerDetection.getFillColor();
	}


	sf::Vector2f Character::getSpeed()
	{
		return _speed;
	}

	void Character::setSpeed(float speedX, float speedY)
	{
		_speed = { speedX, speedY };
	}

	int Character::getHp()
	{
		return _hp;
	}

	void Character::setHp(int hp)
	{
		_hp = hp;
	}

	bool Character::getIsAlive()
	{
		return _alive;
	}

	void Character::setIsAlive(bool alive)
	{
		_alive = alive;
	}

	bool Character::getGravity()
	{
		return _gravity;
	}

	void Character::setGravity(bool gravity)
	{
		_gravity = gravity;
	}

	bool Character::getIsPlayer()
	{
		return _isPlayer;
	}

	void Character::setIsPlayer(bool isPlayer)
	{
		_isPlayer = isPlayer;
	}

	void Character::setCurrentlyTouchingPlayer(bool currentlyTouchingPlayer)
	{
		_currentlyTouchingPlayer = currentlyTouchingPlayer;
	}

	bool Character::getCurrentlyTouchingPlayer()
	{
		return _currentlyTouchingPlayer;
	}

	bool Character::getCanShoot()
	{
		return _canShoot;
	}

	void Character::setCanShoot(bool canShoot)
	{
		_canShoot = canShoot;
	}

	bool Character::getFlipLeft()
	{
		return _flipLeft;
	}

	void Character::setFlipLeft(bool flipLeft)
	{
		_flipLeft = flipLeft;
	}

	bool Character::getFlipRight()
	{
		return _flipRight;
	}

	void Character::setFlipRight(bool flipRight)
	{
		_flipRight = flipRight;
	}

	bool Character::getIsJumping()
	{
		return _isJumping;
	}

	void Character::setIsJumping(bool isJumping)
	{
		_isJumping = isJumping;
	}

	bool Character::getIsOnGround()
	{
		return _isOnGround;
	}

	void Character::setIsOnGround(bool isOnGround)
	{
		_isOnGround = isOnGround;
	}

	void Character::StartTimerJump()
	{
		_timerJump.start();
	}

	void Character::setResetTimerJump(sf::Time initialTime)
	{
		_timerJump.reset(initialTime);
	}

	bool Character::isTimerJumpExpired()
	{
		return _timerJump.isExpired();
	}

	bool Character::isTimerJumpRunning()
	{
		return _timerJump.isRunning();
	}

	int Character::getIsOnWhichGround()
	{
		return _isOnWhichGround;
	}

	void Character::setIsOnWhichGround(int isOnWhichGround)
	{
		_isOnWhichGround = isOnWhichGround;
	}

	sf::RectangleShape Character::getRectangle()
	{
		return _rectangle;
	}

	sf::RectangleShape Character::getPlayerDetection()
	{
		return _rectanglePlayerDetection;
	}

	void Character::setOrigin(int x, int y)
	{
		_rectangle.setOrigin(x, y);
	}

	void Character::scale(int x, int y)
	{
		_rectangle.scale(x, y);
	}

	bool Character::getIsDead()
	{
		return _isDead;
	}
	void Character::setIsDead(bool isDead)
	{
		_isDead = isDead;
	}

	bool Character::getMoveRight()
	{
		return _moveRight;
	}

	void Character::setMoveRight(bool moveRight)
	{
		_moveRight = moveRight;
	}

	bool Character::getMoveLeft()
	{
		return _moveLeft;
	}

	void Character::setMoveLeft(bool moveLeft)
	{
		_moveLeft = moveLeft;
	}

	int Character::getIsOnWhichLeftWall()
	{
		return _isOnWhichLeftWall;
	}

	void Character::setIsOnWhichLeftWall(int isOnWhichLeftWall)
	{
		_isOnWhichLeftWall = isOnWhichLeftWall;
	}

	int Character::getIsOnWhichRightWall()
	{
		return _isOnWhichRightWall;
	}

	void Character::setIsOnWhichRightWall(int isOnWhichRightWall)
	{
		_isOnWhichRightWall = isOnWhichRightWall;
	}

}