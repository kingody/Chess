﻿#include "Piece.hpp"


Piece::Piece(char r, char c, Color color, char value, char id)
    :row(r), column(c), color(color), value(value), id(id) {}

Piece::Piece(const Piece &old)
{
    char oldrow, oldcol;
    old.GetPos(oldrow, oldcol);
   
    row = oldrow;
    column = oldcol;
    color = old.GetColor();
    value = old.GetValue();
    id = old.GetId();
}

Piece* Piece::operator[] (char pos)
{
    return &this[pos];
}

void Piece::GetPos(char &row, char &column) const
{
    row = this->row;
    column = this->column;
}

char Piece::GetValue() const
{
    return value;
}

char Piece::GetId() const
{
    return id;
}

Color Piece::GetColor() const
{
    return color;
}

void Piece::Move(char newrow, char newcol)
{
    row = newrow;
    column = newcol;
}