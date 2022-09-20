#include "bfprt.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using testing::ElementsAre;

class BfprtUnitTest : public testing::Test {};

TEST_F(BfprtUnitTest, test_insert_sort) {
    std::vector<int> values{5, 3, 2, 4, 1};
    mj::bfprt::detail::inner_sort(values.begin(), values.end());
    EXPECT_THAT(values, ElementsAre(1, 2, 3, 4, 5));

    values = std::vector<int>{2, 1};
    mj::bfprt::detail::inner_sort(values.begin(), values.end());
    EXPECT_THAT(values, ElementsAre(1, 2));
}

TEST_F(BfprtUnitTest, test_insert_sort_for_string) {
    std::string values{"hello"};
    mj::bfprt::detail::inner_sort(values.begin(), values.end());
    EXPECT_EQ(values, "ehllo");
}

TEST_F(BfprtUnitTest, TODO_1) {
    std::string values{"hello"};
    mj::bfprt::nth_element(values.begin(), values.begin() + 2, values.end());
    EXPECT_EQ(values, "ehllo");
}

TEST_F(BfprtUnitTest, TODO_2) {
    std::vector<int> values{};
    for (int i = 0; i < 100; i++) {
        values.emplace_back(1000 - i);
    }
    std::nth_element(values.begin(), values.begin() + 10, values.end());
    EXPECT_THAT(values, ElementsAre(1, 2, 3, 4, 5));
}

TEST_F(BfprtUnitTest, TODO_3) {
    std::vector<int> values{};
    for (int i = 0; i < 100; i++) {
        values.emplace_back(1000 - i);
    }
    mj::bfprt::nth_element(values.begin(), values.begin() + 10, values.end());
    EXPECT_THAT(values, ElementsAre(1, 2, 3, 4, 5));
}