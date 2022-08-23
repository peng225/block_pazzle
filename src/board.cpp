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

bool Board::checkEqual(const Board &cmpObj) const
{
    // Direct compare
    if (body == cmpObj.body)
    {
        return true;
    }

    // mirror compare
    if (mirrorEqual(cmpObj))
    {
        return true;
    }

    // 180 deg rotate compare
    if (rotate180Equal(cmpObj))
    {
        return true;
    }

    // mirror and 180 deg rotate compare
    if (mirrornAndrotate180Equal(cmpObj))
    {
        return true;
    }

    return false;
}

bool Board::operator==(const Board &obj) const
{
    const Board* objPtr = &obj;
    if (WIDTH == obj.WIDTH && HEIGHT == obj.HEIGHT) {
        return checkEqual(*objPtr);
    }
    if (WIDTH == obj.HEIGHT && HEIGHT == obj.WIDTH) {
        auto tmpObj = obj;
        tmpObj.rotate();
        objPtr = &tmpObj;
        return checkEqual(*objPtr);
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

bool Board::rotate180Equal(const Board &cmpObj) const {
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (getVal(x, y) != cmpObj.getVal(WIDTH - 1 - x, HEIGHT - 1 - y))
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::mirrornAndrotate180Equal(const Board &cmpObj) const {
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (getVal(x, y) != cmpObj.getVal(x, HEIGHT - 1 - y))
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

std::size_t Board::getHash() const
{
    std::size_t hashVal = 1;

    // Top edge
    std::size_t tmpHashVal = 0;
    for (int i = 0; i < WIDTH; i++)
    {
        tmpHashVal += getVal(i, 0);
    }
    hashVal *= tmpHashVal;

    tmpHashVal = 0;
    for (int i = 1; i < WIDTH-1; i++)
    {
        tmpHashVal += getVal(i, 1);
    }
    hashVal *= tmpHashVal;

    // Bottom edge
    tmpHashVal = 0;
    for (int i = 0; i < WIDTH; i++)
    {
        tmpHashVal += getVal(i, HEIGHT - 1);
    }
    hashVal *= tmpHashVal;

    tmpHashVal = 0;
    for (int i = 1; i < WIDTH - 1; i++)
    {
        tmpHashVal += getVal(i, HEIGHT-2);
    }
    hashVal *= tmpHashVal;

    // Left edge
    tmpHashVal = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        tmpHashVal += getVal(0, i);
    }
    hashVal *= tmpHashVal;

    tmpHashVal = 0;
    for (int i = 1; i < HEIGHT - 1; i++)
    {
        tmpHashVal += getVal(1, i);
    }
    hashVal *= tmpHashVal;

    // Right edge
    tmpHashVal = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        tmpHashVal += getVal(WIDTH-1, i);
    }
    hashVal *= tmpHashVal;

    tmpHashVal = 0;
    for (int i = 1; i < HEIGHT - 1; i++)
    {
        tmpHashVal += getVal(WIDTH-2, i);
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