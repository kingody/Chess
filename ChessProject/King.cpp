#include "King.h"
#include <cstdlib>

King::King(char r, char c, Color color):Piece(r, c, color)
{
    value = 99;
    id = 'K';
    HasMoved = 0;
}

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

    bool IsAdjacent = (drow || dcol) && (drow < 2) && (dcol < 2);

    return IsAdjacent;
}

void King::Move(char newrow, char newcol)
{
    row = newrow;
    column = newcol;
    HasMoved = 1;
}
