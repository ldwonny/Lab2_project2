#pragma once
/*
 * board.h
 */
#ifndef CHESSPIECE_H_
#define CHESSPIECE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cctype>

#include "utils.h"

using namespace std;


// NOTE: DO NOT CHANGE `Chesspiece` CLASS EXCEPT THE RETURN TYPE OF `get_possible_moves()`
class ChessPiece
{
public:
    ChessPiece(string, string, int, int, int = 0); // default flag 0 is empty tile.
    ChessPiece(const ChessPiece& other);

    friend ostream& operator<<(ostream& os, const ChessPiece& piece);

    string get_color() { return color; }
    string get_type() { return type; }

    int get_x() { return x; }
    int get_y() { return y; }
    int get_flag() { return flag; }

    void set_x(int x) { this->x = x; }
    void set_y(int y) { this->y = y; }
    void set_flag(int flag) { this->flag = flag; }

    virtual void move(int x, int y) { this->x = x; this->y = y; }; // you need to define move function in each pieces such as king class.

    // NOTE: YOU CAN MODIFY THE RETURN TYPE OF THE FUNCTION BELOW
    //virtual vector<tuple<MoveType, Direction, int>> get_possible_moves() = 0; // you need to define this function in each pieces.

protected:
    string color;
    string type;
    int x;
    int y;
    int flag;
};

ChessPiece* create_piece(string color, string type, int x, int y, int flag = 0);

// NOTE: INHERIT ChessPiece CLASS AND IMPLEMENT CLASSES
// NOTE: FILL FREE TO ADD ANY MEMBER VARIABLES OR FUNCTIONS

class King : public ChessPiece
{
    // upright, upleft, downright, downleft, rightup, rightdown, leftup, leftdown
    // TODO
    void move(int x, int y)
    {
        this->x += x;
        this->y += y;
    }
};

class Queen : public ChessPiece
{
    // TODO
    void move(int x, int y)
    {
        this->x += x;
        this->y += y;
    }
};

class Rook : public ChessPiece
{
    // TODO
    void move(int x, int y)
    {
        this->x += x;
        this->y += y;
    }
};

class Bishop : public ChessPiece
{
    // TODO
    void move(int x, int y)
    {
        this->x += x;
        this->y += y;
    }
};

class Knight : public ChessPiece
{
    // TODO
    void move(int x, int y)
    {
        this->x += x;
        this->y += y;
    }
};

class Pawn : public ChessPiece
{
    // TODO
public:
    Pawn(string color, int x, int y, int flag) : ChessPiece(color, "Pawn", x, y, flag)
    { /* Pawn constructor */ }
    void move(int x, int y /* x, y is location of pawn*/)
    {
        /*
        if (color == "Black")
        {
            this->x += direction_to_pair[DOWN].first;
            this->y += direction_to_pair[DOWN].second;
        }
        else
        {
            this->x += direction_to_pair[UP].first;
            this->y += direction_to_pair[UP].second;
        }
        */
        this->x = x;
        this->y = y;
    }

    // Black pawn move down
    // White pawn move up
};

// NOTE: YOU CAN ADD OTHER FUNCTIONS HERE

#endif /* CHESSPIECE_H_ */