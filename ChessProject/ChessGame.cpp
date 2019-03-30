#include "ChessGame.h"
#include <string>

ChessGame::ChessGame()
{
    Names[0] = "Black";
    Names[1] = "White";
}

void ChessGame::PlayChess()
{
    Board = new Field();
    
    Color turn = WHITE;
    string oldpos = "something", newpos = "else";
    bool Check = false;

    while (true)
    {
        do
        {
            Board->PrintField();

            if (Check)
                cout << "Check!" << endl;

            cout << " It is " << Names[turn] << "'s turn." << endl << endl;

            cout << " -Enter your move: ";
            cin >> oldpos;

            if (oldpos == "HELP" || oldpos == "help")
            {
                ShowHelp();
                continue;
            }

            cin >> newpos;

            if ((oldpos == "CASTLE" || oldpos == "castle") && (newpos == "RIGHT" || newpos == "right" || newpos == "LEFT" || newpos == "left"))
            {
                if (Board->Castle(turn, newpos))
                    break;
            }
        } 
        while (!Board->Move(oldpos, newpos, turn));

        turn = (Color) !turn;

        Check = Board->IsCheck(turn);
        if (Check && Board->IsCheckmate(turn))
            break;
    }

    Board->PrintField();
    cout << "Checkmate! " << Names[!turn] << " wins!" << endl;
    system("pause");

    delete Board;
}

void ChessGame::ShowHelp()
{
    system("cls");
    
    cout << endl << "Moving Pieces:" << endl << "--------------" << endl << endl;

    cout << "To move, type the coordinates of the piece you want to move followed by the coordinates of your desired destination." << endl << endl;

    cout << "\t-Example: D7 D5" << endl << endl;

    cout << endl << "Special Commands:" << endl << "-----------------" << endl << endl;

    cout << " HELP: Shows this message." << endl << endl;

    cout << " CASTLE RIGHT/LEFT: Swaps the King with the right/left Rook if the requirements are met" << endl << endl;

    cout << "\t-Requirements: Both pieces have never moved before, the squares between them are empty,\n\t and the King is not in check for every square till his final destination" << endl << endl;

    system("pause");
}    
