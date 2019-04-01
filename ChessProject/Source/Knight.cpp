#include "Knight.h"
#include <cstdlib>

Knight::Knight(char r, char c, Color color):Piece(r, c, color)
{
    value = 3;
    id = 'H';
}

Piece* Knight::CreateCopy()
{
    return new Knight(*this);
}

bool Knight::IsValidMove(char newrow, char newcol)
{
    char dcol = abs(newcol - column), drow = abs(newrow - row);

    bool IsGamma = drow && dcol && (drow + dcol == 3);

    return IsGamma;
}