#include <SFML/Graphics.hpp>
#include "Game.h"

int WinMain()
{
	// —оздаем окно размером 600 на 600 и частотой обновлени€ 60 кадров в секунду
	sf::RenderWindow window(sf::VideoMode(600, 600), "PixelMaze", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	Game game;
	game.Init();


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// ѕолучаем нажатую клавишу - выполн€ем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) game.Move(Direction::Left);
				if (event.key.code == sf::Keyboard::Right) game.Move(Direction::Right);
				if (event.key.code == sf::Keyboard::Up) game.Move(Direction::Up);
				if (event.key.code == sf::Keyboard::Down) game.Move(Direction::Down);
				if (game.Check())
					window.close();
				// Ќова€ игра
				if (event.key.code == sf::Keyboard::F2)
				{
					game.Init();
					//move_counter = 100;
				}
			}


			window.clear();
			window.draw(game);
			window.display();
		}
	}
	return 0;
}