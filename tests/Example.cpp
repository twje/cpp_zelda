#include <gtest/gtest.h>

TEST(ExampleTests, GridCoordToIndex)
{
    size_t rows = 20;
    size_t cols = 20;
    size_t count = 0;

    for (size_t y = 0; y < rows; y++)
    {
        for (size_t x = 0; x < cols; x++)
        {
            size_t index = x + (y * cols);
            EXPECT_EQ(index, count);
            count += 1;
        }
    }
}
