#include "enemy.h"

namespace Game
{
	Enemy::Enemy()
	{
		_position = {0,0};
		_size = { 0,0 };
		_color = sf::Color::White;
		_move = { 0,0 };
		_speed = { 0,0 };
		_alive = true;
		_gravity = true;
	}

	Enemy::Enemy(int x, int y, int width, int height, sf::Color color)
	{
		_position = { x,y };
		_size = { width,height };
		_color = color;
		_move = { 0,0 };
		_speed = { 0,0 };
		_alive = true;
		_gravity = true;
	}

	Enemy::~Enemy()
	{

	}

	void Enemy::setPosition(int x, int y)
	{
		_position = { x,y };
	}

	sf::Vector2i Enemy::getPosition()
	{
		return _position;
	}

	void Enemy::setMove(float x, float y)
	{
		_move = { x,y };
	}

	sf::Vector2f Enemy::getMove()
	{
		return _move;
	}

	void Enemy::setSize(int width, int height)
	{
		_size = { width,height };
	}

	sf::Vector2i Enemy::getSize()
	{
		return _size;
	}

	void Enemy::setColor(sf::Color color)
	{
		_color = color;
	}

	sf::Color Enemy::getColor()
	{
		return _color;
	}

	sf::Vector2f Enemy::getSpeed()
	{
		return _speed;
	}
	void Enemy::setSpeed(float speedX, float speedY)
	{
		_speed = { speedX, speedY };
	}

	bool Enemy::getIsAlive()
	{
		return _alive;
	}
	void Enemy::setIsAlive(bool alive)
	{
		_alive = alive;
	}

	bool Enemy::getGravity()
	{
		return _gravity;
	}

	void Enemy::setGravity(bool gravity)
	{
		_gravity = gravity;
	}
}