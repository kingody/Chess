#pragma once
#include "Piece.hpp"


class Queen : public Piece
{
    public:
        Queen(char, char, Color);

        Piece* CreateCopy();
        bool IsValidMove(char, char);
};

