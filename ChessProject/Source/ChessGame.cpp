﻿#include "ChessGame.h"
#include <string>
#include <fstream>

ChessGame::ChessGame()
{
    Names[0] = "Black";
    Names[1] = "White";

    Board = NULL;
}

bool ChessGame::Command(Color &turn, string command)
{
    if (command == "HELP" || command == "help")
    {   
        ShowHelp();
        return true;
    }    
    else if (command == "CASTLE" || command == "castle")
    {
        string direction;
        cin >> direction;

        if (direction == "RIGHT" || direction == "right" || direction == "LEFT" || direction == "left")
            if (!Board->Castle(turn, direction))
            {       
                cout << "You can't do that." << endl;
                return false;
            }
            else
            {
                turn = (Color) !turn;
                return true;
            }
       
        cout << "Invalid command." << endl;
        system("pause");
        return false;      
    }
    else if (command == "SAVE" || command == "save")
    {
        SaveGame();
        return true;
    }

    string newpos;
    cin >> newpos;

    if (!Board->Move(command, newpos, turn))
    {
        system("pause");
        return false;
    }
    
    turn = (Color) !turn;
    return true;
}

void ChessGame::PlayChess()
{
    Board = new Field();
    
    Color turn = WHITE;
    string command;
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
            cin >> command;
        } 
        while (!Command(turn, command));

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

    cout << " SAVE: Saves the current state of the game." << endl << endl;

    cout << " CASTLE RIGHT/LEFT: Swaps the King with the right/left Rook if the requirements are met" << endl << endl;

    cout << "\t-Requirements: Both pieces have never moved before, the squares between them are empty,\n\t and the King is not in check for every square till his final destination" << endl << endl;

    system("pause");
}

void ChessGame::SaveGame()
{
    fstream file;
    string filename;
    char index = 0;
    
    do
    {
        file.close();

        filename = "Saves/savefile" + to_string(index++) + ".txt";

        file.open(filename, ios::in);     
    } 
    while (file.is_open());

    file.open(filename, ios::out);

    for (char i = 0; i < 8; i++)
    {
        for (char j = 0; j < 8; j++)
        {
            if ((*Board)[i][j])
                file << (*Board)[i][j]->GetId() << (*Board)[i][j]->GetColor();
            
            else
                file << "--";
        }
        file << endl;
    }

    file.close();
    cout << "File saved";
    system("pause");
}
