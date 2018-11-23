#include "player.h"

namespace Juego
{
	Player::Player()
	{
		_position = {0,0};
		_size = { 0,0 };
		_move = { 0,0 };
		_color = sf::Color::White;
		_alive = true;
		_speed = 0;
		_direction = 0;
		_canMoveUp = true;
		_canMoveDown = true;
		_canMoveLeft = true;
		_canMoveRight = true;
		_gravity = true;
	}

	Player::Player(int x, int y, int width, int height, sf::Color color)
	{
		_position = { x,y };
		_size = { width,height };
		_color = color;
		_alive = true;
		_move = { 0,0 };
		_speed = 0;
		_direction = 0;
		_canMoveUp = true;
		_canMoveDown = true;
		_canMoveLeft = true;
		_canMoveRight = true;
		_gravity = true;
	}

	Player::~Player()
	{

	}

	void Player::setPosition(int x, int y)
	{
		_position = { x,y };
	}

	sf::Vector2i Player::getPosition()
	{
		return _position;
	}

	void Player::setMove(float x, float y)
	{
		_move = { x,y };
	}

	sf::Vector2f Player::getMove()
	{
		return _move;
	}


	void Player::setSize(int width, int height)
	{
		_size = { width,height };
	}

	sf::Vector2i Player::getSize()
	{
		return _size;
	}

	void Player::setColor(sf::Color color)
	{
		_color = color;
	}

	sf::Color Player::getColor()
	{
		return _color;
	}

	int Player::getDirection()
	{
		return _direction;
	}

	void Player::setDirection(int direction)
	{
		_direction = direction;
	}

	float Player::getSpeed()
	{
		return _speed;
	}

	void Player::setSpeed(float speed)
	{
		_speed = speed;
	}

	bool Player::getIsAlive()
	{
		return _alive;
	}

	void Player::setIsAlive(bool alive)
	{
		_alive = alive;
	}

	bool Player::getCanMoveUp()
	{
		return _canMoveUp;
	}

	void Player::setCanMoveUp(bool canMoveUp)
	{
		_canMoveUp = canMoveUp;
	}

	bool Player::getCanMoveDown()
	{
		return _canMoveDown;
	}

	void Player::setCanMoveDown(bool canMoveDown)
	{
		_canMoveDown = canMoveDown;
	}

	bool Player::getCanMoveLeft()
	{
		return _canMoveLeft;
	}

	void Player::setCanMoveLeft(bool canMoveLeft)
	{
		_canMoveLeft = canMoveLeft;
	}

	bool Player::getCanMoveRight()
	{
		return _canMoveRight;
	}

	void Player::setCanMoveRight(bool canMoveRight)
	{
		_canMoveRight = canMoveRight;
	}

	bool Player::getGravity()
	{
		return _gravity;
	}

	void Player::setGravity(bool gravity)
	{
		_gravity = gravity;
	}
}