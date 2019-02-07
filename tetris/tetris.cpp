#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(320, 640),
								"Tetris",
								sf::Style::Close | sf::Style::Titlebar);
	
	sf::Texture blocksTexture;
	blocksTexture.loadFromFile("textures/blocks.png");

	sf::Sprite blocksSprite(blocksTexture);
	blocksSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	while (mainWindow.isOpen())
	{
		sf::Event windowEvent;

		while (mainWindow.pollEvent(windowEvent))
		{
			if (windowEvent.type == windowEvent.Closed)
			{
				mainWindow.close();
			}
		}

		mainWindow.draw(blocksSprite);
		mainWindow.display();
	}


	return 0;
}
