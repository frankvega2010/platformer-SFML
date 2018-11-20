#ifndef PLAYER_H
#define PLAYER_H
#include "game.h"

namespace Juego
{
	class Player
	{
	private:
		sf::Vector2i _position;
		sf::Vector2i _size;
		sf::Color _color;
		sf::Vector2f _move;
		float _speed;
		bool _alive;
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
		float getSpeed();
		void setSpeed(float speed);
		bool getIsAlive();
		void setIsAlive(bool alive);
	};
}
#endif // PLAYER_H
