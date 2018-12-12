#ifndef WEAPON_H
#define WEAPON_H

#include "gameplay.h"
#include "SpriteAnimation.h"

namespace newgame
{
	enum weaponList
	{
		pistol,
		shotgun,
		smg,
		maxWeapons
	};


	class weapon
	{
	private:
		//sf::Texture _texture;
		//SpriteAnimation _animation;
		//sf::Time _fireRate;
		int _ammo;
		int _damage;
		thor::CallbackTimer _fireRateTimer;
		sf::SoundBuffer _shootSoundBuffer;
		sf::SoundBuffer _drawSoundBuffer;
		sf::Sound _shootSound;
		sf::Sound _drawSound;
	public:
		weapon();
		~weapon();
		void setAmmo(int ammo);
		int getAmmo();
		void setDamage(int damage);
		int getDamage();
		void setSoundBufferLocation(const char* path);
		void setSoundBufferLocationDraw(const char* path);
		void setSoundVolume(int volume);
		void StartFireRateTimer();
		void StopFireRateTimer();
		void setFireRateTimer(sf::Time initialTime);
		bool isFireRateTimerExpired();
		bool isFireRateTimerRunning();
		void playSound();
		void playDrawSound();
	};
}

#endif // WEAPON_H