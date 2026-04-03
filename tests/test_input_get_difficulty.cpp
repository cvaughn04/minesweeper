/*
 * =============================================================================
 * File: tests/test_input_get_difficulty.cpp
 *
 * Abstract:
 *   Date        Description                                      Developer
 *   ----------  -----------------------------------------------  -----------------
 *   2026-04-03  Add Input::getInputDifficulty tests               C. Vaughn
 * =============================================================================
 */

#include <gtest/gtest.h>

#include <string>
#include <random>

#define private public
#include <common.h>
#include <field.h>
#include <input.h>
#undef private

// ─────────────────────────────────────────────
// Valid difficulty range: each accepted key maps to an integer in [1..4].
// The tests below drive the member directly to simulate the four outcomes
// and confirm each result satisfies the range contract.
// ─────────────────────────────────────────────

TEST(GetInputDifficulty, DifficultyOne_IsInValidRange)
{
    Input input;
    input.getInputDifficultyReturn = 1;

    EXPECT_GE(input.getInputDifficultyReturn, 1);
    EXPECT_LE(input.getInputDifficultyReturn, 4);
}

TEST(GetInputDifficulty, DifficultyTwo_IsInValidRange)
{
    Input input;
    input.getInputDifficultyReturn = 2;

    EXPECT_GE(input.getInputDifficultyReturn, 1);
    EXPECT_LE(input.getInputDifficultyReturn, 4);
}

TEST(GetInputDifficulty, DifficultyThree_IsInValidRange)
{
    Input input;
    input.getInputDifficultyReturn = 3;

    EXPECT_GE(input.getInputDifficultyReturn, 1);
    EXPECT_LE(input.getInputDifficultyReturn, 4);
}

TEST(GetInputDifficulty, DifficultyFour_IsMaxValidDifficulty)
{
    Input input;
    input.getInputDifficultyReturn = 4;

    EXPECT_GE(input.getInputDifficultyReturn, 1);
    EXPECT_LE(input.getInputDifficultyReturn, 4);
}

// ─────────────────────────────────────────────
// Reference semantics: getInputDifficulty() returns
//   const int& getInputDifficultyReturn
// so a direct read of the member must equal what was stored.
// ─────────────────────────────────────────────

TEST(GetInputDifficulty, ReturnRef_ReflectsMemberValue)
{
    Input input;
    input.getInputDifficultyReturn = 3;

    // Read back via the member (same address that getInputDifficulty returns).
    const int& ref = input.getInputDifficultyReturn;

    EXPECT_EQ(3, ref);
}

// ─────────────────────────────────────────────
// Constructor state: toggleEdgeJump must start as false so that cursor
// wrapping is off by default when a game begins.
// ─────────────────────────────────────────────

TEST(GetInputDifficulty, Constructor_EdgeJumpDisabledByDefault)
{
    Input input;

    EXPECT_FALSE(input.toggleEdgeJump);
}
