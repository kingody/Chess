#include "Rook.h"

Rook::Rook(char r, char c, Color color):Piece(r, c, color)
{
    value = 5;
    id = 'R';
    HasMoved = 0;
}

Rook::Rook(const Rook &old):Piece(old)
{
    HasMoved = old.HasMoved;
}

Piece* Rook::CreateCopy()
{
    return new Rook(*this);
}

bool Rook::IsValidMove(char newrow, char newcol)
{
    char drow = newrow - row, dcol = newcol - column;

    bool IsStraight = (!drow && dcol) || (drow && !dcol);

    return IsStraight;
}

void Rook::Move(char newrow, char newcol)
{
    row = newrow;
    column = newcol;
    HasMoved = 1;
}
