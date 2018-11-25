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
	}

	Character::Character(int x, int y, int width, int height, sf::Color color)
	{
		_position = { x,y };
		_size = { width,height };
		_color = color;
		_alive = true;
		_move = { 0,0 };
		_speed = { 0,0 };
		_gravity = true;
		_isPlayer = false;
	}

	Character::~Character()
	{

	}

	void Character::setPosition(int x, int y)
	{
		_position = { x,y };
	}

	sf::Vector2i Character::getPosition()
	{
		return _position;
	}

	void Character::setMove(float x, float y)
	{
		_move = { x,y };
	}

	sf::Vector2f Character::getMove()
	{
		return _move;
	}


	void Character::setSize(int width, int height)
	{
		_size = { width,height };
	}

	sf::Vector2i Character::getSize()
	{
		return _size;
	}

	void Character::setColor(sf::Color color)
	{
		_color = color;
	}

	sf::Color Character::getColor()
	{
		return _color;
	}

	sf::Vector2f Character::getSpeed()
	{
		return _speed;
	}

	void Character::setSpeed(float speedX, float speedY)
	{
		_speed = { speedX, speedY };
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
}