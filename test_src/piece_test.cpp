#include <gtest/gtest.h>
#include <piece.h>

#include <vector>
#include <memory>

TEST(PieceTest, rotate)
{
    std::vector<char> body = {'a'};
    auto piece = std::make_shared<Piece>(1, 1, body);
    piece->rotate();
    EXPECT_EQ(1, piece->WIDTH);
    EXPECT_EQ(1, piece->HEIGHT);
    EXPECT_EQ('a', piece->getVal(0, 0));

    body = {'b',
            'b',
            'b'};
    piece = std::make_shared<Piece>(1, 3, body);
    piece->rotate();
    EXPECT_EQ(3, piece->WIDTH);
    EXPECT_EQ(1, piece->HEIGHT);
    EXPECT_EQ('b', piece->getVal(0, 0));
    EXPECT_EQ('b', piece->getVal(1, 0));
    EXPECT_EQ('b', piece->getVal(2, 0));

    body = {' ', 'c', ' ',
            'c', 'c', 'c'};
    piece = std::make_shared<Piece>(3, 2, body);
    piece->rotate();
    EXPECT_EQ('c', piece->getVal(0, 0));
    EXPECT_EQ(' ', piece->getVal(1, 0));
    EXPECT_EQ('c', piece->getVal(0, 1));
    EXPECT_EQ('c', piece->getVal(1, 1));
    EXPECT_EQ('c', piece->getVal(0, 2));
    EXPECT_EQ(' ', piece->getVal(1, 2));
}

TEST(PieceTest, reflect)
{
    std::vector<char> body = {'a'};
    auto piece = std::make_shared<Piece>(1, 1, body);
    piece->reflect();
    EXPECT_EQ(1, piece->WIDTH);
    EXPECT_EQ(1, piece->HEIGHT);
    EXPECT_EQ('a', piece->getVal(0, 0));

    body = {' ', 'b', 'b'};
    piece = std::make_shared<Piece>(3, 1, body);
    piece->reflect();
    EXPECT_EQ(3, piece->WIDTH);
    EXPECT_EQ(1, piece->HEIGHT);
    EXPECT_EQ('b', piece->getVal(0, 0));
    EXPECT_EQ('b', piece->getVal(1, 0));
    EXPECT_EQ(' ', piece->getVal(2, 0));

    body = {'c', 'c', ' ',
            ' ', 'c', 'c'};
    piece = std::make_shared<Piece>(3, 2, body);
    piece->reflect();
    EXPECT_EQ(' ', piece->getVal(0, 0));
    EXPECT_EQ('c', piece->getVal(1, 0));
    EXPECT_EQ('c', piece->getVal(2, 0));
    EXPECT_EQ('c', piece->getVal(0, 1));
    EXPECT_EQ('c', piece->getVal(1, 1));
    EXPECT_EQ(' ', piece->getVal(2, 1));
}