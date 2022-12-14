#include <piece.h>

#include <cassert>
#include <iostream>

Piece::Piece(int width, int height, const std::vector<char> &body) : WIDTH(width), HEIGHT(height), body(body)
{
    assert(static_cast<size_t>(WIDTH * HEIGHT) == this->body.size());
}

char Piece::getVal(int x, int y) const
{
    return body[x + y * WIDTH];
}

void Piece::print() const
{
    for (int y = 0; y < HEIGHT; y++)
    {
        std::cout << y << ": ";
        for (int x = 0; x < WIDTH; x++)
        {
            std::cout << getVal(x, y) << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<char> rotatedBody;
void Piece::rotate()
{
    rotatedBody.resize(WIDTH * HEIGHT);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            rotatedBody[HEIGHT - y - 1 + x * HEIGHT] = getVal(x, y);
        }
    }
    // Note that the WIDTH and HEIGHT is swapped.
    auto tmp = HEIGHT;
    HEIGHT = WIDTH;
    WIDTH = tmp;
    body.swap(rotatedBody);
}

void Piece::reflect()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH/2; x++)
        {
            auto tmp = getVal(x, y);
            setVal(x, y, getVal(WIDTH - x - 1, y));
            setVal(WIDTH - x - 1, y, tmp);
        }
    }
}

void Piece::setVal(int x, int y, char val)
{
    body[x + y * WIDTH] = val;
}

bool Piece::operator==(const Piece &obj) const {
    return WIDTH == obj.WIDTH && HEIGHT == obj.HEIGHT && body == obj.body;
}

bool Piece::operator!=(const Piece &obj) const
{
    return !(*this == obj);
}