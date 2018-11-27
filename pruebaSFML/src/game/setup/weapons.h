#ifndef WEAPONS_H
#define WEAPONS_H

#include "gameplay.h"
#include "SpriteAnimation.h"

namespace Game_Namespace
{
	class Weapons
	{
	private:
		sf::Texture _texture;
		SpriteAnimation _animation;
		int _ammo;
		sf::Time _fireRate;
		thor::CallbackTimer _fireRateTimer;
	public:
		Weapons();
		~Weapons();
		virtual void pickup()=0;
		virtual void shoot()=0;
		virtual void draw()=0;
	};
}

#endif // WEAPONS_H