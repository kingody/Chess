#pragma once

enum Color {BLACK, WHITE};

class Piece
{
    public:
        Piece(char , char , Color);
        Piece(const Piece&);
        virtual Piece* CreateCopy() = 0;

        Piece* operator[] (char);

        void GetPos(char&, char&) const;
        char GetValue() const;
        char GetId() const;
        Color GetColor() const;

        virtual bool IsValidMove(char, char) = 0;
        void Move(char, char);

    protected:
        char row;
        char column;
        char value;
        char id;
        Color color;
};
