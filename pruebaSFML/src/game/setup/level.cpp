#include "level.h"

namespace Game_Namespace
{
	level::level()
	{
	}


	level::~level()
	{
	}

	void level::setResultPath(const char* resultPath)
	{
		_result = _doc.load_file(resultPath);
	}

	void level::setRectangles(int RectanglesInLevel)
	{
		_object = _doc.child("map").child("objectgroup");;
		_someObjects = _object.begin();
		_RectanglesInLevel = RectanglesInLevel;
		_enemyKillObjetive = 0;
		
		int i = 0;
		for (pugi::xml_node_iterator it = _object.begin(); it != _object.end(); ++it)
		{
			_rectangles[i].setPosition(sf::Vector2f(static_cast<float>(it->attribute("x").as_int()),
				static_cast<float>(it->attribute("y").as_int())));

			_rectangles[i].setSize(sf::Vector2f(static_cast<float>(it->attribute("width").as_int()),
				static_cast<float>(it->attribute("height").as_int())));

			_rectangles[i].setFillColor(sf::Color::Transparent);
			i++;
		}
		i = 0;

	}

	sf::RectangleShape level::getRectangles(int i)
	{
		return _rectangles[i];
	}

	sf::RectangleShape level::getRectangleTest()
	{
		return _rectangleTest;
	}

	int level::getRectanglesInLevel()
	{
		return _RectanglesInLevel;
	}

	void level::setEnemyKillObjetive(int enemyKillObjetive)
	{
		_enemyKillObjetive = enemyKillObjetive;
	}

	int level::getEnemyKillObjetive()
	{
		return _enemyKillObjetive;
	}
}