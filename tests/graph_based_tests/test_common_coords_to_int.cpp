/*
 * =============================================================================
 * File: tests/test_common_coords_to_int.cpp
 *
 * Abstract:
 *   Date        Description                              Developer
 *   ----------  ---------------------------------------  -----------------
 *   2026-04-04  Common::coordsToInt test cases           R. Vaughn
 *
 * Note: coordsToInt is the inverse of intToCoords.
 *   row == 1  → return coords.col
 *   row  > 1  → return cols * (row - 1) + col
 * =============================================================================
 */

#include <gtest/gtest.h>
#include <common.h>

// First row — result is simply coords.col regardless of cols
TEST(CoordsToIntTest, FirstRow_FirstCell) {
    Common::CoordsStruct c{1, 1};
    EXPECT_EQ(Common::coordsToInt(c, 5), 1);
}

TEST(CoordsToIntTest, FirstRow_MiddleCell) {
    Common::CoordsStruct c{3, 1};
    EXPECT_EQ(Common::coordsToInt(c, 5), 3);
}

TEST(CoordsToIntTest, FirstRow_LastCell) {
    Common::CoordsStruct c{5, 1};
    EXPECT_EQ(Common::coordsToInt(c, 5), 5);
}

// Later rows — formula: cols * (row - 1) + col
TEST(CoordsToIntTest, LaterRow_MidCell) {
    // cols=5, row=2, col=2 → 5*(2-1)+2 = 7
    Common::CoordsStruct c{2, 2};
    EXPECT_EQ(Common::coordsToInt(c, 5), 7);
}

TEST(CoordsToIntTest, LaterRow_LastCellOfRow) {
    // cols=5, row=3, col=5 → 5*(3-1)+5 = 15
    Common::CoordsStruct c{5, 3};
    EXPECT_EQ(Common::coordsToInt(c, 5), 15);
}

// Inverse property: intToCoords(coordsToInt(c, cols), cols) == c
TEST(CoordsToIntTest, InverseOfIntToCoords_FirstRow) {
    Common::CoordsStruct c{4, 1};
    int pos = Common::coordsToInt(c, 5);
    auto roundtrip = Common::intToCoords(pos, 5);
    EXPECT_EQ(roundtrip.col, c.col);
    EXPECT_EQ(roundtrip.row, c.row);
}

TEST(CoordsToIntTest, InverseOfIntToCoords_LaterRow) {
    Common::CoordsStruct c{3, 4};
    int pos = Common::coordsToInt(c, 5);
    auto roundtrip = Common::intToCoords(pos, 5);
    EXPECT_EQ(roundtrip.col, c.col);
    EXPECT_EQ(roundtrip.row, c.row);
}
