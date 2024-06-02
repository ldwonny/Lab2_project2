#include "game.h"

using namespace std;


void Game::read_file(string filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cerr << "Error: file open failed" << endl;
        exit(1);
    }

    ifs >> problem_id;
    ifs.ignore();
    getline(ifs, problem_specification); // problem_specification is string

    cout << "problem_id: [" << problem_id << "]" << endl;
    cout << "problem_specification: [" << problem_specification << "]" << endl;


    // TODO: CREATE CHESSBOARD
    int width, height;
    ifs >> height >> width;
    board = new ChessBoard(width, height); // empty board
    ifs.ignore();
    char temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ifs.get(temp);
            if (isalpha(temp)) // No empty tile
            {
                if (isupper(temp)) // White
                {
                    board->Settile("White", char_to_piece[temp], i, j, 1);
                }
                else // Black
                {
                    board->Settile("Black", char_to_piece[toupper(temp)], i, j, 1);
                }
            }
            else
            {
                board->Settile("Empty", "Empty", i, j, 0);
            }
        }
        ifs.ignore();
    }
}

void Game::open_output_file(string filename)
{
    ofs.open(filename);
    if (!ofs)
    {
        cerr << "Error: file open failed" << endl;
        exit(1);
    }
}

void Game::solve()
{
    switch (problem_id)
    {
    case 0:
        solve_print_board();
        break;
    case 1:
        solve_print_possible_moves();
        break;
    case 2:
        solve_check();
        break;
    case 3:
        solve_checkmate();
        break;
    case 4:
        solve_checkmate_in_one_move();
        break;
    default:
        cout << "Invalid problem_id" << endl;
        break;
    }
    return;
}

void Game::solve_print_board()
{
    ofs << *board;
}

void Game::solve_print_possible_moves()
{
    // TODO
    // problem_specification is string such as Qd7
    // Q is type of piece, d is location of x from left, 7 is location of y from bottom

    char type = problem_specification[0];
    string color;
    ChessBoard newboard(board->getwidth(), board->getheight());
    if (isupper(type)) { color = "White"; }
    else { color = "Black"; }

    (*board)[problem_specification]; // tiles[x][y] chesspiece
    
    if (char_to_piece[toupper(type)] == "Pawn")
    {

    }



}

int Game::solve_check()
{
    // TODO
    // EXAMPLE: "Black king is in check"
    //          "White king is not in check"
    return 0;
}

int Game::solve_checkmate()
{
    // TODO 
    // EXAMPLE: "Black king is checkmated"
    //          "White king is not checkmated"
    return 0;
}

int Game::solve_checkmate_in_one_move()
{
    // TODO
    // EXAMPLE: "Black king is checkmated in one move"
    //          "White king is not checkmated in one move"
    return 0;
}