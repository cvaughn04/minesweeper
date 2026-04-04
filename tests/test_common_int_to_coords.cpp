/*
 * =============================================================================
 * File: tests/test_common_int_to_coords.cpp
 *
 * Abstract:
 *   Date        Description                              Developer
 *   ----------  ---------------------------------------  -----------------
 *   2026-04-04  Common::intToCoords test cases           R. Vaughn
 * =============================================================================
 */

#include <gtest/gtest.h>
#include <common.h>

// B1 - first row, first cell
// position == 1, cols == 5 → {col:1, row:1}
TEST(IntToCoordsTest, FirstRow_FirstCell) {
    auto result = Common::intToCoords(1, 5);
    EXPECT_EQ(result.col, 1);
    EXPECT_EQ(result.row, 1);
}

// B2 - first row, middle cell
// position == 3, cols == 5 → {col:3, row:1}
TEST(IntToCoordsTest, FirstRow_MiddleCell) {
    auto result = Common::intToCoords(3, 5);
    EXPECT_EQ(result.col, 3);
    EXPECT_EQ(result.row, 1);
}

// B3 - first row, last cell (position == cols boundary)
// position == 5, cols == 5 → {col:5, row:1}
TEST(IntToCoordsTest, FirstRow_LastCell) {
    auto result = Common::intToCoords(5, 5);
    EXPECT_EQ(result.col, 5);
    EXPECT_EQ(result.row, 1);
}

// B4 - exact column boundary on a later row
// position == 10, cols == 5 → position % cols == 0 → {col:5, row:2}
TEST(IntToCoordsTest, ExactColumnBoundary) {
    auto result = Common::intToCoords(10, 5);
    EXPECT_EQ(result.col, 5);
    EXPECT_EQ(result.row, 2);
}

// B5 - mid-row cell (not first row, not column boundary)
// position == 7, cols == 5 → 7 % 5 == 2, 7 / 5 + 1 == 2 → {col:2, row:2}
TEST(IntToCoordsTest, MidRowCell) {
    auto result = Common::intToCoords(7, 5);
    EXPECT_EQ(result.col, 2);
    EXPECT_EQ(result.row, 2);
}
