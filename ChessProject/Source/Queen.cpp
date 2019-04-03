#include "Queen.hpp"
#include <cstdlib>

Queen::Queen(char r, char c, Color color) : Piece(r, c, color, 9, 'Q') {}

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
