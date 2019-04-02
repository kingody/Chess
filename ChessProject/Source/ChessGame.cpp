#include "ChessGame.hpp"
#include <string>

ChessGame::ChessGame()
{
    Names[0] = "Black";
    Names[1] = "White";

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

bool ChessGame::Command(Color &turn, string command)
{
    if (command == "HELP" || command == "help")
    {   
        system("cls");
        PrintFromFile("help.txt");
        system("pause");
        return true;
    }    
    else if (command == "CASTLE" || command == "castle")
    {
        string direction;
        cin >> direction;

        if (direction == "RIGHT" || direction == "right" || direction == "LEFT" || direction == "left")
        {
            char rookColumn = (direction == "RIGHT" || direction == "right") ? 7 : 0;

            if (!Board->Castle(turn, rookColumn))
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
    else if (command == "LOAD" || command == "load")
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
            PrintField();

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

    PrintField();
    cout << "Checkmate! " << Names[!turn] << " wins!" << endl;
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
        while (!file.eof())
        {
            getline(file, line);
            cout << line << endl;
        }
    }
    else
        cout << "Cannot find " + filename << endl;
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
	file << (int) Board->EnPassantStatus() << ' ' << (int) Board->GetEnPassantColumn() << endl;

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

    for (char i = 0; i < 8; i += 7)
    {
        for (char j = 0; j < 8; j += 7)
        {
            if ((*Board)[i][j]->GetId() == 'R')
                file << ((Rook*) (*Board)[i][j])->HasMoved << ' ';

            else
                file << '1 ';
        }

        if ((*Board)[i][4]->GetId() == 'K')
            file << ((King*) (*Board)[i][4])->HasMoved << ' ';

        else
            file << '1 ';

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
