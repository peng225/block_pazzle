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
    for (int i = 0; i < 8; i++)
    {
        switch (i)
        {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
            copiedObj.rotate();
            break;
        case 4:
            copiedObj.reflect();
            break;
        }
        if (WIDTH == copiedObj.WIDTH && HEIGHT == copiedObj.HEIGHT &&
            body == copiedObj.body) {
            return true;
        }
    }
    return false;
}

bool Board::operator!=(const Board &obj) const {
    return !(*this == obj);
}

std::size_t Board::getHash() const {
    std::size_t hashVal = 0;
    for(const auto val : body) {
        hashVal += static_cast<size_t>(val) - static_cast<size_t>(' ');
    }
    hashVal += WIDTH;
    hashVal += HEIGHT;
    return hashVal;
}

void Board::setVal(int x, int y, char val)
{
    body.at(x + y * WIDTH) = val;
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