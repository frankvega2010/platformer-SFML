#ifndef CREDITS_H
#define CREDITS_H

#include "setup/screens.h"

namespace Game_Namespace
{
	namespace Credits_Section
	{
		class CreditsScreen :public Screens
		{
		private:
		public:
			CreditsScreen();
			~CreditsScreen();
			void init();
			void input();
			void update();
			void draw();
			void deInit();
			bool finish();
		};
	}
}
#endif // CREDITS_H