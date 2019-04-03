#pragma once
#include "Piece.hpp"


class Rook : public Piece
{
    public:
        Rook(char, char, Color);
        Rook(const Rook&);

        Piece* CreateCopy();
        bool IsValidMove(char, char);
        void Move(char, char);

        bool HasMoved{ false };
};
