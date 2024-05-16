//
// Created by gael8 on 4/14/2024.
//
#include "LeaderBoard.h"
#include <iostream>
#include<fstream>
#include <sstream>

LeaderBoard::LeaderBoard() {
    // Read configuration data from file
    std::ifstream file("files/config.cfg");
    std::string line;
    if (!file.is_open()) {
        std::cerr << "file not opened" << std::endl;
    }
    while (getline(file, line, '\n')) {
        fileDataZ.push_back(stoi(line));
    }

    if (!font.loadFromFile("files/font.ttf")) {
        std::cerr << "Error: Failed to load font" << std::endl;
        // Handle error
    }

    std::ifstream file2("files/leaderboard.txt");
    std::string read;
    if (!file2.is_open()) {
        std::cerr << "file not opened" << std::endl;
    }
    else {
        while (std::getline(file2, line)) {
            std::stringstream ss(line);
            std::string timeStr, name;

            // Split the line into time and name
            if (std::getline(ss, timeStr, ',')) {
                // Extract time and name substrings
                std::string time = timeStr.substr(0, 5);
                std::string name = line.substr(6); // Start from index 6 to the end

                // Insert into map
                myMap.emplace(time, name);
            }
        }
        file2.close(); // Close the file stream when done
    }


    rectangle.setSize(sf::Vector2f(fileDataZ[0] * 16 , fileDataZ[1] * 16 + 50));
    rectangle.setFillColor(sf::Color(74, 12, 36));

    text.setFont(font);
    text.setString("LEADERBOARD");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(text, fileDataZ[0] * 16 / 2.0f, fileDataZ[1] * 16 / 5.0f);

}

void LeaderBoard::updateMapWithUserInfo( std::string& userName, std::string& gameTime) {
    // Insert the new user information into the map
    userName = userName + "*";

    myMap.emplace(gameTime, userName);
}


void LeaderBoard::storeUserInfo(const std::string& userName, const std::string& gameTime) {
    std::ofstream file("files/leaderboard.txt", std::ios_base::app); // Append mode

    if (!file.is_open()) {
        std::cerr << "Failed to open leaderboard file" << std::endl;
        return;
    }

    // Write user's information (name and time) to the file
     file << "\n" <<gameTime << ", " <<  userName; // Assuming format: name,time

    file.close();
}


void LeaderBoard::loadNames(sf::RenderWindow& window) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);


    // Draw each player's name and time
    int yOffset = 0;
    int i = 1; // Counter for ranking
    int iterations = 0;
    for (const auto& entry : myMap) {
        if (iterations >= 5) {
            break; // Exit the loop once 5 entries have been processed
        }
        // Time column
        // Position column
        text.setString(std::to_string(i) + ".");
        text.setPosition(fileDataZ[0] * 8/2, fileDataZ[1] * 12 / 2.0f + yOffset); // Adjust as needed
        window.draw(text);

        text.setString(entry.first);
        text.setPosition(fileDataZ[0] * 13/2, fileDataZ[1] * 12 / 2.0f + yOffset); // Adjust as needed
        window.draw(text);

        // Name column
        text.setString(entry.second);
        text.setPosition(fileDataZ[0] * 20/2, fileDataZ[1] * 12 / 2.0f + yOffset); // Adjust as needed
        window.draw(text);

        yOffset += 35;
        i++;
        iterations++;
    }
}



void LeaderBoard::setText(sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}


void LeaderBoard::render(int numCol, int numRow, sf::RenderWindow& window) {
    window.draw(rectangle);
    window.draw(text);
    loadNames(window);
}




