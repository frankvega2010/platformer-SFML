#ifndef CHARACTER_H
#define CHARACTER_H
#include "game.h"

namespace Game_Namespace
{
	class Character
	{
	private:
		sf::Vector2i _position;
		sf::Vector2i _size;
		sf::Color _color;
		sf::Vector2f _move;
		sf::Vector2f _speed;
		bool _alive;
		bool _gravity;
		bool _isPlayer;
	public:
		Character();
		Character(int x, int y, int width, int height, sf::Color color);
		~Character();
		void setPosition(int x, int y);
		sf::Vector2i getPosition();
		void setMove(float x, float y);
		sf::Vector2f getMove();
		void setSize(int width, int height);
		sf::Vector2i getSize();
		void setColor(sf::Color color);
		sf::Color getColor();
		sf::Vector2f getSpeed();
		void setSpeed(float speedX, float speedY);
		bool getIsAlive();
		void setIsAlive(bool alive);
		bool getGravity();
		void setGravity(bool gravity);
		bool getIsPlayer();
		void setIsPlayer(bool isPlayer);
	};
}
#endif // CHARACTER_H