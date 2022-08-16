#include <piece.h>

#include <iostream>

Piece::Piece(int width, int height, const std::vector<char> &body) : WIDTH(width), HEIGHT(height), body(body)
{
}

char Piece::getVal(int x, int y) const
{
    return body.at(x + y * WIDTH);
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

void Piece::rotate()
{
    auto rotatedBody = std::vector<char>(WIDTH * HEIGHT);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            rotatedBody.at(HEIGHT - y - 1 + x * HEIGHT) = getVal(x, y);
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
    auto reflectedBody = std::vector<char>(WIDTH * HEIGHT);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            reflectedBody.at(WIDTH - x - 1 + y * WIDTH) = getVal(x, y);
        }
    }
    body.swap(reflectedBody);
}
