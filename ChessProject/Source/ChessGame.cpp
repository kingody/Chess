#include "ChessGame.hpp"
#include <string>

ChessGame::ChessGame()
{
    Names[0] = "Black";
    Names[1] = "White";

    CurrentPlayer = WHITE;
    Board = NULL;
}

void ChessGame::ShowMenu()
{
    char choice;
    
    system("cls");

    PrintFromFile("menu.txt");

    cout << "Select your choice: ";
    cin >> choice;
}

bool ChessGame::Command(string command)
{
    if (command == "HELP" || command == "help")
    {   
        system("cls");
        PrintFromFile("help.txt");
        system("pause");
        return true;
    }    
    else if (command == "SAVE" || command == "save")
    {
        SaveGame();
        return true;
    }
    else if (command == "SAVEAS" || command == "saveas")
    {
        string filename;
        cin >> filename;

        SaveGame(filename);
        return true;
    }
    else if (command == "LOAD" || command == "load")
    {
        string filename;
        cin >> filename;
        if (!Import2(filename))
        {
            system("pause");
            return false;
        }
        return true;
    }

    string newpos;
    cin >> newpos;

    if (!Board->Move(command, newpos, CurrentPlayer))
    {
        system("pause");
        return false;
    }
    
    CurrentPlayer = (Color) !CurrentPlayer;
    return true;
}

void ChessGame::PlayChess()
{
    Board = new Field();
    
    string command;
    bool isCheck = false;

    while (true)
    {
        do
        {
            PrintField();

            if (isCheck)
                cout << "Check!" << endl;

            cout << " It is " << Names[CurrentPlayer] << "'s turn." << endl << endl;

            cout << " -Enter your move: ";
            cin >> command;
        } 
        while (!Command(command));

        isCheck = Board->IsCheck(CurrentPlayer);
        if (isCheck && Board->IsCheckmate(CurrentPlayer))
            break;
    }

    PrintField();
    cout << "Checkmate! " << Names[!CurrentPlayer] << " wins!" << endl;
    system("pause");

    delete Board;
}

void ChessGame::PrintField()
{
    system("cls");
    
    cout << "\t\t " << Names[0] << endl;
    
    Board->PrintField();

    cout << "\t\t " << Names[1] << endl << endl;
}

void ChessGame::PrintFromFile(string filename)
{
    fstream file;

    file.open(filename, ios::in);

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {           
            cout << line << endl;
        }
        cout << endl;
    }
    else
        cout << "Cannot find " + filename << endl;
}

void ChessGame::SaveGame()
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

    SaveToFile(file);

    cout << "File saved at " + filename << endl;

    system("pause");
}

void ChessGame::SaveGame(string filename)
{
    fstream file;

    filename = "Saves/" + filename + ".chs";

    file.open(filename, ios::in);

    if (!file.is_open())
    {
        file.open(filename, ios::out);

        if (!file.is_open())
        {
            cout << "Error while creating file." << endl;
        }
        else
        {
            SaveToFile(file);
            cout << "File saved at " + filename << endl;
        }
    }
    else
    {
        cout << "This file already exists." << endl;
    }

    system("pause");
}

void ChessGame::SaveToFile(fstream &file)
{
    char id;

    file << Names[0] << endl << Names[1] << endl;
	file << (int) Board->EnPassantStatus() << ' ' << (int) Board->GetEnPassantColumn() << endl;

    for (char i = 0; i < 8; i++)
    {
        for (char j = 0; j < 8; j++)
        {
            if ((*Board)[i][j])
            {
                if ((*Board)[i][j]->GetColor())
                {
                    id = (*Board)[i][j]->GetId() + 32;
                }
                else
                {
                    id = (*Board)[i][j]->GetId();
                }

                file << id;
            }
            else
            {
                file << '-';
            }
        }

        file << endl;
    }

    for (char i = 0; i < 8; i += 7)
    {
        for (char j = 0; j < 8; j += 7)
        {
            if ((*Board)[i][j]->GetId() == 'R')
            {
                file << ((Rook*) (*Board)[i][j])->HasMoved << ' ';
            }
            else
            {
                file << '1 ';
            }
        }

        if ((*Board)[i][4]->GetId() == 'K')
        {
            file << ((King*) (*Board)[i][4])->HasMoved << ' ';
        }
        else
        {
            file << '1 ';
        }

        file << endl;
    }

    file << CurrentPlayer;

    file.close();
}

bool ChessGame::Import(string filename)
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
        CurrentPlayer = (Color) color;
        file.close();
        return true;
    }
    cout << "File not found." << endl;
    return false;
}

bool ChessGame::Import2(string filename)
{
    filename = "Saves/" + filename + ".chs";

    ifstream file(filename);

    if (file.is_open())
    {
        string oldpos, newpos;
        CurrentPlayer = WHITE;
        
        delete Board;
        Board = new Field();

        while (file >> oldpos >> newpos)
        {
            Board->Move(oldpos, newpos, CurrentPlayer);
            CurrentPlayer = (Color)!CurrentPlayer;
        }
    }
    
    return false;
}
