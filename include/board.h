#pragma once

#include <piece.h>

#include <vector>
#include <memory>

class Board : public Piece {
public:
    Board(int width, int height);
    bool put(int x, int y, const std::shared_ptr<Piece> piece);
    bool undo(int x, int y, const std::shared_ptr<Piece> piece);
    bool isFull() const;
    bool operator==(const Board &obj) const;
    bool operator!=(const Board &obj) const;
    std::size_t getHash() const;

private:
    void setVal(int x, int y, char val);
    bool canPut(int x, int y, const std::shared_ptr<Piece> piece) const;
};

namespace std
{
    template <>
    struct hash<Board>
    {
        std::size_t operator()(const Board &key) const
        {
            return key.getHash();
        }
    };
}