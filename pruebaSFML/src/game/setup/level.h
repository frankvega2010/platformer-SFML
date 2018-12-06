#ifndef LEVEL_H
#define LEVEL_H

#include "gameplay.h"

#include "pugixml.hpp"
#include "pugiconfig.hpp"

namespace newgame
{
	const int maxRectanglesPerLevel = 60;

	class level
	{
	private:
		pugi::xml_document _doc;
		pugi::xml_parse_result _result;
		pugi::xml_node _object;
		pugi::xml_node_iterator _someObjects;
		int _RectanglesInLevel;
		sf::RectangleShape _rectangles[maxRectanglesPerLevel];
		sf::RectangleShape _rectangleTest;
		char _resultPath;
		int _enemyKillObjetive;
	public:
		level();
		~level();
		void setResultPath(const char* resultPath);
		void setRectangles(int RectanglesInLevel);
		sf::RectangleShape getRectangles(int i);
		sf::RectangleShape getRectangleTest();
		int getRectanglesInLevel();
		void setEnemyKillObjetive(int enemyKillObjetive);
		int getEnemyKillObjetive();
	};
}


#endif // LEVEL_H