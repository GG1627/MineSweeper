//
// Created by gael8 on 4/11/2024.
//
#include "Board.h"
#include "Ctimer.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <cctype>
#include<string>
#include<sstream>
using namespace std::chrono;
using namespace std;

Ctimer::Ctimer() {
    if (!DigitTexture.loadFromFile("files/images/digits.png")) {
        cerr << "could not load file" << endl;
    }
    startTime = steady_clock::now();
    isTimerRunning = false;
    pausedTime = 0.0f;
}


void Ctimer::startTimer() {
    startTime = chrono::steady_clock::now();
    isTimerRunning = true;
}
void Ctimer::pauseTimer(){
    if (isTimerRunning) {
        pauseTime = chrono::steady_clock::now();
        isTimerRunning = false;
    }
    cout << "timer is paused" << endl;
}

void Ctimer::resumeTimer(){
    if (!isTimerRunning) {
        startTime = chrono::steady_clock::now() - (pauseTime - startTime);
        isTimerRunning = true;
    }
    cout << "timer is running" << endl;

}


//if (!isTimerRunning) {
//startTime += chrono::steady_clock::now() - pauseTime;
//isTimerRunning = true;
//}

float Ctimer::getDisplayedTime() {
    if (isTimerRunning) {
        return chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count();
    } else {
        return pausedTime;
    }
}

float Ctimer::getElaspedTime() {
    if (isTimerRunning) {
        return chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count();
    } else {
        return pausedTime;
    }
}

void Ctimer::loadDigit0(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 0;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigit1(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 1;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigit2(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 2;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigit3(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 3;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigit4(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 4;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigit5(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 5;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigit6(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 6;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigit7(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 7;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigit8(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 8;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigit9(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 9;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}

void Ctimer::loadDigitSlash(sf::RenderWindow& window, float posX, float posY) {
    digitSprite.setTexture(DigitTexture);

    int digitWidth = 21;
    int digitHeight = 32;
    int left = digitWidth * 10;
    int top = 0;

    sf::IntRect digitRect(left, top, digitWidth, digitHeight);

    // Set the texture rectangle for the sprite
    digitSprite.setTextureRect(digitRect);

    // Set the position of the sprite
    digitSprite.setPosition(posX, posY);

    // Draw the sprite to the window
    window.draw(digitSprite);
}


//
//auto start_time = chrono::high_resolution_clock::now();
//
//auto pause_time = chrono::high_resolution_clock::now();
//auto elapsed_paused_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - pause_time).count();
//
//bool paused = false;
//
//if(pauseBttn.getGlobalBounds(). containes(vec.x, vec.y)){
//    paused = !paused;
//
//    if(paused){
//        cout << "paused" << endl;
//        pauseTime = chrono::high_resolution_clock::now();
//    }
//    else{
//        // unpaused
//        auto unPaused = chrono::steady_clock::now();
//        elapsed_paused_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count();
//    }
//}
//
//auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now());
//int total_time = game_duration.count();
//
//if(!paused){
//    total_time = total_time - elapsed_pased_time;
//    minutes = total_time / 60;
//    seconds = total_time % 60;
//}











