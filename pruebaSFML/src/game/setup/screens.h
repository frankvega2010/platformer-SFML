#ifndef SCREENS_H
#define SCREENS_H

namespace newgame
{
	class Screens
	{
	private:
		static bool _hasScreenFinished;
	public:
		Screens();
		~Screens();
		static bool getHasScreenFinished();
		static void setHasScreenFinished(bool hasScreenFinished);
		virtual void init() = 0;
		virtual void input() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
		virtual void deInit() = 0;
		virtual bool finish() = 0;
	};
}

#endif // SCREENS_H
