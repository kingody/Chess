#pragma once
#include "Piece.h"

class Bishop : public Piece
{
    public:
        Bishop(char, char, Color);
        Bishop(const Bishop&);

        Piece* CreateCopy();
        bool IsValidMove(char, char);
};