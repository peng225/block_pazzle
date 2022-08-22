#pragma once

#include <piece.h>
#include <list>

class PieceCollection {
public:
    PieceCollection(std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> next();
    bool isEnd() const;
    void reset();
    size_t size() const;

private:
    std::list<std::shared_ptr<Piece>>::iterator currentPos;
    std::list<std::shared_ptr<Piece>> pieceCollection;
    void dedup();
};
