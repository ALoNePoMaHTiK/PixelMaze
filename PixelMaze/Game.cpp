#include "Game.h"

Game::Game(int height, int width) : maze(height, width)	//Вызов конструктора лабиринта
{
	path.push_back(maze.MazeStart);
}

bool Game::GameOver() {
	if (current == maze.MazeEnd)
		return true;
	else
		return false;
}

void Game::Move(Direction direction) {
	if (direction == Direction::Left) {
		if (current.x > 0 && (maze.maze[current.y][current.x] & maze.CELL_PATH_W)) {
			current.x--;
			if (path.size() > 1 && path[path.size() - 2] == current)
				path.pop_back();	//Если это шаг назад -> Откат
			else
				path.push_back(current);	//Если это шаг вперёд -> Добавление в массив посещённых
		}
	}
	if (direction == Direction::Right) {
		if (current.x < maze.MazeWidth - 1 && (maze.maze[current.y][current.x] & maze.CELL_PATH_E)) {
			current.x++;
			if (path.size() > 1 && path[path.size()-2] == current)
				path.pop_back();	//Если это шаг назад -> Откат
			else
				path.push_back(current);	//Если это шаг вперёд -> Добавление в массив посещённых
		}
	}
	if (direction == Direction::Up) {
		if (current.y > 0 && (maze.maze[current.y][current.x] & maze.CELL_PATH_N)) {
			current.y--;
			if (path.size() > 1 && path[path.size() - 2] == current)
				path.pop_back();	//Если это шаг назад -> Откат
			else
				path.push_back(current);	//Если это шаг вперёд -> Добавление в массив посещённых
		}
	}
	if (direction == Direction::Down) {
		if (current.y < maze.MazeHeight - 1 && (maze.maze[current.y][current.x] & maze.CELL_PATH_S)) {
			current.y++;
			if (path.size() > 1 && path[path.size() - 2] == current)
				path.pop_back();	//Если это шаг назад -> Откат
			else
				path.push_back(current);	//Если это шаг вперёд -> Добавление в массив посещённых
		}
	}
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	sf::Color C_WALL;
	sf::Color C_CELL;
	sf::Color C_VISITED;
	sf::Color C_MazeStart;
	sf::Color C_MazeEnd;
	sf::Color C_PLAYER;

	//Применение цветового стиля
	switch (getColorStyle())
	{
	case BLUE:
		C_WALL = sf::Color(10,30,105);
		C_CELL = sf::Color(190, 225, 240);
		C_VISITED = sf::Color(0, 140, 140);
		C_MazeStart = sf::Color(75, 30, 120);
		C_MazeEnd = sf::Color(100, 1, 95);
		C_PLAYER = sf::Color(0, 80, 140);
		break;
	case RED:
		C_WALL = sf::Color(150, 5, 10);
		C_CELL = sf::Color(240, 170, 115);
		C_VISITED = sf::Color(255, 120, 120);
		C_MazeStart = sf::Color(190, 50, 50);
		C_MazeEnd = sf::Color(190, 0, 50);
		C_PLAYER = sf::Color(240, 65, 60);
		break;
	case GREEN:
		C_WALL = sf::Color(0, 71, 59);
		C_CELL = sf::Color(240, 220, 145);
		C_VISITED = sf::Color(131, 194, 89);
		C_MazeStart = sf::Color(3, 146, 84);
		C_MazeEnd = sf::Color(0, 130, 141);
		C_PLAYER = sf::Color(85, 159, 46);
		break;
	case STANDART:
		C_WALL = sf::Color(0, 0, 0);
		C_CELL = sf::Color(255, 255, 255);
		C_VISITED = sf::Color(90, 110, 250);
		C_MazeStart = sf::Color(0, 0, 255);
		C_MazeEnd = sf::Color(255,0, 0);
		C_PLAYER = sf::Color(0, 255, 0);
		break;
	}
	//Создание спрайта
	sf::Texture texture_cell;
	texture_cell.loadFromFile("textures\\wall.png",sf::IntRect(0,0,CellSize, CellSize));
	sf::Sprite m_cell;
	m_cell.setTexture(texture_cell);
	m_cell.setColor(C_CELL);

	//Рисуем рамку
	sf::RectangleShape frame(sf::Vector2f(
		maze.MazeWidth*CellSize + (maze.MazeWidth-1) * WallWidth, maze.MazeHeight*CellSize + (maze.MazeHeight - 1) * WallWidth)
	);
	frame.setPosition(WallWidth, WallWidth);
	frame.setOutlineThickness(WallWidth);
	frame.setOutlineColor(C_WALL);
	frame.setFillColor(C_WALL);
	target.draw(frame);

	for (int x = 0; x < maze.MazeWidth; x++)
	{
		for (int y = 0; y < maze.MazeHeight; y++)
		{
			//Рисуем клетку
			m_cell.setPosition(x * (WallWidth + CellSize) + WallWidth, y * (WallWidth + CellSize) + WallWidth);
			
			m_cell.setColor(C_CELL);
			target.draw(m_cell);
			//Рисуем проходы
			if (maze.maze[y][x] & maze.CELL_PATH_E) {
				sf::RectangleShape passage(sf::Vector2f(WallWidth, CellSize));
				passage.setPosition((x+1)*(WallWidth +CellSize),y*CellSize + (y+1)*WallWidth);		
				passage.setFillColor(C_CELL);
				target.draw(passage);
			}
			if (maze.maze[y][x] & maze.CELL_PATH_S) {
				sf::RectangleShape passage(sf::Vector2f(CellSize, WallWidth));
				passage.setPosition(x*CellSize + (x + 1)*WallWidth, (y + 1)*(WallWidth + CellSize));
				passage.setFillColor(C_CELL);
				target.draw(passage);
			}
		}
	}

	//Прорисовка посещённых клеток
	m_cell.setColor(C_VISITED);
	for (int i = 0; i < path.size(); i++) {

		m_cell.setPosition(path[i].x * (WallWidth + CellSize) + WallWidth, path[i].y * (WallWidth + CellSize) + WallWidth);
		target.draw(m_cell);

		//Прорисовка посещённых проходов
		sf::RectangleShape passage;
		passage.setFillColor(C_VISITED);
		if (i < path.size() - 1) {
			if (path[i].y != path[i + 1].y) {		//Движение было по-вертикали
				passage.setSize(sf::Vector2f(CellSize, WallWidth));
				if (path[i].y > path[i + 1].y) {	//Движение вверх
					passage.setPosition(path[i + 1].x*CellSize + (path[i + 1].x + 1)*WallWidth, (path[i + 1].y + 1)*(WallWidth + CellSize));
				}
				else {	//Движение вниз
					passage.setPosition(path[i].x*CellSize + (path[i].x + 1)*WallWidth, (path[i].y + 1)*(WallWidth + CellSize));
				}
			}
			else {	//Движение было по-горизонтали
				passage.setSize(sf::Vector2f(WallWidth, CellSize));
				if (path[i].x > path[i + 1].x) {	//Движение влево
					passage.setPosition((path[i+1].x + 1)*(WallWidth + CellSize), path[i + 1].y*CellSize + (path[i + 1].y + 1)*WallWidth);
				}
				else {	//Движение вправо
					passage.setPosition((path[i].x + 1)*(WallWidth + CellSize), path[i].y*CellSize + (path[i].y + 1)*WallWidth);
				}
			}
			target.draw(passage);
		}
	}

	//Рисуем вход
	m_cell.setColor(C_MazeStart);
	m_cell.setPosition(maze.MazeStart.x * (WallWidth + CellSize) + WallWidth, maze.MazeStart.y * (WallWidth + CellSize) + WallWidth);
	target.draw(m_cell);

	//Рисуем выхода
	m_cell.setColor(C_MazeEnd);
	m_cell.setPosition(maze.MazeEnd.x * (WallWidth + CellSize) + WallWidth, maze.MazeEnd.y * (WallWidth + CellSize) + WallWidth);
	target.draw(m_cell);

	//Рисуем игрока
	m_cell.setColor(C_PLAYER);
	m_cell.setPosition(current.x * (WallWidth + CellSize) + WallWidth, current.y * (WallWidth + CellSize) + WallWidth);
	target.draw(m_cell);
}