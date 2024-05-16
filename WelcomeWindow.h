#ifndef MINESWEEPER_WELCOMEWINDOW_H
#define MINESWEEPER_WELCOMEWINDOW_H
#include<SFML/Graphics.hpp>
#include<string>
#pragma once

class WelcomeWindow {
public:
    WelcomeWindow();

    void handleEvent(sf::Event event);
    void render(sf::RenderWindow& window);
    void moveCursor(int offset);
    const std::string& getUserInput(){
        return userInput;
    }

    std::string getUserName() const {
        return userInput;
    }
    void storeName();



    sf::RectangleShape rectangle;
    sf::Font font;
    sf::Text text;
    sf::Text text2;
    sf::Text inputText;
    std::string userInput;
    int cursorPosition = 0;
    std::vector<int> fileData1;



    void setText(sf::Text& text, float x, float y);
};







#endif //MINESWEEPER_WELCOMEWINDOW_H
