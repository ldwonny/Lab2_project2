#include "chessboard.h"

using namespace std;


void ChessBoard::initialize_board()
{
    // TODO: implement initialize_board

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tiles[i][j] = create_piece("Empty", "Empty", i, j);
        }
    }
}

ostream& operator<<(ostream& os, const ChessBoard& board)
{
    // TODO: implement operator<<

    for (int i = 0; i < board.height; i++)
    {
        for (int j = 0; j < board.width; j++)
        {
            if (board.tiles[i][j]->get_flag() == 1)
            {
                os << board.tiles[i][j];
            }
            else cout << '.';
        }
        cout << endl;
    }
    return os;
}

ChessPiece* ChessBoard::operator[](string s)
{
    // TODO: implement operator[]
    // 이게 왜 필요하지?
    return tiles[0][0];
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
