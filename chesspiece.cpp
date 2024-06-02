#include "chesspiece.h"

using namespace std;


ChessPiece::ChessPiece(string color, string type, int x, int y, int flag)
{
    this->color = color;
    this->type = type;
    this->x = x;
    this->y = y;
    this->flag = flag;
}

ostream& operator<<(ostream& os, const ChessPiece& piece)
{
    char c;
    c = piece_to_char[piece.type];
    if (piece.color == "Black")
    {
        c = tolower(c);
    }
    os << c;
    return os;
}

ChessPiece::ChessPiece(const ChessPiece& other)
{
    this->color = other.color;
    this->type = other.type;
    this->x = other.x;
    this->y = other.y;
    this->flag = other.flag;
}

ChessPiece* create_piece(string color, string type, int x, int y, int flag)
{
    // TODO : implement create_piece
    if (type == "King")
    {
        King* temp = new King(color, x, y, flag);
        return temp;
    }
    else if (type == "Queen")
    {
        Queen* temp = new Queen(color, x, y, flag);
        return temp;
    }
    else if (type == "Rook")
    {
        Rook* temp = new Rook(color, x, y, flag);
        return temp;
    }
    else if (type == "Bishop")
    {
        Bishop* temp = new Bishop(color, x, y, flag);
        return temp;
    }
    else if (type == "Knight")
    {
        Knight* temp = new Knight(color, x, y, flag);
        return temp;
    }
    else if (type == "Pawn")
    {
        Pawn* temp = new Pawn(color, x, y, flag);
        return temp;
    }
    else
    {
        ChessPiece* temp = new ChessPiece(color, type, x, y, flag);
        return temp;
    }
}

// NOTE: YOU CAN ADD OTHER FUNCTIONS HERE