#pragma once
#include "Field.hpp"

class ChessGame
{
    public:
        ChessGame();

        void ShowMenu();

        bool Command(Color&, string);

        void PlayChess();

        void PrintField();

        void PrintFromFile(string);

        void SaveGame(Color);
        void SaveGame(Color, string);
        void SaveToFile(Color, fstream&);

        bool Import(string, Color&);

    private:
        std::string Names[2];

        Field* Board;
};