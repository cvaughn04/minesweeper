/*
 * =============================================================================
 * File: cucumber-acceptance-tests/src/test/java/minesweeper/stepdefinitions/HelpPageSteps.java
 *
 * Abstract:
 *   Date        Description                                      Developer
 *   ----------  -----------------------------------------------  -----------------
 *   2026-04-17  Cucumber step definitions for the help page      R. Vaughn
 * =============================================================================
 */
package minesweeper.stepdefinitions;

import io.cucumber.java.en.Given;
import io.cucumber.java.en.Then;
import io.cucumber.java.en.When;
import minesweeper.HelpPage;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Cucumber step definitions for the "Help page toggle" feature.
 *
 * Each scenario maps to the help-toggle behaviour in
 * Input::toggleHelp() (src/input.cpp) and Print::printExplanation()
 * (src/print.cpp).  Cucumber creates a fresh instance of this class
 * for every scenario, so the HelpPage field is safe per-scenario state.
 */
public class HelpPageSteps {

    private HelpPage helpPage;

    @Given("I am in an active game")
    public void iAmInAnActiveGame() {
        helpPage = new HelpPage();
        helpPage.startGame();
        assertTrue(helpPage.isGameActive(),
                "Game should be active after startGame()");
    }

    @When("I open the help page")
    public void iOpenTheHelpPage() {
        helpPage.open();
        assertTrue(helpPage.isOpen(),
                "Help page should be open after open()");
    }

    /**
     * Verifies that the help page lists a control containing the given keyword.
     * The Cucumber expression captures the quoted string from the feature step.
     *
     * @param keyword text that must appear in at least one control entry
     */
    @Then("the help page should contain {string} as a listed control")
    public void theHelpPageShouldContainAsAListedControl(String keyword) {
        assertTrue(helpPage.containsControl(keyword),
                "Expected the help page to list a control containing: \"" + keyword + "\"");
    }
}
