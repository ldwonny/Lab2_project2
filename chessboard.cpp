#include "chessboard.h"

using namespace std;


void ChessBoard::initialize_board()
{
    // TODO: implement initialize_board
    tiles = new ChessPiece * *[height];
    for (int i = 0; i < height; i++)
    {
        tiles[i] = new ChessPiece * [width];
    }
}

ostream& operator<<(ostream& os, const ChessBoard& board)
{
    // TODO: implement operator<<

    for (int i = 0; i < board.height; i++)
    {
        for (int j = 0; j < board.width; j++)
        {
            if (board.tiles[i][j]->get_flag() == 1) // flag == 1 means that tile is chesspiece
            {
                os << *board.tiles[i][j];
            }
            else if (board.tiles[i][j]->get_flag() == 2) // flag == 2 means that tile can be rechable
            {
                os << 'o';
            }
            else if (board.tiles[i][j]->get_flag() == 3) // flag == 3 means that tile is attacked
            {
                os << 'x';
            }
            else os << '.';
        }
        os << endl;
    }
    return os;
}

ChessPiece* ChessBoard::operator[](string s)
{
    // TODO: implement operator[]
    int x = height - s[2] + '0';
    int y = toupper(s[1]) - 'A';
    return tiles[x][y];
}

ChessBoard& ChessBoard::operator=(const ChessBoard& other)
{
    // TODO: implement operator=

    return *this;
}

ChessBoard::ChessBoard(const ChessBoard& other)
{
    // TODO: implement copy constructor
}

// NOTE: YOU CAN ADD MORE FUNCTIONS HERE

void ChessBoard::Settile(string color, string type, int height, int width, int flag)
{
    tiles[height][width] = create_piece(color, type, height, width, flag);
}

int ChessBoard::possible_move_check(int x, int y, int posx, int posy) // x, y are location of piece, posx, posy are target location
{
    // return 1 move, return 2 attack, return 0 cannot move
    string type, color;
    type = tiles[x][y]->get_type();
    color = tiles[x][y]->get_color();

    if (type == "King")
    {
        // you don't need to consider color, location
        // just enemy check!

    }
    else if (type == "Queen")
    {
        cout << 2 << endl;
        return 0;
    }
    else if (type == "Rook")
    {
        cout << 3 << endl;
        return 0;
    }
    else if (type == "Bishop")
    {
        // recursive call? or 2d array
        cout << 4 << endl;
        return 0;
    }
    else if (type == "Knight")
    {
        cout << 5 << endl;
        return 0;
    }
    else if (type == "Pawn") // 1. color check, 2. location check, 3. enemy check.
    {
        if (color == "Black")
        {
            if (x == 1)
            {
                if ((posx == x + 1 && posy == y) && tiles[posx][posy]->get_flag() == 0) // target tile is empty
                {
                    return 1;
                }
                else if ((posx == x + 2 && posy == y) && (tiles[posx][posy]->get_flag() == 0 && tiles[posx - 1][posy]->get_flag() == 0))
                {
                    return 1;
                }
            }
            else
            {
                if ((posx == x + 1 && posy == y) && tiles[posx][posy]->get_flag() == 0) // target tile is empty
                {
                    return 1;
                }
            }
            if ((posx == x + 1) && (posy == y - 1 || posy == y + 1))
            {
                if (tiles[posx][posy]->get_color() == "White")
                {
                    return 2;
                }
            }
        }
        else
        {
            if (x == height - 2)
            {
                if ((posx == x - 1 && posy == y) && tiles[posx][posy]->get_flag() == 0) // target tile is empty
                {
                    return 1;
                }
                else if ((posx == x - 2 && posy == y) && (tiles[posx][posy]->get_flag() == 0 && tiles[posx + 1][posy]->get_flag() == 0))
                {
                    return 1;
                }
            }
            else
            {
                if ((posx == x - 1 && posy == y) && tiles[posx][posy]->get_flag() == 0) // target tile is empty
                {
                    return 1;
                }
            }
            if ((posx == x - 1) && (posy == y - 1 || posy == x + 1))
            {
                if (tiles[posx][posy]->get_color() == "Black")
                {
                    return 2;
                }
            }
        }
        return 0;
    }
}