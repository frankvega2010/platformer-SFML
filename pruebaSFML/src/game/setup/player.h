#ifndef PLAYER_H
#define PLAYER_H
#include "game.h"

namespace Juego
{
	enum playerControls
	{
		Up,
		Down,
		Left,
		Right,
		Jump,
		controlsCount
	};

	class Player
	{
	private:
		sf::Vector2i _position;
		sf::Vector2i _size;
		sf::Color _color;
		sf::Vector2f _move;
		int _direction;
		float _speed;
		bool _alive;
		bool _canMoveUp;
		bool _canMoveDown;
		bool _canMoveLeft;
		bool _canMoveRight;
		bool _gravity;
	public:
		Player();
		Player(int x, int y, int width, int height, sf::Color color);
		~Player();
		void setPosition(int x, int y);
		sf::Vector2i getPosition();
		void setMove(float x, float y);
		sf::Vector2f getMove ();
		void setSize(int width, int height);
		sf::Vector2i getSize();
		void setColor(sf::Color color);
		sf::Color getColor();
		int getDirection();
		void setDirection(int direction);
		float getSpeed();
		void setSpeed(float speed);
		bool getIsAlive();
		void setIsAlive(bool alive);
		bool getCanMoveUp();
		void setCanMoveUp(bool canMoveUp);
		bool getCanMoveDown();
		void setCanMoveDown(bool canMoveDown);
		bool getCanMoveLeft();
		void setCanMoveLeft(bool canMoveLeft);
		bool getCanMoveRight();
		void setCanMoveRight(bool canMoveRight);
		bool getGravity();
		void setGravity(bool gravity);
	};
}
#endif // PLAYER_H
