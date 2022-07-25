#include <catch2/catch.hpp>
#include <game.h>

TEST_CASE("Game tests") {
  SECTION("Setup") {
    Game g{};
    REQUIRE(g.getState() == Game::BEGIN);
    REQUIRE(g.nonEmptyStacks(0).size() == 9); // N_STACKS = 9
    REQUIRE(g.turns() == 0);
    REQUIRE(g.redRoundResult() == 0);
    REQUIRE(g.blackRoundResult() == 0);
    REQUIRE(g.redVictoryPoints() == 0);
    REQUIRE(g.blackVictoryPoints() == 0);
    g.setState(Game::BLACK);
    REQUIRE(g.getState() == Game::BLACK);
  }
  SECTION("Playing") {
    // Reset the game and "shuffle" in testMode
    // This means that the buttons are not shuffled
    // and follow the original buttons declaration:
    // <WHITE, WHITE, WHITE, RED, RED, RED, BLACK, BLACK, BLACK>
    // <  0,     1,     2,    3,   4,   5,    6,     7,     8  >
    Game g{};
    g.reset();
    g.shuffleStacks(true);
    // In the core game logic, there is no protection for moving colors
    // other than white because the controller must take care of that
    // Not a problem for testing.
    REQUIRE(g[0][0] == Button::WHITE);
    REQUIRE(g[1][0] == Button::WHITE);
    REQUIRE(g[2][0] == Button::WHITE);
    REQUIRE(g[3][0] == Button::RED);
    REQUIRE(g[4][0] == Button::RED);
    REQUIRE(g[5][0] == Button::RED);
    REQUIRE(g[6][0] == Button::BLACK);
    REQUIRE(g[7][0] == Button::BLACK);
    REQUIRE(g[8][0] == Button::BLACK);
    // --- Test moves --- /
    g.setState(Game::RED); // Let RED be first
    g.moveStack(0);        // Makes 0 empty and 1 has 2 buttons
    REQUIRE(
        g.getState() ==
        Game::RED); // As there was 2 same buttons on <1>, state does not change
    REQUIRE(g[0].isEmpty());
    REQUIRE(g[1].nButtons() == 2);
    REQUIRE(g[1].has2SameButtons());
    g.moveStack(1); // 1 has 2 buttons -> they go to 2 and 3 respectively
    REQUIRE(g.getState() == Game::BLACK); // State has changed since there
                                          // aren't 2 same buttons on top
    REQUIRE(g[1].isEmpty());
    REQUIRE((g[2][0] == Button::WHITE && g[2][1] == Button::WHITE));
    REQUIRE((g[3][0] == Button::RED && g[2][1] == Button::WHITE));
    g.moveStack(2); // 2 has 2 buttons -> 3 has 3 buttons and 4 has 2 buttons
    g.moveStack(3); // 3 has buttons -> 4 has 3 buttons 5 & 6 have 2 buttons
    REQUIRE(g[3].isEmpty());
    REQUIRE(g[4].nButtons() == 3);
    REQUIRE(g[5].nButtons() == 2);
    REQUIRE(g[6].nButtons() == 2);
    g.moveStack(
        8); // Moving 8, it will go to the first non empty -> 4 has 4 buttons
    REQUIRE(g[8].isEmpty());
    REQUIRE(g[4].nButtons() == 4);
    g.moveStack(7); // Moving 7 -> 4 has 5 buttons
    REQUIRE(g[7].isEmpty());
    REQUIRE(g[4].nButtons() == 5);
    // NOW ==> 4: 5buttons, 5: 2buttons, 6: 2buttons (9 total)
    // Moving 4 will empty 4, cause 5 to have 3 buttons and 6 to have 6 buttons
    g.moveStack(4);
    REQUIRE(g[4].isEmpty());
    REQUIRE(g[5].nButtons() == 3);
    REQUIRE(g[6].nButtons() == 6);
    // Moving 6 will drop the remaning buttons into 5
    // Meaning that 5 has 9 buttons and the game is over!
    g.moveStack(6);
    REQUIRE(g[6].isEmpty());
    REQUIRE(g[5].nButtons() == 9);
    REQUIRE(g.isGameOver());
    REQUIRE(g.turns() == 8); // Game always ends after 8 turns
    // --- End game management --- //
    // This is the result if the previous round was played on paper (final
    // result is)
    // clang-format off
    // <BLACK>
    // <BLACK>
    // <RED>
    // <WHITE>
    // <WHITE>
    // <BLACK>
    // <RED>
    // <WHITE>
    // <RED>
    // clang-format on
    g.computeRoundPoints();
    REQUIRE(g.blackRoundResult() == 21);   // 21 points after the round above
    REQUIRE(g.redRoundResult() == 11);     // 11 points after the round above
    REQUIRE(g.blackVictoryPoints() == 10); // (21 - 11)
    REQUIRE(g.redVictoryPoints() == 0);
    // --- Resetting cleans up the round points but the victory points are still
    // there
    g.reset();
    g.shuffleStacks(true);
    REQUIRE(g.blackRoundResult() == 0);
    REQUIRE(g.redRoundResult() == 0);
    REQUIRE(g.blackVictoryPoints() == 10);
    REQUIRE(g.redVictoryPoints() == 0);
  }
}
