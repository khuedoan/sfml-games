#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 640

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

#define BLOCK_SIZE 32

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// Each tetromino is in a 4x4 grid
// The 4x4 grid can be represent as a 16 bit integer
// For example, the I tetromino has the following directions:
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

uint16_t tetrominoes[7][4] = {
    //  UP     RIGHT   DOWN    LEFT
    //  0       1       2       3
    {0x4444, 0x0F00, 0x2222, 0x00F0}, // I
    {0x44C0, 0x8E00, 0x6440, 0x0E20}, // J
    {0x4460, 0x0E80, 0xC440, 0x2E00}, // L
    {0xCC00, 0xCC00, 0xCC00, 0xCC00}, // O
    {0x06C0, 0x8C40, 0x6C00, 0x4620}, // S
    {0x0E40, 0x4C40, 0x4E00, 0x4640}, // T
    {0x0C60, 0x4C80, 0xC600, 0x2640}, // Z
};

// Tetromino's index match the color in tetures/blocks.png
// [0, 1, 2, 3, 4, 5, 6]
// [I, J, L, O, S, T, Z]
void drawBlock(sf::RenderWindow &window,
               sf::Vector2 &position,
               int colorIndex,
               sf::Texture blockTextures)
{
    sf::Sprite blockSprite;
    blockSprite.setTexture(blockTextures);
    blockSprite.setTextureRect(sf::IntRect(BLOCK_SIZE * colorIndex, 0, // Position
                                           BLOCK_SIZE, BLOCK_SIZE));   // Size
    blockSprite.setPosition(32, 32);
    window.draw(blockSprite);
}

void drawTetromino(int tetromino, int direction, coordinate position)
{
}

int main()
{
    sf::RenderWindow mainWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                "Tetris",
                                sf::Style::Close | sf::Style::Titlebar);

    sf::Texture blockTextures;
    blockTextures.loadFromFile("textures/blocks.png");

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
        coordinate a = {2, 1};

        mainWindow.clear(sf::Color::White);
        drawBlock(mainWindow, a, 6, blockTextures);
        mainWindow.display();
    }

    return 0;
}
