#pragma once

#include <vector>
#include <memory>

class Piece {
public:
    int WIDTH, HEIGHT;
    Piece(){}
    Piece(int width, int height, const std::vector<char> &body);
    char getVal(int x, int y) const;
    void print() const;
    void rotate();
    void reflect();
    bool operator==(const Piece &obj) const;
    bool operator!=(const Piece &obj) const;

protected:
    std::vector<char> body;
    void setVal(int x, int y, char val);
};
