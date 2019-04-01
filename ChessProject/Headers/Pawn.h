#pragma once
#include "Piece.h"

class Pawn : public Piece
{
    public:
        Pawn(char, char, Color);
        //Pawn(const Pawn&);

        Piece* CreateCopy();
        bool IsValidMove(char, char);
        bool IsCapture(char, char);
};
