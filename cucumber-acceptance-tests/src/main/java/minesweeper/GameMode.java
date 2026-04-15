package minesweeper;

/**
 * Represents the board configuration returned after the player selects a
 * difficulty.  The field values mirror the constants in include/game.h of
 * the C++ minesweeper project.
 */
public class GameMode {

    private final int cols;
    private final int rows;
    private final int mines;

    public GameMode(int cols, int rows, int mines) {
        this.cols  = cols;
        this.rows  = rows;
        this.mines = mines;
    }

    public int getCols()  { return cols;  }
    public int getRows()  { return rows;  }
    public int getMines() { return mines; }
}
