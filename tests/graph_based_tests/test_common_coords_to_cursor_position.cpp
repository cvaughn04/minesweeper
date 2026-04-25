/*
 * =============================================================================
 * File: tests/test_common_coords_to_cursor_position.cpp
 *
 * Abstract:
 *   Date        Description                              Developer
 *   ----------  ---------------------------------------  -----------------
 *   2026-04-04  Common::coordsToCursorPosition tests     R. Vaughn
 *
 * Note: coordsToCursorPosition converts a field (col, row) into a terminal
 * cursor position given an offset and cell width.
 *
 * With cellWidth=3:
 *   cursor.col = offsetX + (col - 1) * 4      (each cell occupies 4 columns)
 *   cursor.row = offsetY + (row - 1) * 2      (each cell occupies 2 rows)
 *
 * Tests use offsetX=4, offsetY=4, cellWidth=3 (standard game defaults from
 * test_helpers.h).
 * =============================================================================
 */

#include <gtest/gtest.h>
#include <common.h>

// Top-left cell — no loop iterations, result is purely the offsets
TEST(CoordsToCursorPositionTest, TopLeftCell) {
    Common::CoordsStruct coords{1, 1};
    auto result = Common::coordsToCursorPosition(coords, 4, 4, 3);
    EXPECT_EQ(result.col, 4);
    EXPECT_EQ(result.row, 4);
}

// Move one column right — col advances by cellWidth+1 == 4
TEST(CoordsToCursorPositionTest, SecondColumn_FirstRow) {
    Common::CoordsStruct coords{2, 1};
    auto result = Common::coordsToCursorPosition(coords, 4, 4, 3);
    EXPECT_EQ(result.col, 8);
    EXPECT_EQ(result.row, 4);
}

// Move one row down — row advances by 2
TEST(CoordsToCursorPositionTest, FirstColumn_SecondRow) {
    Common::CoordsStruct coords{1, 2};
    auto result = Common::coordsToCursorPosition(coords, 4, 4, 3);
    EXPECT_EQ(result.col, 4);
    EXPECT_EQ(result.row, 6);
}

// Both axes — verifies col and row step independently
TEST(CoordsToCursorPositionTest, ThirdColumn_ThirdRow) {
    // col: 4 + 2*4 = 12   row: 4 + 2*2 = 8
    Common::CoordsStruct coords{3, 3};
    auto result = Common::coordsToCursorPosition(coords, 4, 4, 3);
    EXPECT_EQ(result.col, 12);
    EXPECT_EQ(result.row, 8);
}

// Different offsets — confirms offset is applied as a base, not hard-coded
TEST(CoordsToCursorPositionTest, OffsetIsRespected) {
    Common::CoordsStruct coords{1, 1};
    auto result = Common::coordsToCursorPosition(coords, 10, 6, 3);
    EXPECT_EQ(result.col, 10);
    EXPECT_EQ(result.row, 6);
}

// cellWidth=5 — (cellWidth-1)/2 == 2, so each column step is 2+1+2+1 == 6
TEST(CoordsToCursorPositionTest, WiderCellWidth) {
    // col: offsetX + (5-1)/2 - 1 = 4+2-1 = 5; second col adds 6 → 11
    Common::CoordsStruct coords{2, 1};
    auto result = Common::coordsToCursorPosition(coords, 4, 4, 5);
    EXPECT_EQ(result.col, 11);
    EXPECT_EQ(result.row, 4);
}
