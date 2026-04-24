package minesweeper;

/**
 * Models the board-size selection logic from Game::chooseGamemode() in
 * src/game.cpp.  The preset constants are taken directly from include/game.h:
 *
 *   small  →  9 cols × 9 rows,  10 mines  (difficulty == 1)
 *   medium → 16 cols × 16 rows, 40 mines  (difficulty == 2)
 *   large  → 30 cols × 16 rows, 99 mines  (difficulty == 3)
 */
public class GameModeSelector {

    // Constants mirrored from include/game.h
    private static final int SMALL_COLS  = 9,  SMALL_ROWS  = 9,  SMALL_MINES  = 10;
    private static final int MEDIUM_COLS = 16, MEDIUM_ROWS = 16, MEDIUM_MINES = 40;
    private static final int LARGE_COLS  = 30, LARGE_ROWS  = 16, LARGE_MINES  = 99;

    private boolean menuPresented = false;
    private GameMode selectedMode = null;

    /** Simulates the menu being rendered to the player. */
    public void presentMenu() {
        menuPresented = true;
        selectedMode  = null;
    }

    public boolean isMenuPresented() {
        return menuPresented;
    }

    /**
     * Simulates the player pressing 1 / 2 / 3 in the menu.
     *
     * @param size "small", "medium", or "large" (case-insensitive)
     */
    public void selectDifficulty(String size) {
        if (!menuPresented) {
            throw new IllegalStateException("Menu has not been presented yet.");
        }
        switch (size.trim().toLowerCase()) {
            case "small":
                selectedMode = new GameMode(SMALL_COLS,  SMALL_ROWS,  SMALL_MINES);
                break;
            case "medium":
                selectedMode = new GameMode(MEDIUM_COLS, MEDIUM_ROWS, MEDIUM_MINES);
                break;
            case "large":
                selectedMode = new GameMode(LARGE_COLS,  LARGE_ROWS,  LARGE_MINES);
                break;
            default:
                throw new IllegalArgumentException("Unknown board size: " + size);
        }
    }

    public GameMode getSelectedMode() {
        return selectedMode;
    }
}
