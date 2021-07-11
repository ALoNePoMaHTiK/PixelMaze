#pragma once
#include "Map.h"
#include "ConfigLoader.h"

enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

const int CellSize = getCellSize(); 		// Размер клетки в пикселях
const int WallWidth = getWallWidth();		// Размер стены в пикселях

class Game : public sf::Drawable, public sf::Transformable
{
private:
	Map maze;
	cell current = maze.MazeStart;		//Текущее положение
	std::vector<cell> path;			//Пройденные клетки
	sf::Font font;
public:
	Game(int height, int width);
	bool GameOver();	//Проверка победы
	void Move(Direction direction);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};