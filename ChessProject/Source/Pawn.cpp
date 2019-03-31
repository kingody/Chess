#include "Pawn.h"
#include <cstdlib>

Pawn::Pawn(char r, char c, Color color):Piece(r, c, color)
{
    value = 1;
    id = 'P';
}

Pawn::Pawn(const Pawn &old):Piece(old) {}

Piece* Pawn::CreateCopy()
{
    return new Pawn(*this);
}

bool Pawn::IsValidMove(char newrow, char newcol)
{
    char direction = color ? -1 : 1;  //upwards or downwards motion depends on color
    char drow = newrow - row, dcol = newcol - column;

    bool IsSingleStep = !dcol && (drow == direction);
    bool IsDoubleStep = (row == (color ? 1 : 6)) && (drow == 2 * direction);

    return IsSingleStep || IsCapture(drow, dcol) || IsDoubleStep;
}

bool Pawn::IsCapture(char drow, char dcol)
{
    char direction = color? -1:1;   //upwards or downwards motion depends on color

    return (abs(dcol) == 1) && (drow == direction);
}