#pragma once
#include "Troops.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class Field
{
    public:
        Field();
        Field(fstream&);
        Field(const Field&);

        ~Field();

        Piece** operator[] (char);

        Piece* CreatePiece(char, char, char, Color);
        Piece* Promote(Pawn*);
        bool EnPassantStatus() const;
        char GetEnPassantColumn() const;
        bool CanCastle(Color, char);
        bool Castle(Color, char);

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
        int EnPassantColumn;
};