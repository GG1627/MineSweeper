#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "WelcomeWindow.h"
#include "Ctimer.h"
#include "Board.h"
#include "LeaderBoard.h"
#include <chrono>
#include <iomanip>

using namespace std::chrono;
using namespace std;



int main() {
    std::vector<int> fileData;

    std::ifstream file("files/config.cfg");
    std::string line;
    if (!file.is_open()) {
        std::cerr << "file not opened" << std::endl;
    }
    while (getline(file, line, '\n')) {
        fileData.push_back(stoi(line));
    }

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(fileData[0] * 32, fileData[1] * 32 + 100), "SFML window", sf::Style::Close);

    // Create instances of game components
    WelcomeWindow welcomeWindow;
    Board gameBoard(fileData[0], fileData[1], fileData[2], fileData[2]);  //fileData[2]
    LeaderBoard leaderBoard;
    Ctimer ctimZ;

    sf::Sprite RestartButton;
    sf::Sprite DebugButton;
    sf::Sprite PauseButton;
    sf::Sprite LeaderboardButton;

    gameBoard.initializeRestartButton(RestartButton);
    gameBoard.initializeDebugButton(DebugButton);
    gameBoard.initializePPButton(PauseButton);
    gameBoard.initializeLeaderBoard(LeaderboardButton);

    bool inWelcomeScreen = true;
    bool inGameScreen = true;
    bool NeedtoRenderAgain = false;

    auto pause_time = chrono::steady_clock::now();
    auto elapsed_paused_time = chrono::duration_cast<chrono::seconds>(
            chrono::steady_clock::now() - pause_time).count();

    bool paused = false;
    bool leaderBoardIsOpen = false;
    bool leaderboardOpenedWhilePaused = false;

    bool GameOfficiallyWON = false;
    bool gameWonAndLeaderboardDisplayed = false;
    bool updateLeaderboard = false; // Flag to indicate if the leaderboard needs to be updated


    // Game loop
    while (window.isOpen()) {
        gameBoard.CanClick = false;
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                gameBoard.CanClick = true;
                window.close();
                inGameScreen = false;
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter &&
                       !welcomeWindow.getUserInput().empty()) {
                gameBoard.CanClick = true;
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                gameBoard.handleMouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), window);
            } else if (inWelcomeScreen) {
                std::cout << "good" << std::endl;
                welcomeWindow.handleEvent(event);
            }
        }
        // Clear the window
        window.clear();
        // Render appropriate screen
        welcomeWindow.render(window);
        window.display();
    }


    sf::RenderWindow gamewindow(sf::VideoMode(fileData[0] * 32, fileData[1] * 32 + 100), "Game Window",sf::Style::Close);
    auto start_time = chrono::steady_clock::now();


    while (gamewindow.isOpen()) {
        sf::Event event;

        while (gamewindow.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                gamewindow.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
                gameBoard.handleMouseClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), window);


                if (gameBoard.pausePlayButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition)) &&
                    !gameBoard.GameWon && gameBoard.CanClick) {
                    cout << "click was successfully registerddddddddddddddd" << endl;
                    gameBoard.CanClickFaceWhilePaused = true;
                    paused = !paused;
                    if (paused) {
                        gameBoard.gamePaused = true;
                        std::cout << "paused" << std::endl;                                 // && !gameBoard.GameWon
                        pause_time = chrono::steady_clock::now();
                    }
                    else {
                        gameBoard.gamePaused = false;
                        std::cout << "unpaused" << std::endl;
                        auto unPausedTime = chrono::steady_clock::now();
                        elapsed_paused_time += chrono::duration_cast<chrono::seconds>(
                                unPausedTime - pause_time).count();
                    }
                }
                else if (gameBoard.restartButtonBounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
//                    std::cout << "restartbuttonclicked" << std::endl;
//                    gameBoard.gamePaused = !gameBoard.gamePaused;
                    //if (!gameBoard.GameWon) {
                        paused = false;
                        start_time = chrono::steady_clock::now();

                    //}

                }
            }
//             gameBoard.drawSecretLayer(gamewindow);     // i was playing around with this idk if i need to add it
        }
        gameBoard.render(gamewindow);

        if(gameBoard.LeaderBoardClicked){
            gameBoard.hideBackWhenLeaderboardCLicked(gamewindow);
            cout << "yesssssssssssssssssssssssssssss" << endl;
            gamewindow.display();
        }

        if(gameBoard.GameWon){
            cout << "TRUEEEEEEEEEEEEEEEEE" << endl;
        }
        else if(!gameBoard.GameWon){
            cout << "FALSEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << endl;
        }
                        // || (gameBoard.GameWon && !gameWonAndLeaderboardDisplayed)
        if (gameBoard.LeaderBoardClicked) {
//            NeedtoRenderAgain = true;
            if(!gameBoard.GameWon){
                gameBoard.hideBackWhenLeaderboardCLicked(gamewindow);
            }
            gamewindow.display();
            sf::RenderWindow LeaderBoardWindow(sf::VideoMode(fileData[0] * 16 , fileData[1] * 16 + 50),
                                               "Leaderboard Window", sf::Style::Close);

//            leaderBoardIsOpen = true;
//            paused = true; // Pause the timer when leaderboard window opens
            pause_time = chrono::steady_clock::now(); // Record the pause time


            while (LeaderBoardWindow.isOpen()) {
                sf::Event event;
                while (LeaderBoardWindow.pollEvent(event)) {
                    if(LeaderBoardWindow.isOpen() && paused){
                        leaderboardOpenedWhilePaused = true;
                    }
                    else if(LeaderBoardWindow.isOpen() && !paused){
                        leaderboardOpenedWhilePaused = false;
                    }
                    if (event.type == sf::Event::Closed) { //depends on your device
                        gameBoard.GameWon = false;
                        gameBoard.LeaderBoardClicked = false;
                        LeaderBoardWindow.close();
                        std::cout << "Space bar pressed, window closed" << std::endl;
//                        leaderBoardIsOpen = false;
//                        gameBoard.gamePaused = false;
                        gameWonAndLeaderboardDisplayed = true; // Set the flag to true when closing the leaderboard window
                        if (leaderboardOpenedWhilePaused) {
                            paused = true; // Pause the game if leaderboard was opened while paused
//                            leaderboardOpenedWhilePaused = false; // Reset the flag
                        }
                        else if(!leaderboardOpenedWhilePaused){
                            cout << "YUPPPPPPPPPPPPPPPPP" << endl;
                            paused = false; // Resume the game if leaderboard was opened while not paused
//                            leaderboardOpenedWhilePaused = false; // Reset the flag
                        }

//                        paused = true;
                        auto unPausedTime = chrono::steady_clock::now();
                        elapsed_paused_time += chrono::duration_cast<chrono::seconds>(
                                unPausedTime - pause_time).count();
                    }
                }
                //if(NeedtoRenderAgain) {
                    leaderBoard.render(fileData[0], fileData[1], LeaderBoardWindow);
                    LeaderBoardWindow.display();
                //}
            }

        }


        auto game_duration = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start_time);
        int total_time = game_duration.count();

        int minutes;
        int seconds;


        if (!paused and !gameBoard.LeaderBoardClicked && !gameBoard.GameWon && !gameBoard.GameLost) {
//            gameBoard.gamePaused = false;

            total_time = total_time - elapsed_paused_time;

            minutes = int(total_time) / 60;
            seconds = (int) (total_time) % 60;
            // Separate minutes into individual digits
        }

        int tensMinutes = minutes / 10;  // Get the tens place digit
        int onesMinutes = minutes % 10;   // Get the ones place digit

        // Separate seconds into individual digits
        int tensSeconds = seconds / 10;  // Get the tens place digit
        int onesSeconds = seconds % 10;   // Get the ones place digit

        // logic goes here
        if (tensMinutes == 0) {
            ctimZ.loadDigit0(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensMinutes == 1) {
            ctimZ.loadDigit1(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensMinutes == 2) {
            ctimZ.loadDigit2(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensMinutes == 3) {
            ctimZ.loadDigit3(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensMinutes == 4) {
            ctimZ.loadDigit4(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensMinutes == 5) {
            ctimZ.loadDigit5(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensMinutes == 6) {
            ctimZ.loadDigit6(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensMinutes == 7) {
            ctimZ.loadDigit7(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensMinutes == 8) {
            ctimZ.loadDigit8(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensMinutes == 9) {
            ctimZ.loadDigit9(gamewindow, fileData[0] * 32 - 97, 32 * (fileData[1] + 0.5) + 16);
        }

        if (onesMinutes == 0) {
            ctimZ.loadDigit0(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesMinutes == 1) {
            ctimZ.loadDigit1(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesMinutes == 2) {
            ctimZ.loadDigit2(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesMinutes == 3) {
            ctimZ.loadDigit3(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesMinutes == 4) {
            ctimZ.loadDigit4(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesMinutes == 5) {
            ctimZ.loadDigit5(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesMinutes == 6) {
            ctimZ.loadDigit6(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesMinutes == 7) {
            ctimZ.loadDigit7(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesMinutes == 8) {
            ctimZ.loadDigit8(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesMinutes == 9) {
            ctimZ.loadDigit9(gamewindow, fileData[0] * 32 - 76, 32 * (fileData[1] + 0.5) + 16);
        }

        if (tensSeconds == 0) {
            ctimZ.loadDigit0(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensSeconds == 1) {
            ctimZ.loadDigit1(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensSeconds == 2) {
            ctimZ.loadDigit2(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensSeconds == 3) {
            ctimZ.loadDigit3(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensSeconds == 4) {
            ctimZ.loadDigit4(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensSeconds == 5) {
            ctimZ.loadDigit5(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensSeconds == 6) {
            ctimZ.loadDigit6(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensSeconds == 7) {
            ctimZ.loadDigit7(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensSeconds == 8) {
            ctimZ.loadDigit8(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }
        if (tensSeconds == 9) {
            ctimZ.loadDigit9(gamewindow, fileData[0] * 32 - 54, 32 * (fileData[1] + 0.5) + 16);
        }

        if (onesSeconds == 0) {
            ctimZ.loadDigit0(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesSeconds == 1) {
            ctimZ.loadDigit1(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesSeconds == 2) {
            ctimZ.loadDigit2(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesSeconds == 3) {
            ctimZ.loadDigit3(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesSeconds == 4) {
            ctimZ.loadDigit4(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesSeconds == 5) {
            ctimZ.loadDigit5(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesSeconds == 6) {
            ctimZ.loadDigit6(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesSeconds == 7) {
            ctimZ.loadDigit7(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesSeconds == 8) {
            ctimZ.loadDigit8(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }
        if (onesSeconds == 9) {
            ctimZ.loadDigit9(gamewindow, fileData[0] * 32 - 33, 32 * (fileData[1] + 0.5) + 16);
        }


        cout << total_time << endl;
        if(inGameScreen) {
            gamewindow.display();
        }
        else{
            gamewindow.close();
        }

        bool gameWon = gameBoard.GameWon;
        if (gameWon && !GameOfficiallyWON) {
            gameBoard.numFlagsPlaced = 0;
            std::string userName = welcomeWindow.getUserInput();

            // Format the time
            int minutes = total_time / 60;
            int seconds = total_time % 60;
            std::stringstream formattedTime;
            formattedTime << std::setw(2) << std::setfill('0') << minutes << ":"; // Set width to 2 and fill with '0'
            formattedTime << std::setw(2) << std::setfill('0') << seconds;
            std::string gameTime = formattedTime.str();

            // Store user info
            leaderBoard.storeUserInfo(userName, gameTime);
            leaderBoard.updateMapWithUserInfo(userName, gameTime); // Update the map with new user info

            GameOfficiallyWON = true;
            sf::RenderWindow LeaderBoardWindow2(sf::VideoMode(fileData[0] * 16 , fileData[1] * 16 + 50),
                                               "Updated Leaderboard Window", sf::Style::Close);
            while(LeaderBoardWindow2.isOpen()) {
                while (LeaderBoardWindow2.pollEvent(event)) {
                    if (event.type == sf::Event::Closed){
                        LeaderBoardWindow2.close();
                    }
                }

                leaderBoard.render(fileData[0], fileData[1], LeaderBoardWindow2);
                LeaderBoardWindow2.display();
            }

        }
    }
    return 0;
}

