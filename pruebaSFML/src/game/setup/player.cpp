#include "player.h"

namespace Game_Namespace
{
	Player::Player()
	{
		_position = {0,0};
		_size = { 0,0 };
		_move = { 0,0 };
		_color = sf::Color::White;
		_alive = true;
		_speed = { 0,0 };
		_gravity = true;
	}

	Player::Player(int x, int y, int width, int height, sf::Color color)
	{
		_position = { x,y };
		_size = { width,height };
		_color = color;
		_alive = true;
		_move = { 0,0 };
		_speed = { 0,0 };
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

	sf::Vector2f Player::getSpeed()
	{
		return _speed;
	}

	void Player::setSpeed(float speedX, float speedY)
	{
		_speed = { speedX, speedY };
	}

	bool Player::getIsAlive()
	{
		return _alive;
	}

	void Player::setIsAlive(bool alive)
	{
		_alive = alive;
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