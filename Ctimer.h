//
// Created by gael8 on 4/11/2024.
//

#ifndef MINESWEEPER_CTIMER_H
#define MINESWEEPER_CTIMER_H
#include<SFML/Graphics.hpp>
#include <chrono>
#include<string>
#include<vector>
#include "WelcomeWindow.h"
#pragma once
using namespace std::chrono;

struct Ctimer{
    // Constructor
    Ctimer();

    // Member functions
    // Function to load digit textures from file
    void loadDigit0(sf::RenderWindow& window, float posX, float posY);
    void loadDigit1(sf::RenderWindow& window, float posX, float posY);
    void loadDigit2(sf::RenderWindow& window, float posX, float posY);
    void loadDigit3(sf::RenderWindow& window, float posX, float posY);
    void loadDigit4(sf::RenderWindow& window, float posX, float posY);
    void loadDigit5(sf::RenderWindow& window, float posX, float posY);
    void loadDigit6(sf::RenderWindow& window, float posX, float posY);
    void loadDigit7(sf::RenderWindow& window, float posX, float posY);
    void loadDigit8(sf::RenderWindow& window, float posX, float posY);
    void loadDigit9(sf::RenderWindow& window, float posX, float posY);
    void loadDigitSlash(sf::RenderWindow& window, float posX, float posY);

    void startTimer();
    void pauseTimer();
    void resumeTimer();
    float getDisplayedTime();
    float getElaspedTime();




    bool isTimerRunning;
    float pausedTime;


    steady_clock::time_point startTime;    // Start time of the timer
    steady_clock::time_point pauseTime;
    std::chrono::milliseconds accumulatedTime; // New member variable



    sf::Sprite digitSprite;
    sf::Texture DigitTexture;


};


#endif //MINESWEEPER_CTIMER_H
