/*
 * =============================================================================
 * File: tests/test_field_find_neighbors.cpp
 *
 * Abstract:
 *   Date        Description                                      Developer
 *   ----------  -----------------------------------------------  -----------------
 *   2026-03-30  Add Field::findNeighbors tests + infeasible path  C. Vaughn
 * =============================================================================
 */

#include <gtest/gtest.h>

#include <common.h>
#include <field.h>
#include <symbols.h>

namespace
{
    Field makeField(int cols, int rows)
    {
        Common::GameModeReturnStruct mode;
        mode.difficultyString = "Test";
        mode.cols = cols;
        mode.rows = rows;
        mode.mines = 0;
        mode.cellWidth = 3;
        mode.offsetX = 0;
        mode.offsetY = 0;
        return Field(mode);
    }

    std::vector<std::vector<stringconv>> makeGrid(int cols, int rows, const stringconv& fill)
    {
        // Match the project's 1-based board indexing convention:
        // vectors are sized (cols+1) x (rows+1) and indices [1..cols][1..rows] are used.
        std::vector<std::vector<stringconv>> grid;
        grid.resize(static_cast<size_t>(cols + 1));
        for (int c = 0; c <= cols; ++c)
        {
            grid[c].resize(static_cast<size_t>(rows + 1), fill);
        }
        return grid;
    }

    bool containsCoord(const std::vector<Common::CoordsStruct>& v, int col, int row)
    {
        for (const auto& c : v)
        {
            if (c.col == col && c.row == row) return true;
        }
        return false;
    }
}

// Feasible tests: "other symbol" branch (corner/edge/middle).
// We intentionally do NOT treat the "symbolNumber" branch as feasible coverage,
// because this project does not define "symbolNumber" or "symbolNumbersArray[i]"
// in Symbols' map. That makes the branch effectively unusable for real gameplay.

TEST(FindNeighbors, Corner_OtherSymbol_FindsMatchingNeighbors)
{
    Field field = makeField(3, 3);
    auto grid = makeGrid(3, 3, Symbols::getSymbol("symbolZero"));

    // For (1,1), the valid neighbors are (2,1), (1,2), (2,2).
    // Mark two of them as covered; leave one as zero.
    grid[2][1] = Symbols::getSymbol("symbolCovered");
    grid[1][2] = Symbols::getSymbol("symbolCovered");
    grid[2][2] = Symbols::getSymbol("symbolZero");

    Common::CoordsStruct at{1, 1};
    auto neighbors = field.findNeighbors(grid, at, Symbols::getSymbol("symbolCovered"));

    EXPECT_EQ(2u, neighbors.size());
    EXPECT_TRUE(containsCoord(neighbors, 2, 1));
    EXPECT_TRUE(containsCoord(neighbors, 1, 2));
}

TEST(FindNeighbors, Edge_OtherSymbol_FindsMatchingNeighbors)
{
    Field field = makeField(3, 3);
    auto grid = makeGrid(3, 3, Symbols::getSymbol("symbolZero"));

    // At (1,2) (left edge, non-corner), valid neighbors are:
    // (1,1), (2,1), (2,2), (2,3), (1,3).
    // Mark a subset as covered.
    grid[1][1] = Symbols::getSymbol("symbolCovered");
    grid[2][2] = Symbols::getSymbol("symbolCovered");
    grid[2][3] = Symbols::getSymbol("symbolCovered");

    Common::CoordsStruct at{1, 2};
    auto neighbors = field.findNeighbors(grid, at, Symbols::getSymbol("symbolCovered"));

    EXPECT_EQ(3u, neighbors.size());
    EXPECT_TRUE(containsCoord(neighbors, 1, 1));
    EXPECT_TRUE(containsCoord(neighbors, 2, 2));
    EXPECT_TRUE(containsCoord(neighbors, 2, 3));
}

TEST(FindNeighbors, Middle_OtherSymbol_FindsMatchingNeighbors)
{
    Field field = makeField(3, 3);
    auto grid = makeGrid(3, 3, Symbols::getSymbol("symbolZero"));

    // Mark three neighbors around the center as covered.
    grid[1][1] = Symbols::getSymbol("symbolCovered");
    grid[3][2] = Symbols::getSymbol("symbolCovered");
    grid[2][3] = Symbols::getSymbol("symbolCovered");

    Common::CoordsStruct at{2, 2};
    auto neighbors = field.findNeighbors(grid, at, Symbols::getSymbol("symbolCovered"));

    EXPECT_EQ(3u, neighbors.size());
    EXPECT_TRUE(containsCoord(neighbors, 1, 1));
    EXPECT_TRUE(containsCoord(neighbors, 3, 2));
    EXPECT_TRUE(containsCoord(neighbors, 2, 3));
}

// Infeasible-path characterization: demonstrate why "symbolNumber" is not a usable input.
// Even if adjacent cells contain numeric strings, this implementation compares them against
// Symbols::getSymbol("symbolNumbersArray[i]") which is not defined anywhere in the project.

TEST(FindNeighbors, SymbolNumberPath_IsInfeasibleInCurrentProject)
{
    Field field = makeField(3, 3);
    auto grid = makeGrid(3, 3, Symbols::getSymbol("symbolCovered"));

    // Put number strings around (2,2).
    grid[1][1] = Common::intToStringConv(1);
    grid[2][1] = Common::intToStringConv(2);
    grid[3][1] = Common::intToStringConv(3);
    grid[3][2] = Common::intToStringConv(4);
    grid[3][3] = Common::intToStringConv(5);
    grid[2][3] = Common::intToStringConv(6);
    grid[1][3] = Common::intToStringConv(7);
    grid[1][2] = Common::intToStringConv(8);

    Common::CoordsStruct at{2, 2};

    // "symbolNumber" is not defined in symbolsMap, but getSymbol uses operator[],
    // so this call returns a default-constructed stringconv (empty string).
    auto symbolNumberSentinel = Symbols::getSymbol("symbolNumber");

    auto neighbors = field.findNeighbors(grid, at, symbolNumberSentinel);

    // Because the neighbor-check compares against Symbols::getSymbol("symbolNumbersArray[i]"),
    // which is also undefined, it will not match the numeric strings placed above.
    EXPECT_EQ(0u, neighbors.size());
}

