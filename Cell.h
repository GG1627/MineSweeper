//
// Created by gael8 on 4/13/2024.
//
#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

struct Cell {
    // Constructor to initialize the cell's state
    Cell() : isBottomLayer(true), isMine(false), isFlagged(false), isSecretLayer(false) {}

    // Member functions to modify the cell's state
    void setState(bool bottomLayer, bool mine) {
        isBottomLayer = bottomLayer;
        isMine = mine;
    }


    // Variables representing the state of the cell
    bool isBottomLayer;
    bool isMine;
    bool isFlagged;
    bool isNumbered;
    bool isTopLayer;
    bool isSecretLayer;
    int proximityMines = 0;
};

#endif // MINESWEEPER_CELL_H
