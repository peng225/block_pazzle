#pragma once

#include <board.h>

#include <vector>
#include <unordered_set>
#include <memory>

class Solver {
public:
    Solver(int width, int height);
    void solve();
    void addPiece(std::shared_ptr<Piece> piece);

private:
    std::shared_ptr<Board> board;
    std::vector<std::shared_ptr<Piece>> pieces;
    std::unordered_set<Board> searchedBoard;

    void solveHelper(int xStart, int yStart);
};
