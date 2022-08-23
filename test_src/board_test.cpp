#include <gtest/gtest.h>
#include <board.h>

TEST(BoardTest, equal)
{
    Board b1(2, 3);
    Board b2(2, 3);
    Board b3(2, 3);
    Board b4(3, 2);
    Board b5(2, 4);

    EXPECT_EQ(b1, b4);
    EXPECT_NE(b1, b5);
    EXPECT_NE(b4, b5);

    auto p1 = std::make_shared<Piece>(2, 2, std::vector<char>{'a', ' ',
                                                              ' ', 'b'});
    auto p2 = std::make_shared<Piece>(1, 2, std::vector<char>{'a',
                                                              'b'});

    b1.put(0, 0, *p1);
    b2.put(0, 0, *p1);
    b3.put(0, 0, *p2);

    EXPECT_EQ(b1, b2);
    EXPECT_NE(b1, b3);
    EXPECT_NE(b2, b3);

    auto b6 = b1;
    b1.reflect();
    EXPECT_EQ(b1, b6);
    b1.rotate();
    EXPECT_EQ(b1, b6);
}

TEST(BoardTest, getHash)
{
    Board b1(4, 3);
    Board b2(4, 3);
    Board b3(4, 3);
    Board b4(3, 4);
    Board b5(2, 4);

    EXPECT_EQ(b1.getHash(), b4.getHash());
    EXPECT_NE(b1.getHash(), b5.getHash());
    EXPECT_NE(b4.getHash(), b5.getHash());

    auto p1 = std::make_shared<Piece>(2, 2, std::vector<char>{'a', ' ',
                                                              ' ', 'b'});
    auto p2 = std::make_shared<Piece>(1, 2, std::vector<char>{'a',
                                                              'b'});

    EXPECT_TRUE(b1.put(0, 0, *p1));
    EXPECT_TRUE(b2.put(0, 0, *p1));
    EXPECT_TRUE(b3.put(0, 0, *p1));
    EXPECT_TRUE(b3.put(0, 1, *p2));

    EXPECT_EQ(b1.getHash(), b2.getHash());
    EXPECT_NE(b1.getHash(), b3.getHash());

    auto b6 = b1;
    b1.reflect();
    EXPECT_EQ(b1.getHash(), b6.getHash());
    b1.rotate();
    EXPECT_EQ(b1.getHash(), b6.getHash());

    b6 = b3;
    b3.reflect();
    EXPECT_EQ(b3.getHash(), b6.getHash());
    b3.rotate();
    EXPECT_EQ(b3.getHash(), b6.getHash());
}