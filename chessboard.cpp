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
    int x = toupper(s[1]) - 'A';
    int y = height - s[2] + '0';
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
    type = tiles[y][x]->get_type();
    color = tiles[y][x]->get_color();

    if (type == "King")
    {

    }
    else if (type == "Queen")
    {

    }
    else if (type == "Rook")
    {

    }
    else if (type == "Bishop")
    {

    }
    else if (type == "Knight")
    {

    }
    else if (type == "Pawn") // 1. color check, 2. location check, 3. enemy check.
    {
        if (color == "Black")
        {
            if (y == 1)
            {
                if ((posy == y + 1 && posx == x) && tiles[posy][posx]->get_flag() == 0) // target tile is empty
                {
                    return 1;
                }
                else if ((posy == y + 2 && posx == x) && (tiles[posy][posx]->get_flag() == 0 && tiles[posy-1][posx]->get_flag() == 0))
                {
                    return 1;
                }
            }
            else
            {
                if ((posy == y + 1 && posx == x) && tiles[posy][posx]->get_flag() == 0) // target tile is empty
                {
                    return 1;
                }
            }
            if ((posy == y + 1) && (posx == x - 1 || posx == x + 1))
            {
                if (tiles[posy][posx]->get_color() == "White")
                {
                    return 2;
                }
            }
            return 0;
        }
        else 
        {
            if (y == height - 2)
            {
                if ((posy == y - 1 && posx == x) && tiles[posy][posx]->get_flag() == 0) // target tile is empty
                {
                    return 1;
                }
                else if ((posy == y - 2 && posx == x) && (tiles[posy][posx]->get_flag() == 0 && tiles[posy + 1][posx]->get_flag() == 0))
                {
                    return 1;
                }
            }
            else
            {
                if ((posy == y - 1 && posx == x) && tiles[posy][posx]->get_flag() == 0) // target tile is empty
                {
                    return 1;
                }
            }
            if ((posy == y - 1) && (posx == x - 1 || posx == x + 1))
            {
                if (tiles[posy][posx]->get_color() == "Black")
                {
                    return 2;
                }
            }
            return 0;
        }
        return 0;
    }
}