Feature: Board size selection
  As a player, I want to select a board size option in the menu,
  so that the board size and mine count are customizable.

  Scenario: Easy/Small mode
    Given the menu is presented
    When I select the small board
    Then the board should be 9x9 with 10 mines

  Scenario: Medium mode
    Given the menu is presented
    When I select the medium board
    Then the board should be 16x16 with 40 mines

  Scenario: Hard/Large mode
    Given the menu is presented
    When I select the large board
    Then the board should be 30x16 with 99 mines
