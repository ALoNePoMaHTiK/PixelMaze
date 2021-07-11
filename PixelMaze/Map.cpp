#include "Map.h"

Map::Map(int height, int width) {
	MazeHeight = height;
	MazeWidth = width;

	//Инициализируем нулями
	maze.resize(MazeHeight);
	for (int i = 0; i < MazeHeight; i++)
		maze[i].resize(MazeWidth,0);

	srand(time(0));
	Generate();
}

void Map::Generate() {
	std::stack<cell> way;

	//Генерируем стартовые координаты
	MazeStart.x = rand() % MazeWidth;
	MazeStart.y = rand() % MazeHeight;
	way.push(MazeStart);
	maze[MazeStart.y][MazeStart.x] = CELL_VISITED;
	int visitedCells = 1;

	int MaxLength = 0;	//Самый длинный путь (по нему строится точка выхода)

	while(visitedCells < MazeWidth * MazeHeight)
	{
		// Набор соседей
		std::vector<int> neighbours;

		// North neighbour
		if (way.top().y > 0 && (maze[way.top().y - 1][way.top().x] & CELL_VISITED) == 0)
			neighbours.push_back(0);
		// East neighbour
		if (way.top().x < MazeWidth - 1 && (maze[way.top().y][way.top().x + 1] & CELL_VISITED) == 0)
			neighbours.push_back(1);
		// South neighbour
		if (way.top().y < MazeHeight - 1 && (maze[way.top().y + 1][way.top().x] & CELL_VISITED) == 0)
			neighbours.push_back(2);
		// West neighbour
		if (way.top().x > 0 && (maze[way.top().y][way.top().x - 1] & CELL_VISITED) == 0)
			neighbours.push_back(3);

		// Есть ли доступные соседи ?
		if (!neighbours.empty())
		{
			// Случайный выбор одного из соседей
			int next_cell_dir = neighbours[rand() % neighbours.size()];

			// Создание путей между клетками
			switch (next_cell_dir)
			{
			case 0: // North
				maze[way.top().y - 1][way.top().x] |= CELL_VISITED | CELL_PATH_S;
				maze[way.top().y][way.top().x] |= CELL_PATH_N;
				way.push(cell((way.top().x), (way.top().y - 1)));
				break;

			case 1: // East
				maze[way.top().y][way.top().x + 1] |= CELL_VISITED | CELL_PATH_W;
				maze[way.top().y][way.top().x] |= CELL_PATH_E;
				way.push(cell((way.top().x + 1), (way.top().y)));
				break;

			case 2: // South
				maze[way.top().y + 1][way.top().x] |= CELL_VISITED | CELL_PATH_N;
				maze[way.top().y][way.top().x] |= CELL_PATH_S;
				way.push(cell((way.top().x), (way.top().y + 1)));
				break;

			case 3: // West
				maze[way.top().y][way.top().x - 1] |= CELL_VISITED | CELL_PATH_E;
				maze[way.top().y][way.top().x] |= CELL_PATH_W;
				way.push(cell((way.top().x - 1), (way.top().y)));
				break;

			}
			visitedCells++;
		}
		else
		{
			if (way.size() > MaxLength) {
				MaxLength = way.size();
				MazeEnd = way.top();
			}
			// Нет доступных соседей -> Откат
			way.pop();
		}
	}
}