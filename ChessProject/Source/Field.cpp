#include "Field.h"
#include <cstdlib>
#include <string>

Field::Field()
{
    //emptying the middle of the board
    for (char i = 0; i < 8; i++)
    {
        for (char j = 0; j < 8; j++)
            Pieces[i][j] = NULL;
    }
    //Pawns
    for (char i = 0; i < 8; i++)
    {
        Pieces[1][i] = new Pawn(1, i, BLACK);
        Pieces[6][i] = new Pawn(6, i, WHITE);

        //Pieces[4][i] = new Pawn(4, i, BLACK); //DEBUG
    }
    //Rest of the pieces
    for (char i = 0; i < 8; i += 7 )
    {
        Color color = i ? WHITE : BLACK;

        Pieces[i][0] = new Rook(i, 0, color);
        Pieces[i][7] = new Rook(i, 7, color);

        Pieces[i][1] = new Knight(i, 1, color);
        Pieces[i][6] = new Knight(i, 6, color);

        Pieces[i][2] = new Bishop(i, 2, color);
        Pieces[i][5] = new Bishop(i, 5, color);

        Pieces[i][3] = new Queen(i, 3, color);
        Pieces[i][4] = new King(i, 4, color);
    }
    Kings[0] = (King*) Pieces[0][4];
    Kings[1] = (King*) Pieces[7][4];
    CanEnPassant = false;

    //Pieces[1][2] = new Pawn(1, 2, WHITE); //DEBUG
}

Field::Field(const Field &old)
{
    for (char i = 0; i < 8; i++)
        for (char j = 0; j < 8; j++)
        {
            if (old.Pieces[i][j])
            {
                Pieces[i][j] = old.Pieces[i][j]->CreateCopy();

                if(Pieces[i][j]->GetId() == 'K')
                    Kings[Pieces[i][j]->GetColor()] = (King*)Pieces[i][j];
            }
            else
                Pieces[i][j] = NULL;
        }
    CanEnPassant = old.EnPassantStatus();
}

Field::~Field()
{
    for (char i = 0; i < 8; i++)
        for (char j = 0; j < 8; j++)
            delete Pieces[i][j];
}

Piece** Field::operator[](char pos)
{
    return Pieces[pos];
}

Piece* Field::Promote(Pawn* pawn)
{
    Piece *promoted = NULL;
    char row, column, id;
    Color color = pawn->GetColor();

    pawn->GetPos(row, column);

    cout << "Your pawn will be promoted." << endl << endl;
    do
    {
        cout << "Queen(Q), Rook(R), Bishop(B), Knight(H)" << endl << endl;
        cout << "Choose your piece by typing the right letter: ";

        cin >> id;
        //Clears the buffer
        cin.ignore(INT_MAX, '\n');
        cout << endl;
    } while (id != 'Q' && id != 'R' && id != 'B' && id != 'H');

    delete Pieces[row][column];
    cout << "Your pawn was promoted to a ";

    switch (id)
    {
        case 'Q':
            promoted = new Queen(row, column, color);
            cout << "Queen." << endl;
            break;

        case 'R':
            promoted = new Rook(row, column, color);
            cout << "Rook." << endl;
            break;

        case 'B':
            promoted = new Bishop(row, column, color);
            cout << "Bishop." << endl;
            break;

        case 'H':
            promoted = new Knight(row, column, color);
            cout << "Knight." << endl;
            break;

    }
    system("pause");
    return promoted;
}

bool Field::EnPassantStatus() const
{
    return CanEnPassant;
}

bool Field::CanCastle(Color color, char RookColumn)
{
    char row = color ? 7 : 0;
    
    if (Kings[color]->HasMoved || !Pieces[row][RookColumn] || Pieces[row][RookColumn]->GetId() != 'R' || ((Rook*)Pieces[row][RookColumn])->HasMoved)
    {
        return false;
    }
    return true;
}

bool Field::Castle(Color color, std::string direction)
{
    char row = color ? 7 : 0;
    char RookColumn = (direction == "RIGHT" || direction == "right") ? 7 : 0;

    if (!CanCastle(color, RookColumn))
        return false;

    char dcol = RookColumn - 4;
    char orientation = RookColumn ? 1 : -1;

    for (char i = orientation; i != dcol; i += orientation)
    {
        if (Pieces[row][4 + i])
            return false;
    }
    //King moves 2 squares towards the Rook
    ExecMove(row, 4, row, 4 + 2 * orientation);
    //Rook moves to one square before the King's original position
    ExecMove(row, RookColumn, row, 4 + orientation);

    return true;
}

bool Field::IsCheck(Color color)
{
    char row, column;

    Kings[color]->GetPos(row, column);

    for (char i = 0; i < 8; i++)
        for (char j = 0; j < 8; j++)
            if (Pieces[i][j] && (Pieces[i][j]->GetColor() != color) && CanMove(i, j, row - i, column - j, true))
            {
                cout << (int)i << (int)j << endl;
                system("pause");
                return true;
            }

    return false;
}

bool Field::IsCheckmate(Color color)
{ 
    for (char i = 0; i < 8; i++)
        for (char j = 0; j < 8; j++)
        {
            if (Pieces[i][j] && (Pieces[i][j]->GetColor() == color))
            {
                for (char newrow = 0; newrow < 8; newrow++)
                    for (char newcol = 0; newcol < 8; newcol++)
                    {
                        Field fieldcopy = *this;

                        if (fieldcopy.CanMove(i, j, newrow - i, newcol - j, true))
                        {
                            fieldcopy.ExecMove(i, j, newrow, newcol);

                            if (!fieldcopy.IsCheck(color))
                                return false;
                        }
                    }
            }
        }
    return true;
}

bool Field::OutOfBounds(char row, char column)
{
    return (column > 7) || (column < 0) || (row > 7) || (row < 0);
}

bool Field::PathBlocked(char oldrow, char oldcol, char drow, char dcol)
{
    char RowDirection = (drow < 0) ? -1 : 1;
    char ColumnDirection = (dcol < 0) ? -1 : 1;
    
    for (char row = 0, column = 0; (abs(row) < abs(drow) - 1) || (abs(column) < abs(dcol) - 1);)
    {
        if (abs(row) < abs(drow))
            row += RowDirection;
        if (abs(column) < abs(dcol))
            column += ColumnDirection;

        if (Pieces[oldrow + row][oldcol + column])
            return true;
    }
    return false;
}

bool Field::CanMove(char oldrow, char oldcol, char drow, char dcol, bool silentMode = false)
{
    if (!Pieces[oldrow][oldcol] || !(Pieces[oldrow][oldcol]->IsValidMove(oldrow + drow, oldcol + dcol))) 
    {
        if (!silentMode)
            cout << "Invalid move." << endl;
        return false;
    }

    Color color = Pieces[oldrow][oldcol]->GetColor();

    //Knight check
    if ((Pieces[oldrow][oldcol]->GetId() == 'H') && ( !Pieces[oldrow + drow][oldcol + dcol] || (Pieces[oldrow + drow][oldcol + dcol]->GetColor() != color) ))
        return true;

    //Colision check
    if (PathBlocked(oldrow, oldcol, drow, dcol))
    {
        if (!silentMode)
            cout << "Another piece is on the way." << endl;
        return false;
    }
    
    if (!Pieces[oldrow + drow][oldcol + dcol])
    {   
        //Pawn capture check
        if ((Pieces[oldrow][oldcol]->GetId() == 'P') && dcol)
        {
            bool IsEnPassant = CanEnPassant && (oldcol + dcol) == EnPassantColumn;

            if (!IsEnPassant)
            {
                if (!silentMode)
                    cout << "You cannot capture a blank square." << endl;
                return false;
            }
        }
        return true;
    }
    else if (Pieces[oldrow + drow][oldcol + dcol]->GetColor() != color)
    {   
        //Pawn block check
        bool IsForwardPawnMove = (Pieces[oldrow][oldcol]->GetId() == 'P') && !dcol;
        
        if (IsForwardPawnMove)
        {
            if (!silentMode)
                cout << "A pawn cannot capture a piece in front of itself." << endl;
            return false;
        }

        return true;
    }

    if (!silentMode)
        cout << "This square is occupied by a piece of the same color." << endl;
    return false;
}

bool Field::TryMove(char oldrow, char oldcol, char newrow, char newcol)
{
    Field FieldCopy = *this;
    Color color = FieldCopy[oldrow][oldcol]->GetColor();

    FieldCopy.ExecMove(oldrow, oldcol, newrow, newcol);

    if (FieldCopy.IsCheck(color))
        return false;

    return true;
}

void Field::ExecMove(char oldrow, char oldcol, char newrow, char newcol)
{
    //En Passant only
    if (CanEnPassant && (Pieces[oldrow][oldcol]->GetId() == 'P') && (abs(newcol - oldcol) == 1) && (newcol == EnPassantColumn))
    {
        char EnPassantRow = Pieces[oldrow][oldcol]->GetColor() ? 3 : 4;

        if (oldrow == EnPassantRow)
        {
            //This is the only case in which a piece is destroyed without another piece landing on top of it
            char direction = Pieces[oldrow][oldcol]->GetColor() ? 1 : -1;
            delete Pieces[newrow + direction][newcol];
            Pieces[newrow + direction][newcol] = NULL;
        }
    }

    Pieces[oldrow][oldcol]->Move(newrow, newcol);
    delete Pieces[newrow][newcol];
    Pieces[newrow][newcol] = Pieces[oldrow][oldcol];
    Pieces[oldrow][oldcol] = NULL;

    CanEnPassant = Pieces[newrow][newcol]->GetId() == 'P' && abs(newrow - oldrow) == 2;

    if (CanEnPassant)
        EnPassantColumn = newcol;
}

bool Field::Move(string oldpos, string newpos, Color CurrentPlayer)
 {  
    char oldrow = (int) oldpos[1] - '1';
    char oldcol = (int) oldpos[0] - ((oldpos[0] >= 'A' && oldpos[0] <= 'Z') ? 'A' : 'a');
    char newrow = (int) newpos[1] - '1';
    char newcol = (int) newpos[0] - ((newpos[0] >= 'A' && newpos[0] <= 'Z') ? 'A' : 'a');

    if ( OutOfBounds(oldrow, oldcol) || OutOfBounds(newrow, newcol) || !Pieces[oldrow][oldcol] || Pieces[oldrow][oldcol]->GetColor() != CurrentPlayer )
        return false;

    if ( CanMove(oldrow, oldcol, newrow - oldrow, newcol - oldcol) && TryMove(oldrow, oldcol, newrow, newcol) )
    {
        ExecMove(oldrow, oldcol, newrow, newcol);
        //Promotion check
        if (newrow == (Pieces[newrow][newcol]->GetColor() ? 0 : 7))
            Pieces[newrow][newcol] = Promote((Pawn*)Pieces[newrow][newcol]);

        return true;
    }
    return false;
}

void Field::PrintField()
{
    string id = "  ";
    system("cls");

    cout << endl << "     A   B   C   D   E   F   G   H \n";

    for (char i = 0; i < 8; i++)
    {
        cout << "   +---+---+---+---+---+---+---+---+\n " << i + 1 << ' ';

        for (char j = 0; j < 8; j++)
        {
            id[0] = Pieces[i][j]? Pieces[i][j]->GetId() : ' ';
            id[1] = (!Pieces[i][j] || Pieces[i][j]->GetColor())? ' ' : '`';

            cout << "| " << id;
        }
        cout << "| " << i + 1 << endl;
    }

    cout << "   +---+---+---+---+---+---+---+---+\n";
    cout << "     A   B   C   D   E   F   G   H \n\n";
}