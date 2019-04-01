#include "Bishop.h"
#include <cstdlib>

Bishop::Bishop(char r, char c, Color color):Piece(r, c, color)
{
    value = 3;
    id = 'B';
}

Piece* Bishop::CreateCopy()
{
    return new Bishop(*this);
}

bool Bishop::IsValidMove(char newrow, char newcol)
{
    char drow = abs(newrow - row), dcol = abs(newcol - column);

    bool IsDiagonal = (drow == dcol) && drow;

    return IsDiagonal;
}
