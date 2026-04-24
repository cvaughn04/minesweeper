package minesweeper.stepdefinitions;

import io.cucumber.java.en.Given;
import io.cucumber.java.en.Then;
import io.cucumber.java.en.When;
import minesweeper.GameModeSelector;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Cucumber step definitions for the "Board size selection" feature.
 *
 * Each scenario maps to the difficulty-selection branch in
 * Game::chooseGamemode() (src/game.cpp).  Cucumber creates a fresh instance
 * of this class for every scenario, so instance fields are safe to use as
 * per-scenario state holders.
 */
public class BoardSizeSteps {

    private GameModeSelector selector;

    @Given("the menu is presented")
    public void theMenuIsPresented() {
        selector = new GameModeSelector();
        selector.presentMenu();
        assertTrue(selector.isMenuPresented(),
                "Menu should be in the presented state after presentMenu()");
    }

    @When("I select the small board")
    public void iSelectTheSmallBoard() {
        selector.selectDifficulty("small");
    }

    @When("I select the medium board")
    public void iSelectTheMediumBoard() {
        selector.selectDifficulty("medium");
    }

    @When("I select the large board")
    public void iSelectTheLargeBoard() {
        selector.selectDifficulty("large");
    }

    /**
     * Verifies that the selected game mode has the expected dimensions and
     * mine count.  The Cucumber expression "{int}x{int}" captures cols × rows.
     *
     * @param cols  expected number of columns
     * @param rows  expected number of rows
     * @param mines expected number of mines
     */
    @Then("the board should be {int}x{int} with {int} mines")
    public void theBoardShouldBe(int cols, int rows, int mines) {
        assertNotNull(selector.getSelectedMode(),
                "A game mode should have been selected");
        assertEquals(cols,  selector.getSelectedMode().getCols(),
                "Board column count mismatch");
        assertEquals(rows,  selector.getSelectedMode().getRows(),
                "Board row count mismatch");
        assertEquals(mines, selector.getSelectedMode().getMines(),
                "Mine count mismatch");
    }
}
