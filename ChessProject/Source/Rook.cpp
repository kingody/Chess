#include "Rook.hpp"

Rook::Rook(char r, char c, Color color) : Piece(r, c, color, 5, 'R') {}

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

    bool isStraight = (!drow && dcol) || (drow && !dcol);

    return isStraight;
}

void Rook::Move(char newrow, char newcol)
{
    row = newrow;
    column = newcol;
    HasMoved = 1;
}
