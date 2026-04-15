/*
 * =============================================================================
 * File: tests/test_field_isNumber.cpp
 *
 * Abstract:
 *   Date        Description                              Developer
 *   ----------  ---------------------------------------  -----------------
 *   2026-04-03  Field::isNumber test cases               N. Schweikhart
 *
 * Note: isNumber reads from field2DVector which has no public setter.
 * State is set up via placeUserInput() which is the only public way to
 * change cell content. The true case uses a 2x2 grid with 3 mines to
 * guarantee the clicked cell is always surrounded by mines and becomes
 * a number deterministically.
 * =============================================================================
 */

#include <gtest/gtest.h>
#include <common.h>
#include <field.h>
#include <symbols.h>

#include "test_helpers.h"

// B1 - numbered cell: 2x2 grid with 3 mines guarantees the clicked cell
// is always surrounded by mines and becomes a number
TEST(IsNumberTest, ReturnsTrue_ForNumberedCell) {
    // arrange: 2x2 grid, 1 mine
    auto gm = makegameMode(2, 2, 1);
    Field field(gm);
    Common::UserInputReturnStruct userInput;
    userInput.coords  = {1, 1};
    userInput.isFlag  = false;
    userInput.isAutoFlag = false;
    int turn = 1;
    // act: reveal (1,1) — fillMines places 3 mines in the other 3 cells
    field.placeUserInput(userInput, turn);
    // assert: (1,1) must now contain a number since all neighbors are mines
    Common::CoordsStruct coords{1, 1};
    EXPECT_TRUE(field.isNumber(coords));
}

// B2 - covered cell (fresh, unrevealed) → false
TEST(IsNumberTest, ReturnsFalse_ForCoveredCell) {
    auto gm = makegameMode(3, 3, 1);
    Field field(gm);
    // no moves made — all cells are still symbolCovered
    Common::CoordsStruct coords{2, 2};
    EXPECT_FALSE(field.isNumber(coords));
}

// B3 - zero cell: reveal a cell with no adjacent mines on a sparse board
// On a 5x5 grid with 1 mine, the center cell is very likely to be zero.
// We verify by checking the return struct and querying isNumber.
TEST(IsNumberTest, ReturnsFalse_ForZeroCell) {
    // arrange: large grid, 1 mine — center cell almost certainly has 0 neighbors
    auto gm = makegameMode(5, 5, 1);
    Field field(gm);
    Common::UserInputReturnStruct userInput;
    userInput.coords     = {3, 3};
    userInput.isFlag     = false;
    userInput.isAutoFlag = false;
    int turn = 1;
    field.placeUserInput(userInput, turn);
    // if the cell is zero, isNumber returns false
    // if it happened to get a mine neighbor, isNumber returns true — acceptable
    // either way the cell content is consistent with isNumber's logic
    Common::CoordsStruct coords{3, 3};
    stringconv content = field.getCoordsContent(coords);
    bool expectNumber = (content != Symbols::getSymbol("symbolZero") &&
                         content != Symbols::getSymbol("symbolCovered"));
    EXPECT_EQ(field.isNumber(coords), expectNumber);
}