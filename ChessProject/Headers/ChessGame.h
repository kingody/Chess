#pragma once
#include "Field.h"

class ChessGame
{
    public:
        ChessGame();

        void PlayChess();

        void ShowHelp();


    private:
        std::string Names[2];

        Field* Board;
};