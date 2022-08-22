#include <piece_collection.h>

#include <iostream>

PieceCollection::PieceCollection(std::shared_ptr<Piece> piece)
{
    pieceCollection.push_back(piece);

    auto copiedPiece = std::make_shared<Piece>();
    *copiedPiece = *piece;
    for (int i = 0; i < 3; i++)
    {
        copiedPiece->rotate();
        auto tmpPiece = std::make_shared<Piece>();
        *tmpPiece = *copiedPiece;
        pieceCollection.push_back(tmpPiece);
    }
    copiedPiece->reflect();
    auto tmpPiece = std::make_shared<Piece>();
    *tmpPiece = *copiedPiece;
    pieceCollection.push_back(tmpPiece);
    for (int i = 0; i < 3; i++)
    {
        copiedPiece->rotate();
        auto tmpPiece = std::make_shared<Piece>();
        *tmpPiece = *copiedPiece;
        pieceCollection.push_back(tmpPiece);
    }

    dedup();

    reset();
}

std::shared_ptr<Piece> PieceCollection::next()
{
    auto result = *currentPos;
    currentPos++;
    return result;
}

bool PieceCollection::isEnd() const {
    return currentPos == std::end(pieceCollection);
}

void PieceCollection::reset() {
    currentPos = std::begin(pieceCollection);
}

size_t PieceCollection::size() const
{
    return pieceCollection.size();
}

void PieceCollection::dedup() {
    for (auto leftItr = std::begin(pieceCollection); leftItr != std::end(pieceCollection); leftItr++)
    {
        for (auto rightItr = std::next(leftItr); rightItr != std::end(pieceCollection);)
        {
            if (**leftItr == **rightItr)
            {
                rightItr = pieceCollection.erase(rightItr);
                continue;
            }
            rightItr++;
        }
    }
}