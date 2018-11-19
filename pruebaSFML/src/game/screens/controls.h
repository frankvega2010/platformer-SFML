#ifndef CONTROLS_H
#define CONTROLS_H
#include "Setup/Game.h"
#include "Screens\gameplay.h"
#include "setup/screens.h"
namespace Juego
{
	namespace Controls_Section
	{
		class ControlsScreen :public Screens
		{
		private:
		public:
			ControlsScreen();
			~ControlsScreen();
			void init();
			void input();
			void update();
			void draw();
			void deInit();
			bool finish();

		};
	}
}
#endif // CONTROLS_H
