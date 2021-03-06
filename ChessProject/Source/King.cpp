﻿#include "King.hpp"
#include <cstdlib>

King::King(char r, char c, Color color) : Piece(r, c, color, 100, 'K') {}

King::King(const King &old):Piece(old)
{
    HasMoved = old.HasMoved;
}

Piece* King::CreateCopy()
{
    return new King(*this);
}

bool King::IsValidMove(char newrow, char newcol)
{
    char drow = abs(newrow - row), dcol = abs(newcol - column);

    bool isAdjacent = (drow || dcol) && (drow < 2) && (dcol < 2);

    bool isCastle = (dcol == 2) && !HasMoved && (row = (color ? 7 : 0));

    return isAdjacent || isCastle;
}

void King::Move(char newrow, char newcol)
{
    row = newrow;
    column = newcol;
    HasMoved = 1;
}
