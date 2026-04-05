/*
 * =============================================================================
 * File: tests/test_field_gameLost.cpp
 *
 * Abstract:
 *   Date        Description                              Developer
 *   ----------  ---------------------------------------  -----------------
 *   2026-04-03  Field::gameLost test cases               N. Schweikhart
 *
 * Note: gameLost is private and called by placeUserInput when a mine is hit.
 * It blocks at the end waiting for an Enter key press via getInputEnterKey().
 * To work around this we run it in a background thread, check state changes
 * that occur before the block, then simulate Enter via a stdin pipe to
 * unblock and join the thread cleanly.
 * =============================================================================
 */

#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#define pipe(fds)   _pipe(fds, 256, O_BINARY)
#define dup2        _dup2
#define write       _write
#define close       _close
#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif
#else
#include <unistd.h>
#endif
#include "test_helpers.h"

// Helper: redirects stdin to a pipe and writes a newline to simulate Enter
void simulateEnter(int delayMs = 200)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    int pipefd[2];
    pipe(pipefd);
    dup2(pipefd[0], STDIN_FILENO);
    write(pipefd[1], "\n", 1);
    close(pipefd[1]);
}

// P1 - coveredLeft should be 0 after gameLost regardless of board state
TEST(GameLostTest, CoveredLeft_IsZero_AfterGameLost) {
    auto gm = makegameMode(3, 3, 1);
    Field field(gm);

    // trigger gameLost indirectly: place a mine at (2,2) then click it
    // we need turn > 1 so fillMines is skipped and we control mine placement
    // instead we call placeUserInput on turn 1 first to fill mines,
    // then keep clicking until we find one
    // simplest: use 3x3 with 8 mines — only 1 safe cell
    auto gm2 = makegameMode(3, 3, 8);
    Field field2(gm2);

    Common::UserInputReturnStruct userInput;
    userInput.isFlag     = false;
    userInput.isAutoFlag = false;

    // turn 1: click (1,1) — safe guaranteed (fillMines excludes it)
    userInput.coords = {1, 1};
    int turn = 1;
    field2.placeUserInput(userInput, turn);

    // turn 2: click (2,2) — guaranteed to be a mine (8 mines, only (1,1) safe)
    // run in a thread since gameLost will block on Enter
    std::thread enterThread(simulateEnter, 200);
    userInput.coords = {2, 2};
    turn = 2;
    auto result = field2.placeUserInput(userInput, turn);
    enterThread.join();

    // assert
    EXPECT_TRUE(result.hasLost);
    EXPECT_EQ(field2.getCoveredLeft(), 0);
}