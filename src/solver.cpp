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
    solveHelper(0, 0, 0);
}

void Solver::solveHelper(int xStart, int yStart, int depth)
{
    if(depth < 8) {
        if (searchedBoard.contains(*board)) {
            // std::cout << "skip" << std::endl;
            return;
        }
        searchedBoard.emplace(*board);
    }
    if (board->isFull())
    {
        if (answer.find(*board) == std::end(answer))
        {
            answer.emplace(*board);
            std::cout << "SOLVED! " << answer.size() << " answer(s) found." << std::endl;
            board->print();
        }
        return;
    }

    for (auto pieceCollectionItr = std::begin(pieceCollections);
            pieceCollectionItr != std::end(pieceCollections); pieceCollectionItr++)
    {
        while(!(*pieceCollectionItr)->isEnd()) {
            auto piece = (*pieceCollectionItr)->next();
            // std::cout << "current piece" << std::endl;
            // piece->print();
            for (int y = yStart; y < board->HEIGHT-piece->HEIGHT+1; y++)
            {
                bool isPut = false;
                for (int x = (y == yStart ? xStart : 0); x < board->WIDTH-piece->WIDTH+1; x++)
                {
                    // std::cout << "X, y = " << x << ", " << y << std::endl;
                    if (!board->put(x, y, *piece))
                    {
                        // std::cout << "cannot put" << std::endl;
                        continue;
                    }
                    if(!hasDeadSpace(x-1, y-1, piece->WIDTH+2, piece->HEIGHT+2)) {
                        // std::cout << "can put" << std::endl;
                        auto tmpPieceCollectionPtr = *pieceCollectionItr;
                        pieceCollectionItr = pieceCollections.erase(pieceCollectionItr);
                        // std::cout << "print before next helper call" << std::endl;
                        // board->print();
                        solveHelper(x, y, depth+1);
                        pieceCollectionItr = pieceCollections.insert(pieceCollectionItr, tmpPieceCollectionPtr);
                        // std::cout << "print after helper call and recover" << std::endl;
                        // board->print();
                    }
                    if (!board->undo(x, y, *piece))
                    {
                        std::cerr << "undo failed." << std::endl;
                        board->print();
                        piece->print();
                        return;
                    }
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

bool Solver::hasDeadSpace(int xStart, int yStart, int width, int height) const
{
    xStart = std::max(0, xStart);
    yStart = std::max(0, yStart);
    width = std::min(board->WIDTH - xStart, width);
    height = std::min(board->HEIGHT - yStart, height);
    for (int y = yStart; y < yStart + height; y++)
    {
        for (int x = xStart; x < xStart + width; x++)
        {
            if(board->getVal(x, y) != ' ') {
                continue;
            }
            if (
                (x == 0 || board->getVal(x - 1, y) != ' ') &&
                (x == board->WIDTH - 1 || board->getVal(x + 1, y) != ' ') &&
                (y == 0 || board->getVal(x, y - 1) != ' ') &&
                (y == board->HEIGHT - 1 || board->getVal(x, y + 1) != ' '))
            {
                return true;
            }
        }
    }
    return false;
}
