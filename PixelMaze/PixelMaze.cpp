#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	//Ширина и длина окна	(Значения из файла конфигурации)
	int WindowWidth = getWallWidth() * (getMazeWidth() + 1) + getCellSize() * getMazeWidth();	
	int WindowHeight = getWallWidth() * (getMazeHeight() + 1) + getCellSize() * getMazeHeight();

	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "PixelMaze", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	
	//Иконка
	sf::Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Game game(getMazeHeight(),getMazeWidth());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) game.Move(Direction::Left);
				if (event.key.code == sf::Keyboard::Right) game.Move(Direction::Right);
				if (event.key.code == sf::Keyboard::Up) game.Move(Direction::Up);
				if (event.key.code == sf::Keyboard::Down) game.Move(Direction::Down);
			}

			if (game.GameOver()) {
				//Обработка победы
				window.clear();
				sf::Texture gameOvet_texture;
				gameOvet_texture.loadFromFile("textures\\GameOver.png");
				sf::Sprite gameOver;
				gameOver.setTexture(gameOvet_texture);
				for (int i = 0; i < WindowHeight / 64; i++) {
					for (int j = 0; j < WindowWidth / 64; j++) {
						gameOver.setPosition(i * 64, j * 64);
						window.draw(gameOver);
					}
				}
				window.display();
				sf::sleep(sf::seconds(3));
				window.close();
			}
			else {
				window.clear();
				window.draw(game);
				window.display();
			}
		}
	}
	return 0;
}