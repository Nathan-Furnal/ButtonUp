#include <buttonstack.h>
#include <catch2/catch.hpp>

TEST_CASE("ButtonStack tests") {
  ButtonStack bs{};
  SECTION("Behavior") {
    REQUIRE(bs.isEmpty());
    bs.push(Button::WHITE);
    REQUIRE_FALSE(bs.isEmpty());
    REQUIRE(bs.hasWhite());
    REQUIRE(bs.nButtons() == 1);
    REQUIRE_FALSE(bs.has2SameButtons());
    bs.push(Button::RED);
    REQUIRE(bs.nButtons() == 2);
    REQUIRE_FALSE(bs.has2SameButtons());
    bs.push(Button::RED);
    REQUIRE(bs.nButtons() == 3);
    REQUIRE_FALSE(bs.isEmpty());
    REQUIRE(bs.has2SameButtons());
    REQUIRE(bs[0] == Button::WHITE);
    REQUIRE(bs[2] == Button::RED);
    bs.reset();
    REQUIRE(bs.isEmpty());
  }
}
