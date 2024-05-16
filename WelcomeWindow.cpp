//
// Created by gael8 on 4/10/2024.
//
#include <fstream>
#include "WelcomeWindow.h"
#include "Ctimer.h"
#include <iostream>
#include <cctype>

WelcomeWindow::WelcomeWindow() {
    std::ifstream file("files/config.cfg");
    std::string line;
    if(!file.is_open()){
        std::cerr << "file not opened" << std::endl;
    }
    while(getline(file, line, '\n')) {
        fileData1.push_back(stoi(line));
    }

    rectangle.setSize(sf::Vector2f(fileData1[0] * 32, fileData1[1] * 32 + 100));
    rectangle.setFillColor(sf::Color(2, 5, 102));

    if (!font.loadFromFile("files/font.ttf")) {
        std::cerr << "Error: Failed to load font" << std::endl;
        // Handle error
    }

    int row = fileData1[1] * 32;
    int col = fileData1[0] * 32;

    text.setFont(font);
    text.setString("WELCOME TO MINESWEEPER!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(text, fileData1[0] * 32 / 2.0f, fileData1[1] * 32 / 2.0f - 150);

    text2.setFont(font);
    text2.setString("Enter your name:");
    text2.setCharacterSize(20);
    text2.setFillColor(sf::Color::White);
    text2.setStyle(sf::Text::Bold);
    setText(text2, fileData1[0] * 32 / 2.0f, fileData1[1] * 32 / 2.0f - 75);

    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(sf::Color::Yellow);
    setText(inputText, fileData1[0] * 32 / 2.0f, fileData1[1] * 32 / 2.0f - 45);

}

void WelcomeWindow::setText(sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void WelcomeWindow::moveCursor(int offset) {
    cursorPosition += offset;
    cursorPosition = std::max(0, std::min((int)(userInput.size()), cursorPosition));
}



void WelcomeWindow::handleEvent(sf::Event event) {

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 65 && event.text.unicode <= 90 || event.text.unicode >= 97 && event.text.unicode <= 122) {
            if (std::isalpha(event.text.unicode)) {
                if (userInput.size() < 10) {
                    if (userInput.empty()) {
                        userInput += (char) (std::toupper(event.text.unicode));
                    }
                    else {
                        userInput += (char) (std::tolower(event.text.unicode));
                    }
                    inputText.setString(userInput);
                    moveCursor(1);
                }
            }
        }
        else if (event.text.unicode == '\b' && !userInput.empty()) {
            userInput.pop_back();
            inputText.setString(userInput);
            moveCursor(-1);
        }
        setText(inputText, fileData1[0] * 32 / 2.0f, fileData1[1] * 32 / 2.0f - 45);
    }
}

void WelcomeWindow::render(sf::RenderWindow& window) {
    window.draw(rectangle);
    window.draw(text);
    window.draw(text2);
    window.draw(inputText);


    // Draw cursor
    sf::Text cursor("|", font, 20);
    cursor.setFillColor(sf::Color::White);
    sf::Vector2f inputTextPosition = inputText.getPosition();
    float cursorX = fileData1[0] * 16;
    float cursorOffset = inputText.findCharacterPos(cursorPosition).x - inputTextPosition.x;
    cursor.setPosition(cursorX + cursorOffset,  fileData1[1] * 32 / 2.0f - 57);

    window.draw(cursor);
}