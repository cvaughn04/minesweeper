/*
 * =============================================================================
 * File: tests/test_field_fillMines.cpp
 *
 * Abstract:
 *   Date        Description                              Developer
 *   ----------  ---------------------------------------  -----------------
 *   2026-04-03  Field::fillMines test cases              N. Schweikhart
 *
 * Note: fillMines is private and called by placeUserInput on turn 1.
 * Tests verify correct mine count via getMinesLeft() and confirm the
 * first click cell is never a mine via the hasLost return value.
 * mines2DVector has no public getter so direct mine position verification
 * is not possible through the public interface.
 * =============================================================================
 */

#include <gtest/gtest.h>
#include <common.h>
#include <field.h>
#include <symbols.h>

#include "../test_helpers.h"

// B1 - corner cell as first input → must not be a mine
TEST(FillMinesTest, FirstClick_CornerCell_IsNotMine) {
    auto gm = makegameMode(5, 5, 12);
    Field field(gm);
    Common::UserInputReturnStruct userInput;
    userInput.coords     = {1, 1};
    userInput.isFlag     = false;
    userInput.isAutoFlag = false;
    int turn = 1;
    auto result = field.placeUserInput(userInput, turn);
    EXPECT_FALSE(result.hasLost);
}

// B2 - edge (non-corner) cell as first input → must not be a mine
TEST(FillMinesTest, FirstClick_EdgeCell_IsNotMine) {
    auto gm = makegameMode(5, 5, 12);
    Field field(gm);
    Common::UserInputReturnStruct userInput;
    userInput.coords     = {1, 3};
    userInput.isFlag     = false;
    userInput.isAutoFlag = false;
    int turn = 1;
    auto result = field.placeUserInput(userInput, turn);
    EXPECT_FALSE(result.hasLost);
}

// B3 - interior cell as first input → must not be a mine
TEST(FillMinesTest, FirstClick_InteriorCell_IsNotMine) {
    auto gm = makegameMode(5, 5, 12);
    Field field(gm);
    Common::UserInputReturnStruct userInput;
    userInput.coords     = {3, 3};
    userInput.isFlag     = false;
    userInput.isAutoFlag = false;
    int turn = 1;
    auto result = field.placeUserInput(userInput, turn);
    EXPECT_FALSE(result.hasLost);
}

// B4 - minimum mine count (1 mine)
// Use 3x3 grid so center cell is always numbered (not zero),
// preventing flood fill and win condition from zeroing minesLeft.
TEST(FillMinesTest, MineCount_One_PlacedCorrectly) {
    auto gm = makegameMode(3, 3, 1);
    Field field(gm);
    Common::UserInputReturnStruct userInput;
    userInput.coords     = {2, 2};
    userInput.isFlag     = false;
    userInput.isAutoFlag = false;
    int turn = 1;
    field.placeUserInput(userInput, turn);
    EXPECT_EQ(field.getMinesLeft(), 1);
}

// B5 - typical mine count (12 mines) → getMinesLeft() should equal 12
TEST(FillMinesTest, MineCount_Typical_PlacedCorrectly) {
    auto gm = makegameMode(5, 5, 12);
    Field field(gm);
    Common::UserInputReturnStruct userInput;
    userInput.coords     = {3, 3};
    userInput.isFlag     = false;
    userInput.isAutoFlag = false;
    int turn = 1;
    field.placeUserInput(userInput, turn);
    EXPECT_EQ(field.getMinesLeft(), 12);
}

// B6 - maximum mine count (24 mines)
// Use 10x10 grid so clicking one cell cannot clear the board
// and trigger gameWon() which would zero out minesLeft.
TEST(FillMinesTest, MineCount_Maximum_PlacedCorrectly) {
    auto gm = makegameMode(10, 10, 24);
    Field field(gm);
    Common::UserInputReturnStruct userInput;
    userInput.coords     = {5, 5};
    userInput.isFlag     = false;
    userInput.isAutoFlag = false;
    int turn = 1;
    field.placeUserInput(userInput, turn);
    EXPECT_EQ(field.getMinesLeft(), 24);
}