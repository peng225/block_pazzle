#include <gtest/gtest.h>
#include <piece_collection.h>

#include <vector>

TEST(PieceCollectionTest, constructor)
{
    std::vector<char> body = {' ', 'c', ' ',
                              'c', 'c', 'c'};
    auto piece = std::make_shared<Piece>(3, 2, body);

    auto pc = std::make_shared<PieceCollection>(piece);

    EXPECT_EQ(4, pc->size());
    EXPECT_FALSE(pc->isEnd());
}
