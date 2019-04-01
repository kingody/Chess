#pragma once
#include "Field.h"

class ChessGame
{
    public:
        ChessGame();

        bool Command(Color&, string);

        void PlayChess();

        void ShowHelp();

        void SaveGame();

    private:
        std::string Names[2];

        Field* Board;
};