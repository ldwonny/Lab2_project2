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
        if (tiles[posx][posy]->get_color() == color) // cannot move
        {
            return 0;
        }
        if ((posy == y) && (abs(posx - x) == 1)) // Up, Down
        {
            if (tiles[posx][posy]->get_flag() == 1)
            {
                return 2;
            }
            else return 1;
        }
        else if ((posx == x) && (abs(posy - y) == 1)) //Right, Left
        {
            if (tiles[posx][posy]->get_flag() == 1)
            {
                return 2;
            }
            else return 1;
        }
        else if ((abs(posx - x) == 1) && (abs(posy - y) == 1)) // Diagonal
        {
            if (tiles[posx][posy]->get_flag() == 1)
            {
                return 2;
            }
            else return 1;
        }
        return 0;

    }
    else if (type == "Queen")
    {
        cout << 2 << endl;
        return 0;
    }
    else if (type == "Rook")
    {
        int colarr[26] = { 0, };
        for (int i = x - 1; i >= 0; i--)
        {
            colarr[i] = 1;
            if (tiles[i][y]->get_flag() == 1)
            {
                if (tiles[i][y]->get_color() == color)
                {
                    colarr[i] = 0;
                    break;
                }
                else
                {
                    colarr[i] = 2;
                    break;
                }
            }
        }
        for (int i = x + 1; i < height; i++)
        {
            colarr[i] = 1;
            if (tiles[i][y]->get_flag() == 1)
            {
                if (tiles[i][y]->get_color() == color)
                {
                    colarr[i] = 0;
                    break;
                }
                else
                {
                    colarr[i] = 2;
                    break;
                }
            }
        }
        if (posy == y)
        {
            return colarr[posx];
        }
        int rowarr[26] = { 0, };
        for (int i = y - 1; i >= 0; i--)
        {
            rowarr[i] = 1;
            if (tiles[x][i]->get_flag() == 1)
            {
                if (tiles[x][i]->get_color() == color)
                {
                    rowarr[i] = 0;
                    break;
                }
                else
                {
                    rowarr[i] = 2;
                    break;
                }
            }
        }
        for (int i = y + 1; i < width; i++)
        {
            rowarr[i] = 1;
            if (tiles[x][i]->get_flag() == 1)
            {
                if (tiles[x][i]->get_color() == color)
                {
                    rowarr[i] = 0;
                    break;
                }
                else
                {
                    rowarr[i] = 2;
                    break;
                }
            }
        }
        if (posx == x)
        {
            return rowarr[posy];
        }
        return 0;
    }
    else if (type == "Bishop")
    {
        cout << 4 << endl;
        return 0;
    }
    else if (type == "Knight")
    {
        if (tiles[posx][posy]->get_color() == color)
        {
            return 0;
        }
        if ((abs(x - posx) == 2) && (abs(y - posy) == 1))
        {
            if (tiles[posx][posy]->get_flag() == 1)
            {
                return 2;
            }
            else return 1;
        }
        else if ((abs(x - posx) == 1) && (abs(y - posy) == 2))
        {
            if (tiles[posx][posy]->get_flag() == 1)
            {
                return 2;
            }
            else return 1;
        }
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