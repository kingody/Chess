#include "ChessGame.hpp"
#include <string>

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
                system("pause");
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
        SaveGame(turn);
        return true;
    }
    else if (command == "SAVEAS" || command == "saveas")
    {
        string filename;
        cin >> filename;

        SaveGame(turn, filename);
        return true;
    }
    else if (command == "OPEN" || command == "open")
    {
        string filename;
        cin >> filename;
        if (!Import(filename, turn))
        {
            system("pause");
            return false;
        }
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
    bool isCheck = false;

    while (true)
    {
        do
        {
            PrintBoard();

            if (isCheck)
                cout << "Check!" << endl;

            cout << " It is " << Names[turn] << "'s turn." << endl << endl;

            cout << " -Enter your move: ";
            cin >> command;
        } 
        while (!Command(turn, command));

        isCheck = Board->IsCheck(turn);
        if (isCheck && Board->IsCheckmate(turn))
            break;
    }

    PrintBoard();
    cout << "Checkmate! " << Names[!turn] << " wins!" << endl;
    system("pause");

    delete Board;
}

void ChessGame::PrintBoard()
{
    system("cls");
    
    cout << "\t\t " << Names[0] << endl;
    
    Board->PrintField();

    cout << "\t\t " << Names[1] << endl << endl;
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

void ChessGame::SaveGame(Color currentPlayer)
{
    fstream file;
    string filename;
    char index = 0;
    
    do
    {
        file.close();

        filename = "Saves/savefile" + to_string(index++) + ".chs";

        file.open(filename, ios::in);     
    } 
    while (file.is_open());

    file.open(filename, ios::out);

    SaveToFile(currentPlayer, file);

    cout << "File saved at " + filename << endl;

    system("pause");
}

void ChessGame::SaveGame(Color currentPlayer, string filename)
{
    fstream file;

    filename = "Saves/" + filename + ".chs";

    file.open(filename, ios::in);

    if (!file.is_open())
    {
        file.open(filename, ios::out);

        if (!file.is_open())
            cout << "Error while creating file." << endl;

        else
        {
            SaveToFile(currentPlayer, file);
            cout << "File saved at " + filename << endl;
        }
    }
    else
        cout << "This file already exists." << endl;

    system("pause");
}

void ChessGame::SaveToFile(Color currentPlayer,fstream &file)
{
    char id;

    file << Names[0] << endl << Names[1] << endl;

    for (char i = 0; i < 8; i++)
    {
        for (char j = 0; j < 8; j++)
        {
            if ((*Board)[i][j])
            {
                if ((*Board)[i][j]->GetColor())
                    id = (*Board)[i][j]->GetId() + 32;
                else
                    id = (*Board)[i][j]->GetId();
                file << id;
            }
            else
                file << '-';
        }
        file << endl;
    }
    file << currentPlayer;

    file.close();
}

bool ChessGame::Import(string filename, Color &turn)
{
    fstream file;
    int color;

    filename = "Saves/" + filename + ".chs";

    file.open(filename, ios::in);

    if (file.is_open())
    {
        delete Board;

        file >> Names[0] >> Names[1];
        Board = new Field(file);
        file >> color;
        turn = (Color) color;
        file.close();
        return true;
    }
    cout << "File not found." << endl;
    return false;
}
