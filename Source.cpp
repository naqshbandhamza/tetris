#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "button.h"
#include <Windows.h>
using namespace std;

int main()
{

		sf::RenderWindow win(sf::VideoMode(1200, 700), "My window");
		sf::Texture texture;
		texture.loadFromFile("bg2.png");
		sf::Sprite sprite;
		sprite.setTexture(texture);

		sf::Font* font1;
		font1 = new sf::Font();
		font1->loadFromFile("WithsandDemoRegular.ttf");
		sf::Font font2;
		font2.loadFromFile("WithsandDemoRegular.ttf");
		button loadnewgame(450, 200, 400, 70, font1, font2, "New Game", sf::Color(51, 0, 102), sf::Color(224, 224, 224), sf::Color::Transparent);

		sf::Mouse mos;

		bool gameflag = false;

		while (win.isOpen())
		{
			sf::Event event;
			while (win.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					win.close();
				if (loadnewgame.isPressed())
				{
					if (!gameflag)
					{
						gameflag = true;
						cout << "new game loaded" << endl;
					}
				}
			}

			if (gameflag)
			{
				game* ptr;
				ptr = new game(win);
				bool flag = true;
				bool component_flag = false; int count = 0;
				while (flag)
				{
					while (win.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
						{
							flag = false;
							win.close();
						}
					}
					if (component_flag)
					{
						component_flag = false;
						count = ptr->conmplete_piece_cycle(win, sprite);
						ptr->check_and_burst_if(win, sprite);
					}
					win.clear();
					win.draw(sprite);
					ptr->display_grid(win);
					win.display();
					if (count == 0)
					{
						count++;
						component_flag = true;
						Sleep(500);
					}
					else if (count == -1)
					{
						flag = false;
						cout << "game lost" << endl;
						gameflag = false;
						delete ptr;
					}
				}

			}

			win.clear();
			win.draw(sprite);
			loadnewgame.render(&win);
			sf::Vector2i mpos = mos.getPosition();
			loadnewgame.update(sf::Vector2f(mpos.x, mpos.y), win);
			win.display();
		}
		delete font1;
	
}