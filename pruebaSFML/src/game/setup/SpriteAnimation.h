#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include "gameplay.h"


class SpriteAnimation
{
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
public:
	SpriteAnimation();
	SpriteAnimation(sf::Texture* texture, sf::Vector2u imageCount,float switchTime);
	~SpriteAnimation();
	void Update(int row,float deltaTime);
	void SetAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

public:
	sf::IntRect uvRect;
};

#endif // SPRITEANIMATION_H

