#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 640

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

#define BLOCK_SIZE 32

#define I 0
#define J 1
#define L 2
#define O 3
#define S 4
#define T 5
#define Z 6

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

const uint16_t tetrominoes[7][4] = {
    //  UP     RIGHT   DOWN    LEFT
    //  0       1       2       3
    {0x4444, 0x0F00, 0x2222, 0x00F0}, // 0 I
    {0x44C0, 0x8E00, 0x6440, 0x0E20}, // 1 J
    {0x4460, 0x0E80, 0xC440, 0x2E00}, // 2 L
    {0xCC00, 0xCC00, 0xCC00, 0xCC00}, // 3 O
    {0x06C0, 0x8C40, 0x6C00, 0x4620}, // 4 S
    {0x0E40, 0x4C40, 0x4E00, 0x4640}, // 5 T
    {0x0C60, 0x4C80, 0xC600, 0x2640}, // 6 Z
};

struct tetromino
{
    uint16_t up, right, down, left;
};

struct tetromino i = {0x4444, 0x0F00, 0x2222, 0x00F0};
struct tetromino j = {0x44C0, 0x8E00, 0x6440, 0x0E20};
struct tetromino l = {0x4460, 0x0E80, 0xC440, 0x2E00};
struct tetromino o = {0xCC00, 0xCC00, 0xCC00, 0xCC00};
struct tetromino s = {0x06C0, 0x8C40, 0x6C00, 0x4620};
struct tetromino t = {0x0E40, 0x4C40, 0x4E00, 0x4640};
struct tetromino z = {0x0C60, 0x4C80, 0xC600, 0x2640};

// Each cell in the 4x4 grid which contain the tetromino is either occupied or not
bool cellIsOccupied(const uint16_t tetrominoWithDirection, int cellIndex)
{
    int bitIndex = 15 - cellIndex;
    return (tetrominoWithDirection & (1 << bitIndex)) >> bitIndex;
}

// Tetromino's index match the color in tetures/blocks.png
// [0, 1, 2, 3, 4, 5, 6]
// [I, J, L, O, S, T, Z]
void drawBlock(const sf::Texture &blockTextures,
               const sf::Vector2f &position,
               int colorIndex,
               sf::RenderWindow *window)
{
    sf::Sprite blockSprite(blockTextures);
    blockSprite.setTextureRect(sf::IntRect(BLOCK_SIZE * colorIndex, 0, // Offset
                                           BLOCK_SIZE, BLOCK_SIZE));   // Size
    blockSprite.setPosition(position);
    window->draw(blockSprite);
}

sf::Vector2f getBlockPosition(const sf::Vector2f &tetrominoPosition,
                              int blockIndexInTetromino)
{
    sf::Vector2f blockPosition;
    blockPosition.x = tetrominoPosition.x + (blockIndexInTetromino % 4) * BLOCK_SIZE;
    blockPosition.y = tetrominoPosition.x + (blockIndexInTetromino / 4) * BLOCK_SIZE;
    return blockPosition;
}

void drawTetromino(const sf::Texture &blockTexture,
                   const sf::Vector2f &position,
                   int tetromino, int direction,
                   sf::RenderWindow *window)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int blockIndex = i * 4 + j;

            if (cellIsOccupied(tetrominoes[tetromino][direction], blockIndex))
            {
                drawBlock(blockTexture, getBlockPosition(position, blockIndex),
                          tetromino, window);
            }
        }
    }
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
        int x = 32, y = 32;
        sf::Vector2f position(x, y);

        mainWindow.clear(sf::Color::White);
        drawTetromino(blockTextures, position, J, 0, &mainWindow);
        mainWindow.display();
    }

    return 0;
}
