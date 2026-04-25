/*
 * =============================================================================
 * File: tests/test_field_create_2D_Vector.cpp
 *
 * Abstract:
 *   Date        Description                              Developer
 *   ----------  ---------------------------------------  -----------------
 *   2026-04-03  Field::create2DVector test cases         N. Schweikhart
 *
 * Note: create2DVector is private and called only by the constructor.
 * The "field" branch is verified via getCoordsContent() after construction.
 * The "mines" branch has no public getter — it is verified indirectly by
 * confirming the first click is never a mine (fillMines reads mines2DVector).
 * The invalid-string branch is untestable through the public interface since
 * the constructor only ever passes "field" or "mines".
 * =============================================================================
 */

#include <gtest/gtest.h>
#include <common.h>
#include <field.h>
#include <symbols.h>

#include "../test_helpers.h"

// P1 - "field" branch: after construction every cell should be symbolCovered
TEST(Create2DVectorTest, FieldType_AllCellsCovered) {
    auto gm = makegameMode(3, 3, 1);
    Field field(gm);
    for (int col = 1; col <= 3; ++col)
    {
        for (int row = 1; row <= 3; ++row)
        {
            Common::CoordsStruct coords{col, row};
            EXPECT_EQ(field.getCoordsContent(coords), Symbols::getSymbol("symbolCovered"))
                << "Failed at col=" << col << " row=" << row;
        }
    }
}

// P2 - "mines" branch: verified indirectly — if mines2DVector was initialized
// correctly with symbolZero, then fillMines can safely place mines without
// false positives. We confirm by checking the first click is never fatal.
TEST(Create2DVectorTest, MinesType_FirstClickAlwaysSafe) {
    auto gm = makegameMode(3, 3, 1);
    Field field(gm);
    Common::UserInputReturnStruct userInput;
    userInput.coords     = {2, 2};
    userInput.isFlag     = false;
    userInput.isAutoFlag = false;
    int turn = 1;
    auto result = field.placeUserInput(userInput, turn);
    // first click must never hit a mine — proves mines2DVector was clean at start
    EXPECT_FALSE(result.hasLost);
}

// P3 - invalid branch: untestable through public interface.
// The constructor only calls create2DVector("field") and create2DVector("mines").
// There is no public method that passes an arbitrary string to create2DVector.
// This path can only be reached by calling the private method directly,
// which would require modifying field.h — not appropriate for production code.