#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 640
#define BLOCK_SIZE 32
#define GRID_WIDTH 10
#define GRID_HEIGHT 20

// Each tetromino is in a 4x4 grid
// The 4x4 grid can be represent as a 16 bit integer
// For example, the I tetromino has the following positions:
//
//     UP           RIGHT         DOWN          LEFT
//
// 0  1  0  0    0  0  0  0    0  0  1  0    0  0  0  0
// 0  1  0  0    1  1  1  1    0  0  1  0    0  0  0  0
// 0  1  0  0    0  0  0  0    0  0  1  0    1  1  1  1
// 0  1  0  0    0  0  0  0    0  0  1  0    0  0  0  0
//
// UP     0100010001000100  0x4444
// RIGHT  0000111100000000  0x0F00
// DOWN   0010001000100010  0x2222
// LEFT   0000000011110000  0x00F0
//
// Tetrominos has different centre of rotation
// So each one needs to be hard coded

uint16_t blocks[7][4] = { //  UP     RIGHT   DOWN    LEFT
                          //  0       1       2       3
							{0x4444, 0x0F00, 0x2222, 0x00F0}, // I
							{0x44C0, 0x8E00, 0x6440, 0x0E20}, // J
							{0x4460, 0x0E80, 0xC440, 0x2E00}, // L
							{0xCC00, 0xCC00, 0xCC00, 0xCC00}, // O
							{0x06C0, 0x8C40, 0x6C00, 0x4620}, // S
							{0x0E40, 0x4C40, 0x4E00, 0x4640}, // T
							{0x0C60, 0x4C80, 0xC600, 0x2640}, // Z
						};

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
								"Tetris",
								sf::Style::Close | sf::Style::Titlebar);
	
	sf::Texture blocksTexture;
	blocksTexture.loadFromFile("textures/blocks.png");

	sf::Sprite blocksSprite(blocksTexture);
	blocksSprite.setTextureRect(sf::IntRect(0, 0, BLOCK_SIZE, BLOCK_SIZE));

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
