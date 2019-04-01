#pragma once
#include "Troops.h"
#include <iostream>

using namespace std;

class Field
{
    public:
        Field();
        Field(const Field&);

        ~Field();

        Piece** operator[] (char);

        Piece* Promote(Pawn*);
        bool EnPassantStatus() const;
        bool CanCastle(Color, char);
        bool Castle(Color, string);

        bool IsCheck(Color);
        bool IsCheckmate(Color);

        bool OutOfBounds(char, char);
        bool PathBlocked(char, char, char, char);

        bool CanMove(char, char, char, char, bool);
        bool TryMove(char, char, char, char);
        void ExecMove(char, char, char, char);
        bool Move(string, string , Color);

        void PrintField();

    private:
        Piece* Pieces[8][8];
        King* Kings[2];

        bool CanEnPassant;
        char EnPassantColumn;
};