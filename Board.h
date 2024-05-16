// Board.h
#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include "Cell.h"
#include "Ctimer.h"
#include "LeaderBoard.h"
#include <SFML/Graphics.hpp>
#include <vector>

struct Board {
    // Constructor
    Board(int numRows, int numCols, int numMines, int numFlagsPlaced);

    void revealRecursive(int row, int col);
    void revealDebug(int row, int col);


    // Functions to initialize and manage the game board
    void drawBackground();
    void initializeLayer0(); // Initialize the grid with cells
    void initializeTopLayer();
    void initializeBombs(int numRows, int numCols, int numMines);
    void initializeNums(int numRows, int numCols, int numMines);
    void initializeSecretLayer();
    void drawSecretLayer(sf::RenderWindow& window);


    void hideBackWhenLeaderboardCLicked(sf::RenderWindow& window);

    // Functions for Buttons components
    void initializeRestartButton();
    void initializeMineCounter();
    void initializeDebugButton(); // loop and set all cells isTopLayer to false;
    void initializePlayPause();
    void initializeLeaderBoard();
    void initializeTimer();
    void drawGUI();


    // Functions to handle user actions
    void handleMouseClick(sf::Vector2i mousePosition, sf::RenderWindow& window);
    void toggleFlag(int row, int col); // Toggles the flag status of a cell
    int getRandomRow(int numRows);
    int getRandomCol(int numRows);

    // Function to render the game board
    void render(sf::RenderWindow& window);

    // Variables to store board dimensions and grid of cells
    int numRows;
    int numCols;
    int numMines;
    int numFlagsPlaced;
    int numCellsRevealed;
    std::vector<std::vector<Cell>> grid;

    sf::RectangleShape rect;
    sf::Texture bottomLayer;
    sf::Texture topLayer;
    sf::Texture MineTexture;
    sf::Texture flagTexture;
    sf::Texture Num1;
    sf::Texture Num2;
    sf::Texture Num3;
    sf::Texture Num4;
    sf::Texture Num5;
    sf::Texture Num6;
    sf::Texture Num7;
    sf::Texture Num8;

    // Buttonz stuff

    void initializeRestartButton(sf::Sprite& buttonSprite);
//    void initializeMineCounter();
    void initializeDebugButton(sf::Sprite& buttonSprite);
    void initializePPButton(sf::Sprite& buttonSprite);
    void initializeLeaderBoard(sf::Sprite& buttonSprite);
//    void initializeTimer();
//    void drawGUI(sf::RenderWindow& window);

    void CheckIfWon(sf::RenderWindow& window);
    void resetGame(sf::RenderWindow& window);
    void drawPausedLayers(sf::RenderWindow& window);


    bool isRestartButton;
    bool isMineCounter;
    bool isDebugButton;
    bool isPlayPause;
    bool isLeaderBoard;
    bool isTimer;

    bool CanClickFaceWhilePaused = false;
    bool isClicked;
    bool GameLost = false;
    bool GameWon = false;
    bool LeaderBoardClicked = false;
    bool GameFinished = false;
    bool gamePaused = false;
    bool CanClick = true;

    sf::Texture HappyFace;
    sf::Texture GameLostFace;
    sf::Texture GameWonFace;
    sf::Texture DeBuggzy;
    sf::Texture PauseButton;
    sf::Texture PlayButton;
    sf::Texture LeaderBoardButton;
    sf::RectangleShape rectangleZ;

    sf::FloatRect restartButtonBounds;
    sf::FloatRect debugButtonBounds;
    sf::FloatRect pausePlayButtonBounds;
    sf::FloatRect leaderboardButtonBounds;

    Ctimer timer;
    LeaderBoard leadZ;
    void toggleTimerPause(Ctimer& timer);



};

#endif // MINESWEEPER_BOARD_H

