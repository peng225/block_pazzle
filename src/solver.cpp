#include <solver.h>

#include <vector>
#include <iostream>

Solver::Solver(int width, int height) : board(std::make_shared<Board>(width, height)) {
}

void Solver::addPiece(std::shared_ptr<Piece> piece)
{
    std::cout << "add a piece:" << std::endl;
    piece->print();
    auto pieceCollection = std::make_shared<PieceCollection>(piece);
    pieceCollections.push_back(pieceCollection);
}

void Solver::solve(){
    solveHelper(0, 0);
}

void Solver::solveHelper(int xStart, int yStart)
{
    if (searchedBoard.contains(*board)) {
        // std::cout << "skip" << std::endl;
        return;
    }
    searchedBoard.emplace(*board);
    if (board->isFull())
    {
        std::cout << "SOLVED!" << std::endl;
        board->print();
        return;
    }

    for (auto pieceCollectionItr = std::begin(pieceCollections);
            pieceCollectionItr != std::end(pieceCollections); pieceCollectionItr++)
    {
        while(!(*pieceCollectionItr)->isEnd()) {
            auto piece = (*pieceCollectionItr)->next();
            // std::cout << "current piece" << std::endl;
            // piece->print();
            for (int y = yStart; y < board->HEIGHT; y++)
            {
                bool isPut = false;
                for (int x = (y == yStart ? xStart : 0); x < board->WIDTH; x++)
                {
                    // std::cout << "X, y = " << x << ", " << y << std::endl;
                    if (!board->put(x, y, piece))
                    {
                        // std::cout << "cannot put" << std::endl;
                        continue;
                    }
                    // std::cout << "can put" << std::endl;
                    auto tmpPieceCollectionPtr = *pieceCollectionItr;
                    pieceCollectionItr = pieceCollections.erase(pieceCollectionItr);
                    // std::cout << "print before next helper call" << std::endl;
                    // board->print();
                    solveHelper(x, y);
                    if (!board->undo(x, y, piece)) {
                        std::cerr << "undo failed." << std::endl;
                        board->print();
                        piece->print();
                        return;
                    }
                    pieceCollectionItr = pieceCollections.insert(pieceCollectionItr, tmpPieceCollectionPtr);
                    // std::cout << "print after helper call and recover" << std::endl;
                    // board->print();
                    isPut = true;
                    break;
                }
                if (isPut) {
                    break;
                }
            }
        }
        (*pieceCollectionItr)->reset();
    }
}
