/*
 * =============================================================================
 * File: tests/test_common.cpp
 *
 * Abstract:
 *   Date        Description                              Developer
 *   ----------  ---------------------------------------  -----------------
 *   2026-03-28  Add GTest CTest integration              R. Vaughn
 * =============================================================================
 */

#include <gtest/gtest.h>
#include <common.h>

// ─────────────────────────────────────────────
// Common::coordsToInt  /  Common::intToCoords
// These two are inverses; test them together and independently.
// ─────────────────────────────────────────────

TEST(CoordsToInt, FirstRow)
{
    // Row 1: result is simply coords.col
    Common::CoordsStruct c;
    c.col = 1; c.row = 1;
    EXPECT_EQ(1, Common::coordsToInt(c, 5));

    c.col = 5; c.row = 1;
    EXPECT_EQ(5, Common::coordsToInt(c, 5));
}
