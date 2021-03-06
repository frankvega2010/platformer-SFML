#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include "gameplay.h"

namespace newgame
{
	enum playerAnimationSequences
	{
		playerWalkBackward,
		playerWalkForward,
		playerJump,
		playerspriteCount
	};

	enum pistolAnimationSequences
	{
		pistolShoot,
		pistolspriteCount
	};

	class SpriteAnimation
	{
	private:
		sf::Vector2u imageCount;
		sf::Vector2u currentImage;
		float totalTime;
		float switchTime;
	public:
		SpriteAnimation();
		SpriteAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
		~SpriteAnimation();
		void Update(int row, float deltaTime);
		bool UpdateOnce(int row, float deltaTime);
		void UpdateReverse(int row, float deltaTime);
		void UpdateY(int row, float deltaTime);
		void SetAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
		void SetAnimationY(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
		void SetSingleFrame(sf::Vector2u imageCount);
	public:
		sf::IntRect uvRect;
	};

}

#endif // SPRITEANIMATION_H