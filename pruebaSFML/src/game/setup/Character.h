#ifndef CHARACTER_H
#define CHARACTER_H
#include "game.h"

#include "Thor/Time.hpp"

//using namespace thor;

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
		int _hp;
		int _isOnWhichGround;
		bool _alive;
		bool _gravity;
		bool _isPlayer;
		bool _currentlyTouchingPlayer;
		bool _canShoot;
		bool _flipLeft;
		bool _flipRight;
		bool _isJumping;
		bool _isOnGround;
		thor::CallbackTimer _timerJump;
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
		int getHp();
		void setHp(int hp);
		bool getIsAlive();
		void setIsAlive(bool alive);
		bool getGravity();
		void setGravity(bool gravity);
		bool getIsPlayer();
		void setIsPlayer(bool isPlayer);
		bool getCurrentlyTouchingPlayer();
		void setCurrentlyTouchingPlayer(bool currentlyTouchingPlayer);
		bool getCanShoot();
		void setCanShoot(bool canShoot);
		bool getFlipLeft();
		void setFlipLeft(bool flipLeft);
		bool getFlipRight();
		void setFlipRight(bool flipRight);
		bool getIsJumping();
		void setIsJumping(bool isJumping);
		bool getIsOnGround();
		void setIsOnGround(bool isOnGround);
		void StartTimerJump();
		void setResetTimerJump(sf::Time initialTime);
		bool isTimerJumpExpired();
		bool isTimerJumpRunning();
		int getIsOnWhichGround();
		void setIsOnWhichGround(int isOnWhichGround);
	};
}

#endif // CHARACTER_H