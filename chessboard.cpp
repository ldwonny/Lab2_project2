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
    // deep copy
    width = other.width;
    height = other.height;
    initialize_board();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            string tempcolor = other.tiles[i][j]->get_color();
            string temptype = other.tiles[i][j]->get_type();
            int tempflag = other.tiles[i][j]->get_flag();
            tiles[i][j] = create_piece(tempcolor, temptype, i, j, tempflag);
        }
    }
}

// NOTE: YOU CAN ADD MORE FUNCTIONS HERE

void ChessBoard::Settile(string color, string type, int height, int width, int flag)
{
    tiles[height][width] = create_piece(color, type, height, width, flag);
}

ChessPiece* ChessBoard::gettile(int x, int y)
{
    return tiles[x][y];
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
                if (tiles[posx][posy]->get_type() == "King") return 3;
                else return 2;
            }
            else return 1;
        }
        else if ((posx == x) && (abs(posy - y) == 1)) //Right, Left
        {
            if (tiles[posx][posy]->get_flag() == 1)
            {
                if (tiles[posx][posy]->get_type() == "King") return 3;
                else return 2;
            }
            else return 1;
        }
        else if ((abs(posx - x) == 1) && (abs(posy - y) == 1)) // Diagonal
        {
            if (tiles[posx][posy]->get_flag() == 1)
            {
                if (tiles[posx][posy]->get_type() == "King") return 3;
                else return 2;
            }
            else return 1;
        }
        return 0;

    }
    else if (type == "Queen")
    {
        int arr[26][26] = { 0, };
        int i = x - 1;
        int j = y - 1;
        while (i >= 0 && j >= 0)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i--; j--;
        }
        i = x + 1; j = y + 1;
        while (i < height && j < width)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i++; j++;
        }
        i = x - 1; j = y + 1;
        while (i >= 0 && j < width)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i--; j++;
        }
        i = x + 1; j = y - 1;
        while (i < height && j >= 0)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i++; j--;
        }
        i = x - 1; j = y;
        while (i >= 0)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i--;
        }
        i = x + 1; j = y;
        while (i < height)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i++;
        }
        i = x; j = y - 1;
        while (j >= 0)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            j--;
        }
        i = x; j = y + 1;
        while (j < width)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            j++;
        }

        return arr[posx][posy];
    }
    else if (type == "Rook")
    {
        int arr[26][26] = { 0, };
        int i, j;
        i = x - 1; j = y;
        while (i >= 0)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i--;
        }
        i = x + 1; j = y;
        while (i < height)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i++;
        }
        i = x; j = y - 1;
        while (j >= 0)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            j--;
        }
        i = x; j = y + 1;
        while (j < width)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            j++;
        }
        return arr[posx][posy];
    }
    else if (type == "Bishop")
    {
        int arr[26][26] = {0,};
        int i = x - 1;
        int j = y - 1;
        while (i>=0 && j>=0)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i--; j--;
        }
        i = x + 1; j = y + 1;
        while (i < height && j < width)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    if (tiles[i][j]->get_type() == "King")
                    {
                        arr[i][j] = 3;
                    }
                    else
                    {
                        arr[i][j] = 2;
                    }
                    break;
                }
            }
            i++; j++;
        }

        i = x - 1; j = y + 1;
        while (i >= 0 && j < width)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    arr[i][j] = 2;
                    break;
                }
            }
            i--; j++;
        }

        i = x + 1; j = y - 1;
        while (i <height && j >= 0)
        {
            arr[i][j] = 1;
            if (tiles[i][j]->get_flag() == 1)
            {
                if (tiles[i][j]->get_color() == color)
                {
                    arr[i][j] = 0;
                    break;
                }
                else
                {
                    arr[i][j] = 2;
                    break;
                }
            }
            i++; j--;
        }
        
        return arr[posx][posy];
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
                if (tiles[posx][posy]->get_type() == "King") return 3;
                else return 2;
            }
            else return 1;
        }
        else if ((abs(x - posx) == 1) && (abs(y - posy) == 2))
        {
            if (tiles[posx][posy]->get_flag() == 1)
            {
                if (tiles[posx][posy]->get_type() == "King") return 3;
                else return 2;
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
                    if (tiles[posx][posy]->get_type() == "King") return 3;
                    else return 2;
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
                    if (tiles[posx][posy]->get_type() == "King") return 3;
                    else return 2;
                }
            }
        }
        return 0;
    }
}

int ChessBoard::is_check(string str)
{
    string color, s;
    if (str == "b")
    {
        color = "White";
        s = "Black";
    }
    else
    {
        color = "Black";
        s = "White";
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (tiles[i][j]->get_color() == color && tiles[i][j]->get_flag() == 1)
            {
                for (int x = 0; x < height; x++)
                {
                    for (int y = 0; y < width; y++)
                    {
                        if (possible_move_check(i, j, x, y) == 3)
                        {
                            return 1; // Check
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int ChessBoard::is_checkmate(string str)
{
    string color;
    if (str == "b")
    {
        color = "Black";
    }
    else
    {
        color = "White";
    }

    if (is_check(str) == 1) // is check
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (tiles[i][j]->get_color() == color && tiles[i][j]->get_flag() == 1)
                {
                    // move
                    // is check
                    // is not check -> legal move present -> is not checkmate
                    // there is no legal move -> checkmate
                    
                    for (int x = 0; x < height; x++)
                    {
                        for (int y = 0; y < width; y++)
                        {
                            if (possible_move_check(i, j, x, y) == 1) // move
                            {
                                ChessBoard temp(*this);
                                ChessPiece *temppiece = create_piece(" ", " ", 0, 0, 0);
                                temp.tiles[i][j]->move(x, y); // value change
                                temp.tiles[x][y]->move(i, j); // value change
                                temppiece = temp.tiles[x][y];
                                temp.tiles[x][y] = temp.tiles[i][j];
                                temp.tiles[i][j] = temppiece;
                                if (temp.is_check(str) == 0) return 0;
                            }
                            else if (possible_move_check(i, j, x, y) == 2) // attack
                            {
                                ChessBoard temp(*this);
                                ChessPiece* temppiece = create_piece(" ", " ", 0, 0, 0);
                                temp.tiles[i][j]->move(x, y); // value change
                                temp.tiles[x][y]->move(i, j); // value change
                                temp.tiles[x][y]->set_flag(0); // attacked
                                temppiece = temp.tiles[x][y];
                                temp.tiles[x][y] = temp.tiles[i][j];
                                temp.tiles[i][j] = temppiece;
                                if (temp.is_check(str) == 0) return 0;
                            }
                        }
                    }
                }
            }
        }
        return 1;
    }
    else // is not check -> is not checkmate
    {
        return 0;
    }
}

int ChessBoard::is_checkmate_onemove(string str)
{
    string color, opcolor;
    if (str == "b")
    {
        color = "Black";
        opcolor = "White";
    }
    else
    {
        color = "White";
        opcolor = "Black";
    }


    // possible move check
    // move or attack
    // is check?
    // is checkmate?



    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (tiles[i][j]->get_color() == opcolor && tiles[i][j]->get_flag() == 1)
            {

                for (int x = 0; x < height; x++)
                {
                    for (int y = 0; y < width; y++)
                    {
                        if (possible_move_check(i, j, x, y) == 1) // move
                        {
                            ChessBoard temp(*this);
                            ChessPiece* temppiece = create_piece(" ", " ", 0, 0, 0);
                            temp.tiles[i][j]->move(x, y); // value change
                            temp.tiles[x][y]->move(i, j); // value change
                            temppiece = temp.tiles[x][y];
                            temp.tiles[x][y] = temp.tiles[i][j];
                            temp.tiles[i][j] = temppiece;
                            if (temp.is_checkmate(str) == 1) return 1;
                        }
                        else if (possible_move_check(i, j, x, y) == 2) // attack
                        {
                            ChessBoard temp(*this);
                            ChessPiece* temppiece = create_piece(" ", " ", 0, 0, 0);
                            temp.tiles[i][j]->move(x, y); // value change
                            temp.tiles[x][y]->move(i, j); // value change
                            temp.tiles[x][y]->set_flag(0); // attacked
                            temppiece = temp.tiles[x][y];
                            temp.tiles[x][y] = temp.tiles[i][j];
                            temp.tiles[i][j] = temppiece;
                            if (temp.is_checkmate(str) == 1) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}