#include "car_fueling.h"
#include "test/catch.hpp"

TEST_CASE("impossible")
{
    int d = 10;
    int m = 3;
    std::vector<int> stops{1, 2, 5, 9};
	REQUIRE(car_fueling::compute_min_refills(d, m, stops) == -1);
}

TEST_CASE("two stops")
{
    int d = 500;
    int m = 200;
    std::vector<int> stops{100, 200, 300, 400};
	REQUIRE(car_fueling::compute_min_refills(d, m, stops) == 2);
}

TEST_CASE("all stops")
{
    int d = 10;
    int m = 1;
    std::vector<int> stops{1, 2, 3, 4, 5, 6, 7, 8, 9};
	REQUIRE(car_fueling::compute_min_refills(d, m, stops) == 9);
}

TEST_CASE("No stops2")
{
    int d = 200;
    int m = 250;
    std::vector<int> stops{100, 150};
	REQUIRE(car_fueling::compute_min_refills(d, m, stops) == 0);
}


TEST_CASE("No stops")
{
    int d = 10;
    int m = 20;
    std::vector<int> stops{3, 6, 9};
	REQUIRE(car_fueling::compute_min_refills(d, m, stops) == 0);
}


#if defined(RUN_ALL_TESTS)





#endif // !RUN_ALL_TESTS
