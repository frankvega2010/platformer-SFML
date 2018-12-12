#include "weapon.h"

namespace newgame
{
	weapon::weapon()
	{
		_ammo = 0;
	}

	weapon::~weapon()
	{
	}

	void weapon::setAmmo(int ammo)
	{
		_ammo = ammo;
	}

	int weapon::getAmmo()
	{
		return _ammo;
	}

	void weapon::setDamage(int damage)
	{
		_damage = damage;
	}

	int weapon::getDamage()
	{
		return _damage;
	}

	void weapon::setSoundBufferLocation(const char* path)
	{
		_shootSoundBuffer.loadFromFile(path);
		_shootSound.setBuffer(_shootSoundBuffer);
	}

	void weapon::setSoundBufferLocationDraw(const char* path)
	{
		_drawSoundBuffer.loadFromFile(path);
		_drawSound.setBuffer(_drawSoundBuffer);
	}

	void weapon::setSoundVolume(int volume)
	{
		_shootSound.setVolume(static_cast<float>(volume));
		_drawSound.setVolume(static_cast<float>(volume));
	}

	void weapon::StartFireRateTimer()
	{
		_fireRateTimer.start();
	}

	void weapon::StopFireRateTimer()
	{
		_fireRateTimer.stop();
	}

	void weapon::setFireRateTimer(sf::Time initialTime)
	{
		_fireRateTimer.reset(initialTime);
	}

	bool weapon::isFireRateTimerExpired()
	{
		return _fireRateTimer.isExpired();
	}

	bool weapon::isFireRateTimerRunning()
	{
		return _fireRateTimer.isRunning();
	}

	void weapon::playSound()
	{
		_shootSound.play();
	}

	void weapon::playDrawSound()
	{
		_drawSound.play();
	}
}


