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
    // TODO
public:
    King(string color, int x, int y, int flag) : ChessPiece(color, "King", x, y, flag) { /* King constructor */ }
    virtual void move(int x, int y);
};

class Queen : public ChessPiece
{
    // TODO
public:
    Queen(string color, int x, int y, int flag) : ChessPiece(color, "Queen", x, y, flag) { /* Queen constructor */ }
    virtual void move(int x, int y);
};

class Rook : public ChessPiece
{
    // TODO
public:
    Rook(string color, int x, int y, int flag) : ChessPiece(color, "Rook", x, y, flag) { /* Rook constructor */ }
    virtual void move(int x, int y);
};

class Bishop : public ChessPiece
{
    // TODO
public:
    Bishop(string color, int x, int y, int flag) : ChessPiece(color, "Bishop", x, y, flag) { /* Bishop constructor */ }
    virtual void move(int x, int y);
};

class Knight : public ChessPiece
{
    // TODO
public:
    Knight(string color, int x, int y, int flag) : ChessPiece(color, "Knight", x, y, flag) { /* Knight constructor */ }
    virtual void move(int x, int y);
};

class Pawn : public ChessPiece
{
    // TODO
public:
    Pawn(string color, int x, int y, int flag) : ChessPiece(color, "Pawn", x, y, flag) { /* Pawn constructor */ }
    virtual void move(int x, int y);
    virtual vector<tuple<MoveType, Direction, int>> get_possible_moves()
    {
        vector<tuple<MoveType, Direction, int>> v;
        v.push_back(make_tuple(MOVE, UP, 1));
        return v;
    }
};

// NOTE: YOU CAN ADD OTHER FUNCTIONS HERE

#endif /* CHESSPIECE_H_ */