#include "screens.h"

namespace newgame
{
	bool Screens::_hasScreenFinished=0;

	Screens::Screens()
	{
		_hasScreenFinished = false;
	}

	Screens::~Screens()
	{
	}

	bool Screens::getHasScreenFinished()
	{
		return _hasScreenFinished;
	}

	void Screens::setHasScreenFinished(bool hasScreenFinished)
	{
		_hasScreenFinished = hasScreenFinished;
	}
}