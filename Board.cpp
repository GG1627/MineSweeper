//
// Created by gael8 on 4/12/2024.
//
#include "Board.h"
#include "Cell.h"
#include "Ctimer.h"
#include "LeaderBoard.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <random>
using namespace std;

Board::Board(int numRows, int numCols, int numMines, int numFlagsPlaced) : leadZ() {
    this->numRows = numRows;
    this->numCols = numCols;
    this->numMines = numMines;
    this->numFlagsPlaced = numFlagsPlaced;


    // In the constructor or initialization method
    if (!bottomLayer.loadFromFile("files/images/tile_revealed.png")) {
        cerr << "could not load file" << endl;
    }
    if (!topLayer.loadFromFile("files/images/tile_hidden.png")) {
        cerr << "could not load file" << endl;
    }
    if (!MineTexture.loadFromFile("files/images/mine.png")) {
        cerr << "could not load file" << endl;
    }
    if (!flagTexture.loadFromFile("files/images/flag.png")) {
        cerr << "could not load file" << endl;
    }

    if (!Num1.loadFromFile("files/images/number_1.png")) {
        cerr << "could not load file" << endl;
    }
    if (!Num2.loadFromFile("files/images/number_2.png")) {
        cerr << "could not load file" << endl;
    }
    if (!Num3.loadFromFile("files/images/number_3.png")) {
        cerr << "could not load file" << endl;
    }
    if (!Num4.loadFromFile("files/images/number_4.png")) {
        cerr << "could not load file" << endl;
    }
    if (!Num5.loadFromFile("files/images/number_5.png")) {
        cerr << "could not load file" << endl;
    }
    if (!Num6.loadFromFile("files/images/number_6.png")) {
        cerr << "could not load file" << endl;
    }
    if (!Num7.loadFromFile("files/images/number_7.png")) {
        cerr << "could not load file" << endl;
    }
    if (!Num8.loadFromFile("files/images/number_8.png")) {
        cerr << "could not load file" << endl;
    }

    if (!HappyFace.loadFromFile("files/images/face_happy.png")) {
        cerr << "could not load file" << endl;
    }
    if (!GameLostFace.loadFromFile("files/images/face_lose.png")) {
        cerr << "could not load file" << endl;
    }
    if (!GameWonFace.loadFromFile("files/images/face_win.png")) {
        cerr << "could not load file" << endl;
    }

    if (!DeBuggzy.loadFromFile("files/images/debug.png")) {
        cerr << "could not load file" << endl;
    }
    if (!PauseButton.loadFromFile("files/images/pause.png")) {
        cerr << "could not load file" << endl;
    }
    if (!PlayButton.loadFromFile("files/images/play.png")) {
        cerr << "could not load file" << endl;
    }
    if (!LeaderBoardButton.loadFromFile("files/images/leaderboard.png")) {
        cerr << "could not load file" << endl;
    }

    // Set initial game state
    numFlagsPlaced = 0;
    numCellsRevealed = 0;

    initializeLayer0();
    initializeBombs(numRows, numCols, numMines);
    initializeNums(numRows, numCols, numMines);
    initializeTopLayer();


}

int Board::getRandomRow(int numRows) {
    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate a random row index between 0 and numRows - 1
    std::uniform_int_distribution<int> dist(0, numRows - 1);
    return dist(gen);
}

int Board::getRandomCol(int numCols) {
    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate a random row index between 0 and numRows - 1
    std::uniform_int_distribution<int> dist(0, numCols - 1);
    return dist(gen);
}

void Board::initializeLayer0() {

    grid.resize(numRows, std::vector<Cell>(numCols));
    // setting up the grid inital grid
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            grid[i][j].isBottomLayer = true;
            grid[i][j].isMine = false;
            grid[i][j].isFlagged = false;
            grid[i][j].isNumbered = false;
            grid[i][j].isTopLayer = false;

            // You can add more initialization here as needed
        }
    }
}

void Board::initializeBombs(int numRows, int numCols, int numMines) {

    // Count the number of mines already placed on the board
    int currentMines = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (grid[i][j].isMine) {
                currentMines++;
            }
        }
    }

    while (currentMines < numMines) {
        int randomRow = getRandomRow(numRows);
        int randomCol = getRandomCol(numCols);
        if (!grid[randomRow][randomCol].isMine) {
            grid[randomRow][randomCol].isMine = true;
            grid[randomRow][randomCol].isTopLayer = true;
            grid[randomRow][randomCol].isBottomLayer = true;
            currentMines++;
        }
    }
}

void Board::initializeNums(int numRows, int numCols, int numMines) {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (!grid[i][j].isMine) {
                int proximityMineTotal = 0;
                for(int r = -1; r <= 1; r++) {
                    for (int t = -1; t <= 1; t++) {
                        if (!(r == 0 && t == 0)) { // Exclude the current cell itself
                            int x = i + r;
                            int y = j + t;

                            if (x >= 0 && x < numRows && y >= 0 && y < numCols) {
                                if (grid[x][y].isMine) {
                                    // Increment proximityMines if the neighboring cell is a mine
                                    proximityMineTotal++;
                                }
                                grid[i][j].proximityMines = proximityMineTotal;
                            }
                        }
                    }
                }
                if(proximityMineTotal > 0) {
                    grid[i][j].isNumbered = true;
                    grid[i][j].isTopLayer = false;
                    grid[i][j].isBottomLayer = true;

                }
            }
        }
    }
}

void Board::initializeTopLayer() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            grid[i][j].isBottomLayer = false;
            grid[i][j].isTopLayer = true;

        }
    }
}

void Board::initializeSecretLayer() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            grid[i][j].isSecretLayer = false;
        }
    }
}
void Board::drawSecretLayer(sf::RenderWindow& window){
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if(grid[i][j].isSecretLayer) {
                // Calculate the position of the cell on the window
                float cellY = j * 32;
                float cellX = i * 32;
                sf::Sprite botLayerZ(bottomLayer);  //
                botLayerZ.setPosition(cellX, cellY);
                window.draw(botLayerZ);
            }
        }
    }
}

void Board::drawBackground(){
    rect.setSize(sf::Vector2f(numRows * 32, numCols * 32 + 100));
    rect.setFillColor(sf::Color(255, 190, 255));
}

void Board::initializeRestartButton(sf::Sprite& buttonSprite) {
    buttonSprite.setTexture(HappyFace);
    buttonSprite.setPosition(((numRows/2) * 32) - 32, (numCols+0.5) * 32);
    restartButtonBounds = buttonSprite.getGlobalBounds();
}

void Board::initializeDebugButton(sf::Sprite& buttonSprite) {
    buttonSprite.setTexture(DeBuggzy);
    buttonSprite.setPosition((numRows * 32) - 304, (numCols+0.5) * 32);
    debugButtonBounds = buttonSprite.getGlobalBounds();
}

void Board::initializePPButton(sf::Sprite &buttonSprite) {
    buttonSprite.setTexture(PauseButton);
    buttonSprite.setPosition((numRows * 32) - 240, (numCols+0.5) * 32);
    pausePlayButtonBounds = buttonSprite.getGlobalBounds();
}

void Board::initializeLeaderBoard(sf::Sprite &buttonSprite) {
    buttonSprite.setTexture(LeaderBoardButton);
    buttonSprite.setPosition((numRows * 32) - 176, (numCols+0.5) * 32);
    leaderboardButtonBounds = buttonSprite.getGlobalBounds();
}

void Board::CheckIfWon(sf::RenderWindow& window) {
    bool allRegTilesRevealed = true;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (!grid[i][j].isMine && grid[i][j].isNumbered && grid[i][j].isTopLayer) {
                allRegTilesRevealed = false;
                break;
            }
        }
        if (!allRegTilesRevealed) {
            break;
        }
    }

    if (allRegTilesRevealed && !gamePaused) {
        // Game won
        cout << "YAY U WON" << endl;
        sf::Sprite GameWonFacez(GameWonFace);  //
        GameWonFacez.setPosition(((numRows / 2) * 32) - 32, (numCols + 0.5) * 32);
        window.draw(GameWonFacez);
        GameWon = true;
        CanClick = false;
    }
}

void Board::resetGame(sf::RenderWindow& window){
    CanClick = true;
    GameLost = false;
    GameWon = false;
    gamePaused = false;

    // Clear the grid and initialize it again
    numFlagsPlaced = numMines;
    initializeLayer0();
    initializeBombs(numRows, numCols, numMines);
    initializeNums(numRows, numCols, numMines);
    initializeTopLayer();
    initializeSecretLayer();

    // Redraw the game board
    render(window); // Assuming window is the SFML render window
}

void Board::hideBackWhenLeaderboardCLicked(sf::RenderWindow& window){
    if(LeaderBoardClicked){
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                // Calculate the position of the cell on the window
                float cellY = j * 32;
                float cellX = i * 32;
                sf::Sprite botLayerZ(bottomLayer);  //
                botLayerZ.setPosition(cellX, cellY);
                window.draw(botLayerZ);
                }
            }
    }
}

void Board::drawPausedLayers(sf::RenderWindow& window) {
    sf::Sprite Play(PlayButton);
    Play.setPosition((numRows * 32) - 240, (numCols + 0.5) * 32);
    window.draw(Play);

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            float cellY = j * 32;
            float cellX = i * 32;
            sf::Sprite botLayerZ(bottomLayer);
            botLayerZ.setPosition(cellX, cellY);
            window.draw(botLayerZ);
        }
    }
}


void Board::render(sf::RenderWindow& window) {
    //cout << numFlagsPlaced << endl;
    drawBackground();
    window.draw(rect);

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            // Calculate the position of the cell on the window
            float cellY = j * 32;
            float cellX = i * 32;
            sf::Sprite botLayer(bottomLayer);  //
            botLayer.setPosition(cellX, cellY);
            window.draw(botLayer);

            // Draw the cell based on its state
                if (grid[i][j].isMine){
                    sf::Sprite MineSprite(MineTexture);
                    MineSprite.setPosition(cellX, cellY);
                    window.draw(MineSprite);
                }
                else if (grid[i][j].isNumbered){
                    if(grid[i][j].proximityMines == 1){
                        sf::Sprite Number1Tiles(Num1);
                        Number1Tiles.setPosition(cellX, cellY);
                        window.draw(Number1Tiles);
                    }
                    else if(grid[i][j].proximityMines == 2){
                        sf::Sprite Number2Tiles(Num2);
                        Number2Tiles.setPosition(cellX, cellY);
                        window.draw(Number2Tiles);
                    }
                    else if(grid[i][j].proximityMines == 3){
                        sf::Sprite Number3Tiles(Num3);
                        Number3Tiles.setPosition(cellX, cellY);
                        window.draw(Number3Tiles);
                    }
                    else if(grid[i][j].proximityMines == 4){
                        sf::Sprite Number4Tiles(Num4);
                        Number4Tiles.setPosition(cellX, cellY);
                        window.draw(Number4Tiles);
                    }
                    else if(grid[i][j].proximityMines == 5){
                        sf::Sprite Number5Tiles(Num5);
                        Number5Tiles.setPosition(cellX, cellY);
                        window.draw(Number5Tiles);
                    }
                    else if(grid[i][j].proximityMines == 6){
                        sf::Sprite Number6Tiles(Num6);
                        Number6Tiles.setPosition(cellX, cellY);
                        window.draw(Number6Tiles);
                    }
                    else if(grid[i][j].proximityMines == 7){
                        sf::Sprite Number7Tiles(Num7);
                        Number7Tiles.setPosition(cellX, cellY);
                        window.draw(Number7Tiles);
                    }
                    else if(grid[i][j].proximityMines == 8){
                        sf::Sprite Number8Tiles(Num1);
                        Number8Tiles.setPosition(cellX, cellY);
                        window.draw(Number8Tiles);
                    }
                }
            }
    }
    // Draw the top board tile for each cell
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if(grid[i][j].isTopLayer) {
                float cellY = j * 32;
                float cellX = i * 32;
                sf::Sprite topLayerZ(topLayer);
                topLayerZ.setPosition(cellX, cellY);
                window.draw(topLayerZ);
                grid[i][j].isTopLayer = true;
            }
        }
    }
    // Draw flags on the top layer
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            float cellY = j * 32;
            float cellX = i * 32;
            if (grid[i][j].isFlagged && grid[i][j].isTopLayer) {
                sf::Sprite flagTile(flagTexture);
                flagTile.setPosition(cellX, cellY);
                window.draw(flagTile);
                cout << "Flag placed at (" << i << ", " << j << ")" << endl;
            }
        }
    }

    sf::Sprite RestartButton(HappyFace);  //
    RestartButton.setPosition(((numRows/2) * 32) - 32, (numCols+0.5) * 32);
    window.draw(RestartButton);

    if(GameLost) {
        CanClick = false;
        sf::Sprite GameLostFacez(GameLostFace);  //
        GameLostFacez.setPosition(((numRows / 2) * 32) - 32, (numCols + 0.5) * 32);
        window.draw(GameLostFacez);
        cout << "you lost loser" << endl;
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (grid[i][j].isMine) {
                    grid[i][j].isTopLayer = false;
                }
            }
        }
    }

    sf::Sprite DebugButton(DeBuggzy);  //
    DebugButton.setPosition((numRows * 32) - 304, (numCols+0.5) * 32);
    window.draw(DebugButton);

    sf::Sprite Leader(LeaderBoardButton);  //
    Leader.setPosition((numRows * 32) - 176, (numCols+0.5) * 32);
    window.draw(Leader);

    if(gamePaused) {
        //cout << "NOPEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << endl;
//        CanClick = false;
        sf::Sprite Play(PlayButton);  //
        Play.setPosition((numRows * 32) - 240, (numCols + 0.5) * 32);
        window.draw(Play);
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (!grid[i][j].isSecretLayer) {
                    grid[i][j].isSecretLayer = true;
                }
            }
        }

    }
    if(!gamePaused) {
//        CanClick = true;
        //cout << "WORKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKkkkkkkkkkkkkkkkkkkkkk" << endl;
        sf::Sprite Pause(PauseButton);  //
        Pause.setPosition((numRows * 32) - 240, (numCols + 0.5) * 32);
        window.draw(Pause);
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (grid[i][j].isSecretLayer) {
                    grid[i][j].isSecretLayer = false;
                }
            }
        }
    }

    drawSecretLayer(window);


    int firstDigit = numFlagsPlaced / 100;
    int secondDigit = numFlagsPlaced % 100 / 10;
    int thirdDigit = numFlagsPlaced % 10;
    int maybeNegative = numFlagsPlaced;

    if(firstDigit == 0){
        timer.loadDigit0(window, 33, 32 * (numCols + 0.5) + 16);
    }
    else if(firstDigit == 1 && numFlagsPlaced > 0){
        timer.loadDigit1(window, 33, 32 * (numCols + 0.5) + 16);
    }
    else if(firstDigit == 2 && numFlagsPlaced > 0){
        timer.loadDigit2(window, 33, 32 * (numCols + 0.5) + 16);
    }
    else if(firstDigit == 3 && numFlagsPlaced > 0){
        timer.loadDigit3(window, 33, 32 * (numCols + 0.5) + 16);
    }
    else if(firstDigit == 4 && numFlagsPlaced > 0){
        timer.loadDigit4(window, 33, 32 * (numCols + 0.5) + 16);
    }
    else if(firstDigit == 5 && numFlagsPlaced > 0){
        timer.loadDigit5(window, 33, 32 * (numCols + 0.5) + 16);
    }
    else if(firstDigit == 6 && numFlagsPlaced > 0){
        timer.loadDigit6(window, 33, 32 * (numCols + 0.5) + 16);
    }
    else if(firstDigit == 7 && numFlagsPlaced > 0){
        timer.loadDigit7(window, 33, 32 * (numCols + 0.5) + 16);
    }
    else if(firstDigit == 8 && numFlagsPlaced > 0){
        timer.loadDigit8(window, 33, 32 * (numCols + 0.5) + 16);
    }
    else if(firstDigit == 9 && numFlagsPlaced > 0){
        timer.loadDigit9(window, 33, 32 * (numCols + 0.5) + 16);
    }

    if(secondDigit == 0){
        timer.loadDigit0(window, 54, 32 * (numCols + 0.5) + 16);
    }
    else if(secondDigit == 1 && numFlagsPlaced > 0){
        timer.loadDigit1(window, 54, 32 * (numCols + 0.5) + 16);
    }
    else if(secondDigit == 2 && numFlagsPlaced > 0){
        timer.loadDigit2(window, 54, 32 * (numCols + 0.5) + 16);
    }
    else if(secondDigit == 3 && numFlagsPlaced > 0){
        timer.loadDigit3(window, 54, 32 * (numCols + 0.5) + 16);
    }
    else if(secondDigit == 4 && numFlagsPlaced > 0){
        timer.loadDigit4(window, 54, 32 * (numCols + 0.5) + 16);
    }
    else if(secondDigit == 5 && numFlagsPlaced > 0){
        timer.loadDigit5(window, 54, 32 * (numCols + 0.5) + 16);
    }
    else if(secondDigit == 6 && numFlagsPlaced > 0){
        timer.loadDigit6(window, 54, 32 * (numCols + 0.5) + 16);
    }
    else if(secondDigit == 7 && numFlagsPlaced > 0){
        timer.loadDigit7(window, 54, 32 * (numCols + 0.5) + 16);
    }
    else if(secondDigit == 8 && numFlagsPlaced > 0){
        timer.loadDigit8(window, 54, 32 * (numCols + 0.5) + 16);
    }
    else if(secondDigit == 9 && numFlagsPlaced > 0){
        timer.loadDigit9(window, 54, 32 * (numCols + 0.5) + 16);
    }

    if(thirdDigit == 0){
        timer.loadDigit0(window, 75, 32 * (numCols + 0.5) + 16);
    }
    else if(thirdDigit == 1 && numFlagsPlaced > 0){
        timer.loadDigit1(window, 75, 32 * (numCols + 0.5) + 16);
    }
    else if(thirdDigit == 2 && numFlagsPlaced > 0){
        timer.loadDigit2(window, 75, 32 * (numCols + 0.5) + 16);
    }
    else if(thirdDigit == 3 && numFlagsPlaced > 0){
        timer.loadDigit3(window, 75, 32 * (numCols + 0.5) + 16);
    }
    else if(thirdDigit == 4 && numFlagsPlaced > 0){
        timer.loadDigit4(window, 75, 32 * (numCols + 0.5) + 16);
    }
    else if(thirdDigit == 5 && numFlagsPlaced > 0){
        timer.loadDigit5(window, 75, 32 * (numCols + 0.5) + 16);
    }
    else if(thirdDigit == 6 && numFlagsPlaced > 0){
        timer.loadDigit6(window, 75, 32 * (numCols + 0.5) + 16);
    }
    else if(thirdDigit == 7 && numFlagsPlaced > 0){
        timer.loadDigit7(window, 75, 32 * (numCols + 0.5) + 16);
    }
    else if(thirdDigit == 8 && numFlagsPlaced > 0){
        timer.loadDigit8(window, 75, 32 * (numCols + 0.5) + 16);
    }
    else if(thirdDigit == 9 && numFlagsPlaced > 0){
        timer.loadDigit9(window, 75, 32 * (numCols + 0.5) + 16);
    }

    if(maybeNegative < 0){
        timer.loadDigitSlash(window, 12, 32 * (numCols + 0.5) + 16);
        cout << " number is negative" << endl;
        cout << thirdDigit << endl;
        if(thirdDigit == -1){
            timer.loadDigit1(window, 75, 32 * (numCols + 0.5) + 16);
        }
        else if(thirdDigit == -2){
            timer.loadDigit2(window, 75, 32 * (numCols + 0.5) + 16);
        }
        else if(thirdDigit == -3){
            timer.loadDigit3(window, 75, 32 * (numCols + 0.5) + 16);
        }
        else if(thirdDigit == -4){
            timer.loadDigit4(window, 75, 32 * (numCols + 0.5) + 16);
        }
        else if(thirdDigit == -5){
            timer.loadDigit5(window, 75, 32 * (numCols + 0.5) + 16);
        }
        else if(thirdDigit == -6){
            timer.loadDigit6(window, 75, 32 * (numCols + 0.5) + 16);
        }
        else if(thirdDigit == -7){
            timer.loadDigit7(window, 75, 32 * (numCols + 0.5) + 16);
        }
        else if(thirdDigit == -8){
            timer.loadDigit8(window, 75, 32 * (numCols + 0.5) + 16);
        }
        else if(thirdDigit == -9){
            timer.loadDigit9(window, 75, 32 * (numCols + 0.5) + 16);
        }

        if(secondDigit == 0){
            timer.loadDigit0(window, 54, 32 * (numCols + 0.5) + 16);
        }
        else if(secondDigit == -1){
            timer.loadDigit1(window, 54, 32 * (numCols + 0.5) + 16);
        }
        else if(secondDigit == -2){
            timer.loadDigit2(window, 54, 32 * (numCols + 0.5) + 16);
        }
        else if(secondDigit == -3){
            timer.loadDigit3(window, 54, 32 * (numCols + 0.5) + 16);
        }
        else if(secondDigit == -4){
            timer.loadDigit4(window, 54, 32 * (numCols + 0.5) + 16);
        }
        else if(secondDigit == -5){
            timer.loadDigit5(window, 54, 32 * (numCols + 0.5) + 16);
        }
        else if(secondDigit == -6){
            timer.loadDigit6(window, 54, 32 * (numCols + 0.5) + 16);
        }
        else if(secondDigit == -7){
            timer.loadDigit7(window, 54, 32 * (numCols + 0.5) + 16);
        }
        else if(secondDigit == -8){
            timer.loadDigit8(window, 54, 32 * (numCols + 0.5) + 16);
        }
        else if(secondDigit == -9){
            timer.loadDigit9(window, 54, 32 * (numCols + 0.5) + 16);
        }

        if(firstDigit == 0){
            timer.loadDigit0(window, 33, 32 * (numCols + 0.5) + 16);
        }
        else if(firstDigit == -1){
            timer.loadDigit1(window, 33, 32 * (numCols + 0.5) + 16);
        }
        else if(firstDigit == -2){
            timer.loadDigit2(window, 33, 32 * (numCols + 0.5) + 16);
        }
        else if(firstDigit == -3){
            timer.loadDigit3(window, 33, 32 * (numCols + 0.5) + 16);
        }
        else if(firstDigit == -4){
            timer.loadDigit4(window, 33, 32 * (numCols + 0.5) + 16);
        }
        else if(firstDigit == -5){
            timer.loadDigit5(window, 33, 32 * (numCols + 0.5) + 16);
        }
        else if(firstDigit == -6){
            timer.loadDigit6(window, 33, 32 * (numCols + 0.5) + 16);
        }
        else if(firstDigit == -7){
            timer.loadDigit7(window, 33, 32 * (numCols + 0.5) + 16);
        }
        else if(firstDigit == -8){
            timer.loadDigit8(window, 33, 32 * (numCols + 0.5) + 16);
        }
        else if(firstDigit == -9){
            timer.loadDigit9(window, 33, 32 * (numCols + 0.5) + 16);
        }

    }

    CheckIfWon(window);

    if(GameWon){
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if(grid[i][j].isMine){
                    grid[i][j].isFlagged = true;
                }
            }
        }
    }

}



void Board::toggleFlag(int col, int row){
    cout << "Toggling flag at (" << col << ", " << row << ")" << endl;
    if(grid[col][row].isFlagged && grid[col][row].isTopLayer){
        grid[col][row].isFlagged = false;
        cout << "testing1" << endl;
    }
    else if (!grid[col][row].isFlagged && grid[col][row].isTopLayer){
        grid[col][row].isFlagged = true;
        cout << "testing2" << endl;

    }
}

void Board::revealRecursive(int row, int col) {
    grid[row][col].isTopLayer = false;

    for(int r = -1; r <= 1; r++) {
        for (int t = -1; t <= 1; t++) {
            int newRow = row + r;
            int newCol = col + t;

            if(newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
                if (grid[newRow][newCol].isTopLayer && !grid[newRow][newCol].isMine && !grid[newRow][newCol].isFlagged) {
                    if (grid[newRow][newCol].proximityMines == 0) {
                        revealRecursive(newRow, newCol); // Empty cell, reveal recursively
                    }
                    else {
                        // Cell has a number, reveal it
                        grid[newRow][newCol].isTopLayer = false;
                    }
                }
            }
        }
    }
}


void Board::revealDebug(int row, int col){
    // Draw the top board tile for each cell
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if(grid[i][j].isMine && !(grid[i][j].isTopLayer)) { //
                grid[i][j].isTopLayer = true;
                cout << "worked2" << endl;
            }
            else if(grid[i][j].isMine) { //
                grid[i][j].isTopLayer = false;
                cout << "worked1" << endl;
            }
        }
    }
}



// Implementation of handleMouseClick method
void Board::handleMouseClick(sf::Vector2i mousePosition, sf::RenderWindow& window) {
    // Convert mouse position to grid indices
    int row = mousePosition.y / 32; // Assuming cell size is 32x32
    int col = mousePosition.x / 32;

    // Check if the clicked cell is within the board bounds
    if (row >= 0 && row < numCols && col >= 0 && col < numRows) {
        // Right click to toggle flag
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !GameWon && CanClick) {
            cout << "right click worked" << endl;
            toggleFlag(col, row);
            if(grid[col][row].isFlagged) {
                numFlagsPlaced--;
            }
            else if(!grid[col][row].isFlagged){
                numFlagsPlaced++;
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && CanClick && !gamePaused){
            cout << "left click worked" << endl;
            if(!grid[col][row].isFlagged) {
                grid[col][row].isTopLayer = false;
            }
            if(grid[col][row].proximityMines == 0 && !grid[col][row].isFlagged){
                revealRecursive(col, row);
            }
            if(grid[col][row].isMine == true && !grid[col][row].isFlagged){
                // set Game Lost to true to change face
                GameLost = true;
                CanClick = false;
            }
        }
    }
    else if (restartButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition))){
//        gamePaused = false;
        resetGame(window);
        cout << "this should have changed so if it didn't imma lose my mind" << endl;
    }
    else if (debugButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition)) && !GameWon){
//        CanClick = !CanClick;
        cout << "Debug Button Works" << endl;
        revealDebug(col, row);

    }
    else if (leaderboardButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition))){
        cout << "LeaderBoard Button Works" << endl;
        cout << "LeaderBoard Set True" << endl;
        if(!LeaderBoardClicked){
            LeaderBoardClicked = true;
            cout << "leaderboard set to trueeeeeeeeeeeeeeeee" << endl;
        }
        else if(LeaderBoardClicked) {
            LeaderBoardClicked = false;
            cout << "leaderboard set to falseeeeeeeeeeeeeeeeeeeeeee" << endl;
        }
    }
}

