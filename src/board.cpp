#include <board.h>

#include <iostream>

Board::Board(int width, int height) {
    WIDTH = width;
    HEIGHT = height;
    body.resize(width * height, ' ');
}

bool Board::put(int x, int y, const std::shared_ptr<Piece> piece)
{
    if(!canPut(x, y, piece)) {
        // std::cout << "put failed" << std::endl;
        return false;
    }

    for (int yOffset = 0; yOffset < piece->HEIGHT; yOffset++)
    {
        for (int xOffset = 0; xOffset < piece->WIDTH; xOffset++)
        {
            auto pieceVal = piece->getVal(xOffset, yOffset);
            if (pieceVal != ' ')
            {
                setVal(x + xOffset, y + yOffset, pieceVal);
            }
        }
    }
    return true;
}

bool Board::undo(int x, int y, const std::shared_ptr<Piece> piece) {
    for (int yOffset = 0; yOffset < piece->HEIGHT; yOffset++)
    {
        for (int xOffset = 0; xOffset < piece->WIDTH; xOffset++)
        {
            auto pieceVal = piece->getVal(xOffset, yOffset);
            if (pieceVal == ' ')
            {
                continue;
            }
            auto boardVal = getVal(x + xOffset, y + yOffset);
            if (pieceVal != boardVal)
            {
                return false;
            }
            setVal(x + xOffset, y + yOffset, ' ');
        }
    }
    return true;
}

bool Board::isFull() const {
    for (auto v : body) {
        if (v == ' ') {
            return false;
        }
    }
    return true;
}

bool Board::operator==(const Board &obj) const {
    auto copiedObj = obj;
    if (
        (WIDTH != obj.WIDTH || HEIGHT != obj.HEIGHT) &&
        (WIDTH != obj.HEIGHT || HEIGHT != obj.WIDTH))
    {
        return false;
    }
    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
            copiedObj.rotate();
            break;
        }
        if (WIDTH != copiedObj.WIDTH || HEIGHT != copiedObj.HEIGHT) {
            continue;
        }
        // Direct compare
        if (body == copiedObj.body) {
            return true;
        }
        // mirror compare
        if(mirrorEqual(copiedObj)) {
            return true;
        }
    }
    return false;
}

bool Board::mirrorEqual(const Board &cmpObj) const
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (getVal(x, y) != cmpObj.getVal(WIDTH - 1 - x, y))
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::operator!=(const Board &obj) const {
    return !(*this == obj);
}

std::size_t Board::getHash() const {
    std::size_t hashVal = 1;

    // Top edge
    std::size_t tmpHashVal = 0;
    for (int i = 0; i < WIDTH; i++)
    {
        tmpHashVal += getVal(i, 0);
    }
    hashVal *= tmpHashVal;

    // Bottom edge
    tmpHashVal = 0;
    for (int i = 0; i < WIDTH; i++)
    {
        tmpHashVal += getVal(i, HEIGHT - 1);
    }
    hashVal *= tmpHashVal;

    // Left edge
    tmpHashVal = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        tmpHashVal += getVal(0, i);
    }
    hashVal *= tmpHashVal;

    // Right edge
    tmpHashVal = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        tmpHashVal += getVal(WIDTH-1, i);
    }
    hashVal *= tmpHashVal;

    hashVal += WIDTH;
    hashVal += HEIGHT;
    return hashVal;
}

bool Board::canPut(int x, int y, const std::shared_ptr<Piece> piece) const {
    // Over all size check.
    if (WIDTH <= x + piece->WIDTH-1 || HEIGHT <= y + piece->HEIGHT-1) {
        // std::cout << "piece out of range." << std::endl;
        return false;
    }
    for (int yOffset = 0; yOffset < piece->HEIGHT; yOffset++)
    {
        for (int xOffset = 0; xOffset < piece->WIDTH; xOffset++)
        {
            auto pieceVal = piece->getVal(xOffset, yOffset);
            auto boardVal = getVal(x + xOffset, y + yOffset);
            if (pieceVal != ' ' && boardVal != ' ') {
                // std::cout << "both not space" << std::endl;
                return false;
            }
        }
    }
    return true;
}