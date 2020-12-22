#include "change.h"
#include "test/catch.hpp"

// Uncomment the following line to bypass the test guard below
#define RUN_ALL_TESTS

#if defined(RUN_ALL_TESTS)

TEST_CASE("Change of 2 is 2")
{
	REQUIRE(change::get_change(2) == 2);
}

TEST_CASE("Change of 28 is 6")
{
	REQUIRE(change::get_change(28) == 6);
}

#endif // !RUN_ALL_TESTS
