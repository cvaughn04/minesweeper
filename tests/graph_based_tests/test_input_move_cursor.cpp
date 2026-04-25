/*
 * =============================================================================
 * File: tests/test_input_move_cursor.cpp
 *
 * Abstract:
 *   Date        Description                                      Developer
 *   ----------  -----------------------------------------------  -----------------
 *   2026-04-03  Add Input::moveCursor tests                       C. Vaughn
 * =============================================================================
 */

#include <gtest/gtest.h>

// Pre-include every standard header that the project headers pull in so that
// those headers are already compiled (and their include-guards set) before the
// #define below takes effect.
#include <string>
#include <random>

// Expose private members so the test can call moveCursor directly and
// reference Input::Direction without a friend declaration in the source.
#define private public
#include <common.h>
#include <field.h>
#include <input.h>
#undef private

namespace
{
    Field makeField(int cols, int rows)
    {
        Common::GameModeReturnStruct mode;
        mode.difficultyString = "Test";
        mode.cols             = cols;
        mode.rows             = rows;
        mode.mines            = 0;
        mode.cellWidth        = 3;
        mode.offsetX          = 0;
        mode.offsetY          = 0;
        return Field(mode);
    }
}

// ─────────────────────────────────────────────
// Direction::UP
// ─────────────────────────────────────────────

TEST(MoveCursor, Up_Interior_DecrementsRow)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{3, 3};
    bool noJump = false;
    Input::Direction dir = Input::Direction::UP;

    input.moveCursor(field, pos, dir, &noJump);

    EXPECT_EQ(3, pos.col);
    EXPECT_EQ(2, pos.row);
}

TEST(MoveCursor, Up_TopEdge_NoEdgeJump_RowUnchanged)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{3, 1};
    bool noJump = false;
    Input::Direction dir = Input::Direction::UP;

    input.moveCursor(field, pos, dir, &noJump);

    EXPECT_EQ(1, pos.row);
}

TEST(MoveCursor, Up_TopEdge_EdgeJump_WrapsToBottom)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{3, 1};
    bool doJump = true;
    Input::Direction dir = Input::Direction::UP;

    input.moveCursor(field, pos, dir, &doJump);

    EXPECT_EQ(field.getRows(), pos.row);
}

// ─────────────────────────────────────────────
// Direction::DOWN
// ─────────────────────────────────────────────

TEST(MoveCursor, Down_Interior_IncrementsRow)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{3, 3};
    bool noJump = false;
    Input::Direction dir = Input::Direction::DOWN;

    input.moveCursor(field, pos, dir, &noJump);

    EXPECT_EQ(3, pos.col);
    EXPECT_EQ(4, pos.row);
}

TEST(MoveCursor, Down_BottomEdge_NoEdgeJump_RowUnchanged)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{3, 5};
    bool noJump = false;
    Input::Direction dir = Input::Direction::DOWN;

    input.moveCursor(field, pos, dir, &noJump);

    EXPECT_EQ(field.getRows(), pos.row);
}

TEST(MoveCursor, Down_BottomEdge_EdgeJump_WrapsToTop)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{3, 5};
    bool doJump = true;
    Input::Direction dir = Input::Direction::DOWN;

    input.moveCursor(field, pos, dir, &doJump);

    EXPECT_EQ(1, pos.row);
}

// ─────────────────────────────────────────────
// Direction::LEFT
// ─────────────────────────────────────────────

TEST(MoveCursor, Left_Interior_DecrementsCol)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{3, 3};
    bool noJump = false;
    Input::Direction dir = Input::Direction::LEFT;

    input.moveCursor(field, pos, dir, &noJump);

    EXPECT_EQ(2, pos.col);
    EXPECT_EQ(3, pos.row);
}

TEST(MoveCursor, Left_LeftEdge_NoEdgeJump_ColUnchanged)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{1, 3};
    bool noJump = false;
    Input::Direction dir = Input::Direction::LEFT;

    input.moveCursor(field, pos, dir, &noJump);

    EXPECT_EQ(1, pos.col);
}

TEST(MoveCursor, Left_LeftEdge_EdgeJump_WrapsToRight)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{1, 3};
    bool doJump = true;
    Input::Direction dir = Input::Direction::LEFT;

    input.moveCursor(field, pos, dir, &doJump);

    EXPECT_EQ(field.getCols(), pos.col);
}

// ─────────────────────────────────────────────
// Direction::RIGHT
// ─────────────────────────────────────────────

TEST(MoveCursor, Right_Interior_IncrementsCol)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{3, 3};
    bool noJump = false;
    Input::Direction dir = Input::Direction::RIGHT;

    input.moveCursor(field, pos, dir, &noJump);

    EXPECT_EQ(4, pos.col);
    EXPECT_EQ(3, pos.row);
}

TEST(MoveCursor, Right_RightEdge_NoEdgeJump_ColUnchanged)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{5, 3};
    bool noJump = false;
    Input::Direction dir = Input::Direction::RIGHT;

    input.moveCursor(field, pos, dir, &noJump);

    EXPECT_EQ(field.getCols(), pos.col);
}

TEST(MoveCursor, Right_RightEdge_EdgeJump_WrapsToLeft)
{
    Field field = makeField(5, 5);
    Input input;
    Common::CoordsStruct pos{5, 3};
    bool doJump = true;
    Input::Direction dir = Input::Direction::RIGHT;

    input.moveCursor(field, pos, dir, &doJump);

    EXPECT_EQ(1, pos.col);
}
