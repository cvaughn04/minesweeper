# =============================================================================
# File: cucumber-acceptance-tests/src/test/resources/features/help_page.feature
#
# Abstract:
#   Date        Description                                      Developer
#   ----------  -----------------------------------------------  -----------------
#   2026-04-17  feature file for the help page toggle            R. Vaughn
# =============================================================================

Feature: Help page toggle
  As a player, I want to be able to open and dismiss a help page during gameplay,
  so that I can remind myself of the game controls without quitting.

  Scenario: Help page lists the navigation control
    Given I am in an active game
    When I open the help page
    Then the help page should contain "Arrow Keys" as a listed control

  Scenario: Help page lists the flag placement control
    Given I am in an active game
    When I open the help page
    Then the help page should contain "SPACE" as a listed control

  Scenario: Help page lists the quit control
    Given I am in an active game
    When I open the help page
    Then the help page should contain "q or Q" as a listed control
