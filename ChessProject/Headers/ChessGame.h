#pragma once
#include "Field.h"

class ChessGame
{
    public:
        ChessGame();

        bool Command(Color&, string);

        void PlayChess();

        void ShowHelp();

        void SaveGame(Color);

        bool Import(string, Color&);

    private:
        std::string Names[2];

        Field* Board;
};