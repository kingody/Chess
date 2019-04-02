#pragma once
#include "Field.hpp"

class ChessGame
{
    public:
        ChessGame();

        bool Command(Color&, string);

        void PlayChess();

        void PrintField();

        void ShowHelp();

        void SaveGame(Color);
        void SaveGame(Color, string);
        void SaveToFile(Color, fstream&);

        bool Import(string, Color&);

    private:
        std::string Names[2];

        Field* Board;
};