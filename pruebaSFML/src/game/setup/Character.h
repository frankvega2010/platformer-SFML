#ifndef CHARACTER_H
#define CHARACTER_H
#include "game.h"

#include "Thor/Time.hpp"
#include "spriteanimation.h"

namespace newgame
{
	class Character
	{
	private:
		sf::Vector2f _position;
		sf::Vector2f _size;
		sf::Color _color;
		sf::Vector2f _move;
		sf::Vector2f _speed;
		sf::RectangleShape _rectangle;
		sf::RectangleShape _rectanglePlayerDetection;
		int _hp;
		int _isOnWhichGround;
		int _isOnWhichLeftWall;
		int _isOnWhichRightWall;
		int _isOnWhichCeiling;
		int _isOnWhichCharacterLeftSide;
		int _isOnWhichCharacterRightSide;
		bool _alive;
		bool _gravity;
		bool _isPlayer;
		bool _currentlyTouchingPlayer;
		bool _canShoot;
		bool _flipLeft;
		bool _flipRight;
		bool _isJumping;
		bool _isOnGround;
		bool _isDead;
		bool _moveLeft;
		bool _moveRight;
		bool _moveUp;
		thor::CallbackTimer _timerJump;
	public:
		Character();
		Character(float x, float y, float width, float height, sf::Color color);
		~Character();
		void setPosition(float x, float y);
		sf::Vector2f getPosition();
		void setTexture(sf::Texture& texture);
		void setTextureRect(sf::IntRect uvRect);
		void setPlayerDetectionPosition(float x, float y);
		sf::Vector2f getPlayerDetectionPosition();
		void setMove(float x, float y);
		sf::Vector2f getMove();
		void setSize(float width, float height);
		sf::Vector2f getSize();
		void setPlayerDetectionSize(float width, float height);
		sf::Vector2f getPlayerDetectionSize();
		void setColor(sf::Color color);
		sf::Color getColor();
		void setPlayerDetectionColor(sf::Color color);
		sf::Color getPlayerDetectionColor();
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
		void StopTimerJump();
		void setResetTimerJump(sf::Time initialTime);
		bool isTimerJumpExpired();
		bool isTimerJumpRunning();
		int getIsOnWhichGround();
		void setIsOnWhichGround(int isOnWhichGround);
		int getIsOnWhichCeiling();
		void setIsOnWhichCeiling(int isOnWhichCeiling);
		void setOrigin(int x, int y);
		void scale(int x, int y);
		bool getIsDead();
		void setIsDead(bool isDead);
		bool getMoveRight();
		void setMoveRight(bool moveRight);
		bool getMoveLeft();
		void setMoveLeft(bool moveLeft);
		bool getMoveUp();
		void setMoveUp(bool moveUp);
		int getIsOnWhichLeftWall();
		void setIsOnWhichLeftWall(int isOnWhichLeftWall);
		int getIsOnWhichRightWall();
		void setIsOnWhichRightWall(int isOnWhichRightWall);
		int getIsOnWhichCharacterLeftSide();
		void setIsOnWhichCharacterLeftSide(int isOnWhichCharacterLeftSide);
		int getIsOnWhichCharacterRightSide();
		void setIsOnWhichCharacterRightSide(int isOnWhichCharacterRightSide);
		sf::RectangleShape getRectangle();
		sf::RectangleShape getPlayerDetection();
	};
}

#endif // CHARACTER_H