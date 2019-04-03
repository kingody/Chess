#include "Bishop.hpp"
#include <cstdlib>

Bishop::Bishop(char r, char c, Color color) : Piece(r, c, color, 3, 'B') {}

Piece* Bishop::CreateCopy()
{
    return new Bishop(*this);
}

bool Bishop::IsValidMove(char newrow, char newcol)
{
    char drow = abs(newrow - row), dcol = abs(newcol - column);

    bool isDiagonal = (drow == dcol) && drow;

    return isDiagonal;
}
