#include <solver.h>

#include <vector>
#include <iostream>

Solver::Solver(int width, int height) : board(std::make_shared<Board>(width, height)) {
}

void Solver::addPiece(std::shared_ptr<Piece> piece)
{
    std::cout << "add a piece:" << std::endl;
    piece->print();
    pieces.emplace_back(piece);
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

    for (auto pieceItr = std::begin(pieces); pieceItr != std::end(pieces); pieceItr++)
    {
        auto tmpPiece = std::make_shared<Piece>(0, 0, std::vector<char>(0));
        for(int i = 0; i < 8; i++)
        {
            // std::cout << "i == " << i << std::endl;
            switch (i)
            {
            case 0:
                *tmpPiece = **pieceItr;
                break;
            case 1:
            case 2:
            case 3:
            case 5:
            case 6:
            case 7:
                (*pieceItr)->rotate();
                *tmpPiece = *(*pieceItr);
                break;
            case 4:
                (*pieceItr)->reflect();
                *tmpPiece = *(*pieceItr);
                break;
            }
            // std::cout << "current piece" << std::endl;
            // tmpPiece->print();
            for (int y = yStart; y < board->HEIGHT; y++)
            {
                bool isPut = false;
                for (int x = (y == yStart ? xStart : 0); x < board->WIDTH; x++)
                {
                    // std::cout << "X, y = " << x << ", " << y << std::endl;
                    if (!board->put(x, y, tmpPiece))
                    {
                        // std::cout << "cannot put" << std::endl;
                        continue;
                    }
                    // std::cout << "can put" << std::endl;
                    pieceItr = pieces.erase(pieceItr);
                    // std::cout << "print before next helper call" << std::endl;
                    // board->print();
                    solveHelper(x, y);
                    if (!board->undo(x, y, tmpPiece)) {
                        std::cerr << "undo failed." << std::endl;
                        board->print();
                        tmpPiece->print();
                        return;
                    }
                    pieceItr = pieces.insert(pieceItr, tmpPiece);
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
    }
}
