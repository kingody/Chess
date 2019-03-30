#pragma once
#include "Piece.h"


class Queen : public Piece
{
    public:
        Queen(char, char, Color);
        Queen(const Queen&);

        Piece* CreateCopy();
        bool IsValidMove(char, char);
};

