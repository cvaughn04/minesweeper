/*
 * =============================================================================
 * File: cucumber-acceptance-tests/src/main/java/minesweeper/HelpPage.java
 *
 * Abstract:
 *   Date        Description                                      Developer
 *   ----------  -----------------------------------------------  -----------------
 *   2026-04-17  Help page model for the help page toggle         R. Vaughn
 * =============================================================================
 */
package minesweeper;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * Models the help page toggled by pressing 'h' or 'H' during gameplay.
 *
 * The control entries mirror the output of Print::printExplanation() in
 * src/print.cpp exactly.  The hint shown on the game board itself
 * ("'h' or 'H': Help") comes from Print::getHelpText in the same file.
 *
 * In the real game, Input::toggleHelp() (src/input.cpp) clears the screen,
 * calls Print::printExplanation(), waits for ENTER, then restores the board.
 * This class captures that same open/dismiss lifecycle without any I/O.
 */
public class HelpPage {

    /**
     * The hint label shown on the game board at all times, taken directly
     * from Print::getHelpText in src/print.cpp.
     */
    public static final String BOARD_HINT = "'h' or 'H': Help";

    /**
     * Immutable list of control entries shown inside the help page,
     * taken line-by-line from Print::printExplanation() in src/print.cpp.
     */
    private static final List<String> CONTROLS = Collections.unmodifiableList(Arrays.asList(
            "Arrow Keys:    navigate",
            "ENTER:         reveal",
            "SPACE:         place or remove a flag",
            "f or F:        let the computer place the flags for you",
            "r or R:        trigger auto revealing (after placing flags)",
            "s or S:        automatically place flags, auto-reveal and repeat recursively",
            "c or C:        toggle cursor jump to opposite edge on or off",
            "q or Q:        quit"
    ));

    private boolean gameActive = false;
    private boolean helpOpen   = false;

    /** Simulates starting an active game session. */
    public void startGame() {
        gameActive = true;
        helpOpen   = false;
    }

    public boolean isGameActive() {
        return gameActive;
    }

    /**
     * Simulates pressing 'h' / 'H' to open the help page.
     * Mirrors Input::toggleHelp() in src/input.cpp.
     *
     * @throws IllegalStateException if called before a game is active
     */
    public void open() {
        if (!gameActive) {
            throw new IllegalStateException("Cannot open help page: no active game.");
        }
        helpOpen = true;
    }

    public boolean isOpen() {
        return helpOpen;
    }

    /** Simulates pressing ENTER to dismiss the help page and return to the game. */
    public void dismiss() {
        helpOpen = false;
    }

    /**
     * Returns the full list of control entries shown on the help page.
     * Each entry is a single line from Print::printExplanation().
     */
    public List<String> getControls() {
        return CONTROLS;
    }

    /**
     * Returns true if any control entry contains {@code keyword} as a
     * case-insensitive substring.
     *
     * @param keyword the text to search for (e.g. "SPACE", "Arrow Keys")
     */
    public boolean containsControl(String keyword) {
        String lower = keyword.toLowerCase();
        for (String entry : CONTROLS) {
            if (entry.toLowerCase().contains(lower)) {
                return true;
            }
        }
        return false;
    }
}
