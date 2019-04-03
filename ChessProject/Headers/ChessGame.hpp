#pragma once
#include "Field.hpp"

class ChessGame
{
    public:
        ChessGame();

        void ShowMenu();

        bool Command(string);

        void PlayChess();

        void PrintField();

        void PrintFromFile(string);

        void SaveGame();
        void SaveGame(string);
        void SaveToFile(fstream&);

        bool Import(string);
        bool Import2(string);

    private:
        std::string Names[2];

        Color CurrentPlayer;

        Field* Board;
};