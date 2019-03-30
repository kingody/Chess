#include "Queen.h"
#include <cstdlib>

Queen::Queen(char r, char c, Color color):Piece(r, c, color)
{
    value = 9;
    id = 'Q';
}

Queen::Queen(const Queen &old):Piece(old) {}

Piece* Queen::CreateCopy()
{
    return new Queen(*this);
}

bool Queen::IsValidMove(char newrow, char newcol)
{
    char drow = abs(newrow - row), dcol = abs(newcol - column);

    bool IsStraight = (!drow && dcol) || (drow && !dcol);
    bool IsDiagonal = (drow == dcol) && drow;

    return IsStraight || IsDiagonal;
}
