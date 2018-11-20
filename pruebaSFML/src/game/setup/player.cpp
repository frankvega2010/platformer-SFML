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
	}

	Player::Player(int x, int y, int width, int height, sf::Color color)
	{
		_position = { x,y };
		_size = { width,height };
		_color = color;
		_alive = true;
		_move = { 0,0 };
		_speed = 0;
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
}