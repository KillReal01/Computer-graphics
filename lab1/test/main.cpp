#include "../src/matrix.h"
#include <gtest/gtest.h>

TEST(Matrix, test_sum) {
    Matrix<int> a({
            {1, 2},
            {3, 4}
    });
    Matrix<int> b({
            {5, 6},
            {7, 8}
    });
    Matrix<int> expected_res({
            {6, 8},
            {10, 12}
    });

    const auto res = a + b;

    EXPECT_EQ(res, expected_res);
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
