//
// Created by gael8 on 4/14/2024.
//

#ifndef MINESWEEPER_LEADERBOARD_H
#define MINESWEEPER_LEADERBOARD_H
#include<SFML/Graphics.hpp>
#include "WelcomeWindow.h"
#include<string>
#include<map>

struct LeaderBoard{
    LeaderBoard();

    WelcomeWindow weweWindow;

    void updateMapWithUserInfo(std::string& userName, std::string& gameTime);

    void storeUserInfo(const std::string& userName, const std::string& gameTime); // Method to store user info


    bool leaderboardWindowOpen = false;
    sf::RenderWindow leaderboardWindow;

    void render(int numCol, int numRow, sf::RenderWindow& window);
    std::map<std::string, std::string> myMap;

    void loadNames(sf::RenderWindow& window);

    void getUserInfo();


    std::vector<int> fileDataZ;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape rectangle;


    void setText(sf::Text& text, float x, float y);



};

#endif //MINESWEEPER_LEADERBOARD_H
