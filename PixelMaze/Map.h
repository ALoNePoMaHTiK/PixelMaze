#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <stack>

//структура, хранящая координаты клетки
struct cell
{
	int x;
	int y;
	cell(int X, int Y) { x = X; y = Y; };
	cell() { x = 0; y = 0; };
	bool operator == (const cell& right) const{
		if ((x == right.x) && (y == right.y))
			return true;
		return false;
	}
};

class Map
{	
public:
	enum
	{
		CELL_PATH_N = 0x01,
		CELL_PATH_E = 0x02,
		CELL_PATH_S = 0x04,
		CELL_PATH_W = 0x08,
		CELL_VISITED = 0x10,
	};

	int MazeHeight;
	int MazeWidth;
	cell MazeEnd;
	cell MazeStart;

	std::vector<std::vector<int>> maze;	
	Map(int height, int width);
	void Generate();	//Генерация лабиринта
};