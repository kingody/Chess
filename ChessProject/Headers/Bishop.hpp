#pragma once
#include "Piece.hpp"

class Bishop : public Piece
{
    public:
        Bishop(char, char, Color);

        Piece* CreateCopy();
        bool IsValidMove(char, char);
};