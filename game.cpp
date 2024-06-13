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

    if (problem_id == 0) 
    {
        problem_specification = "";
    }
    else 
    {
        ifs >> problem_specification;
    }

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
    int x, y;
    x = (*board)[problem_specification]->get_x(); // tiles[x][y] chesspiece
    y = (*board)[problem_specification]->get_y();

    for (int i = 0; i < board->getheight(); i++)
    {
        for (int j = 0; j < board->getwidth(); j++)
        {
            if (i == x && j == y)
            {
                newboard.Settile(color, char_to_piece[toupper(type)], x, y, 1);
                continue;
            }
            if (board->possible_move_check(x, y, i, j) == 1) // can move
            {
                newboard.Settile("Reach", "Reach", i, j, 2);
            }
            else if (board->possible_move_check(x, y, i, j) == 2 || board->possible_move_check(x, y, i, j) == 3) // can attack
            {
                newboard.Settile("Attack", "Attack", i, j, 3);
            }
            else // cannot move
            {
                newboard.Settile("Empty", "Empty", i, j, 0);
            }
        }
    }
    ofs << newboard;
}

int Game::solve_check()
{
    // TODO
    // EXAMPLE: "Black king is in check"
    //          "White king is not in check"
    string color, s;
    if (problem_specification == "b")
    {
        color = "White";
        s = "Black";
    }
    else
    {
        color = "Black";
        s = "White";
    }
  
    if (board->is_check(problem_specification) == 1)
    {
        ofs << s << " king is in check" << endl;
        return 0;
    }
    else
    {
        ofs << s << " king is not in check" << endl;
        return 0;
    }
}

int Game::solve_checkmate()
{
    // TODO 
    // EXAMPLE: "Black king is checkmated"
    //          "White king is not checkmated"

    string color, s;
    if (problem_specification == "b")
    {
        color = "White";
        s = "Black";
    }
    else
    {
        color = "Black";
        s = "White";
    }

    if (board->is_checkmate(problem_specification) == 1)
    {
        ofs << s << " king is checkmated" << endl;
        return 0;
    }
    else
    {
        ofs << s << " king is not checkmated" << endl;
        return 0;
    }

    return 0;
}

int Game::solve_checkmate_in_one_move()
{
    // TODO
    // EXAMPLE: "Black king is checkmated in one move"
    //          "White king is not checkmated in one move"

    
    // possible move check
    // move or attack
    // is checkmate
    string color, s;
    if (problem_specification == "b")
    {
        color = "White";
        s = "Black";
    }
    else
    {
        color = "Black";
        s = "White";
    }

    if (board->is_checkmate_onemove(problem_specification) == 1)
    {
        ofs << s << " king is checkmated in one move" << endl;
        return 0;
    }
    else
    {
        ofs << s << " king is not checkmated in one move" << endl;
        return 0;
    }

    return 0;
}