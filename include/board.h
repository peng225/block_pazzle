#pragma once

#include <piece.h>

#include <vector>

class Board : public Piece {
public:
    Board(int width, int height);
    bool put(int x, int y, const Piece& piece);
    bool undo(int x, int y, const Piece& piece);
    bool isFull() const;
    bool operator==(const Board &obj) const;
    bool operator!=(const Board &obj) const;
    std::size_t getHash() const;

private:
    bool canPut(int x, int y, const Piece& piece) const;
    bool checkEqual(const Board &cmpObj) const;
    bool mirrorEqual(const Board &cmpObj) const;
    bool rotate180Equal(const Board &cmpObj) const;
    bool mirrornAndrotate180Equal(const Board &cmpObj) const;
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