#pragma once

#include <board.h>
#include <piece_collection.h>

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
    std::vector<std::shared_ptr<PieceCollection>> pieceCollections;
    std::unordered_set<Board> searchedBoard;
    std::unordered_set<Board> answer;

    void solveHelper(int xStart, int yStart, int depth);
    bool hasDeadSpace(int xStart, int yStart, int width, int height) const;
};
