/*
 * =============================================================================
 * File: tests/test_field_is_flag.cpp
 *
 * Abstract:
 *   Date        Description                                      Developer
 *   ----------  -----------------------------------------------  -----------------
 *   2026-03-31  Add Field::isFlag test                            C. Vaughn
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


TEST(isFlag, Corner_flag_is_flag)
{
    Field field = makeField(3, 3);
    
    Common::CoordsStruct at{1, 1};
    field.field2DVector[at.col][at.row] = Symbols::getSymbol("symbolFlag");

    auto result = field.isFlag(at);

    EXPECT_TRUE(result);
}

TEST(isFlag, Corner_covered_not_flag)
{
    Field field = makeField(3, 3);
    
    Common::CoordsStruct at{1, 1};
    field.field2DVector[at.col][at.row] = Symbols::getSymbol("symbolCovered");

    auto result = field.isFlag(at);

    EXPECT_FALSE(result);
}

TEST(isFlag, Edge_flag_is_flag)
{
    Field field = makeField(3, 3);
    
    Common::CoordsStruct at{1, 2};
    field.field2DVector[at.col][at.row] = Symbols::getSymbol("symbolFlag");

    auto result = field.isFlag(at);

    EXPECT_TRUE(result);
}


TEST(isFlag, Edge_covered_not_flag)
{
    Field field = makeField(3, 3);
    
    Common::CoordsStruct at{1, 2};
    field.field2DVector[at.col][at.row] = Symbols::getSymbol("symbolCovered");

    auto result = field.isFlag(at);

    EXPECT_FALSE(result);
}

TEST(isFlag, Middle_flag_is_flag)
{
    Field field = makeField(3, 3);
    
    Common::CoordsStruct at{2, 2};
    field.field2DVector[at.col][at.row] = Symbols::getSymbol("symbolFlag");

    auto result = field.isFlag(at);

    EXPECT_TRUE(result);
}


TEST(isFlag, Middle_covered_not_flag)
{
    Field field = makeField(3, 3);
    
    Common::CoordsStruct at{2, 2};
    field.field2DVector[at.col][at.row] = Symbols::getSymbol("symbolCovered");

    auto result = field.isFlag(at);

    EXPECT_FALSE(result);
}