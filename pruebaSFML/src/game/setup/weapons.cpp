#include "weapons.h"

namespace Game_Namespace
{
	Weapons::Weapons()
	{
		_texture;
		_animation;
		_ammo = 0;
		_fireRate = sf::seconds(0.1f);
		_fireRateTimer;
	}


	Weapons::~Weapons()
	{
	}
}