#include<SFML/Graphics.hpp>
#include<iostream>
// <> , " "
//using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML 시작");
	window.setFramerateLimit(60);
	// 도형.
	sf::RectangleShape player(sf::Vector2f(100.f, 100.f));
	player.setFillColor(sf::Color::Cyan);
	player.setPosition(sf::Vector2f(300.f, 300.f));

	sf::CircleShape cir(50.f,8);
	cir.setFillColor(sf::Color::Red);
	cir.setPosition(sf::Vector2f(200.f, 200.f));
	while (window.isOpen())
	{
		sf::Event eve;
		while (window.pollEvent(eve))
		{
			switch (eve.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				if (eve.text.unicode < 128)
					std::cout << static_cast<char>(eve.text.unicode);
				break;
			default:
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			player.move(-0.1f, 0.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			player.move(0.1f, 0.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			player.move(0.0f, -0.1f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			player.move(0.0f, 0.1f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousepos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousepos.x, (float)mousepos.y);
		}
		player.move(0.5f, -0.1f);
		player.rotate(2.f); 
		cir.move(-0.1f, 0.3f);
//		cir.rotate(45.f);
		// rendering을 하려면.. 렌더링 흐름: clear -> draw -> display
		window.clear();
		window.draw(player);
		window.draw(cir);
		window.display();
	}
}