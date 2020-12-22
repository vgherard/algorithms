#include "partitions.h"
#include "test/catch.hpp"
#include <utility>

// Uncomment the following line to bypass the test guard below
// #define RUN_ALL_TESTS



TEST_CASE("s = 1, A = [1]")
{   
    int s = 1;
    std::vector<int> A{1};
    
    std::vector<std::vector<int> > expected{{0}};    
	REQUIRE(partitions::summing_to(s, A) == expected);
}

TEST_CASE("s = 1, A = [1, 2, 3]")
{   
    int s = 1;
    std::vector<int> A{1, 2, 3};
    
    std::vector<std::vector<int> > expected{{0}};
	REQUIRE(partitions::summing_to(s, A) == expected);
}


TEST_CASE("s = 2, A = [1, 2]")
{   
    int s = 2;
    std::vector<int> A{1, 2};
    
    std::vector<std::vector<int> > expected{{1}};
	REQUIRE(partitions::summing_to(s, A) == expected);
}

TEST_CASE("s = 3, A = [1, 2, 3]")
{   
    int s = 3;
    std::vector<int> A{1, 2, 3};
    
    std::vector<std::vector<int> > expected{{1, 0}, {2}};
	REQUIRE(partitions::summing_to(s, A) == expected);
}

TEST_CASE("s = 4, A = [1:4]")
{   
    int s = 4;
    std::vector<int> A{1, 2, 3, 4};
    
    std::vector<std::vector<int> > expected{{2, 0}, {3}};
	REQUIRE(partitions::summing_to(s, A) == expected);
}

TEST_CASE("s = 3, A = [1, 1, 1, 3]")
{   
    int s = 3;
    std::vector<int> A{1, 1, 1, 3};
    
    std::vector<std::vector<int> > expected{{2, 1, 0}, {3}};
	REQUIRE(partitions::summing_to(s, A) == expected);
}

TEST_CASE("s = 10, A = [5, 5, 2, 3]")
{   
    int s = 10;
    std::vector<int> A{5, 5, 2, 3};
    
    std::vector<std::vector<int> > expected{{1, 0}, {3, 2, 0}, {3, 2, 1}};
	REQUIRE(partitions::summing_to(s, A) == expected);
}

TEST_CASE("Some intersections of sorted vectors")
{   
    using pairs = std::vector<std::pair<std::vector<int>, std::vector<int> > >;
    pairs true_pairs;
    true_pairs.push_back({ {3, 2, 1}, {9, 3} });
    true_pairs.push_back({ {4, 3, 2, 2, 2, 1}, {2, 0, 0, 0} });
    
    pairs false_pairs;
    false_pairs.push_back({{4, 3, 1}, {9, 2}});
    
    for(auto pair : true_pairs)
        REQUIRE(partitions::intersect(pair.first, pair.second));
    for(auto pair : false_pairs)
        REQUIRE(not partitions::intersect(pair.first, pair.second));
}

#if defined(RUN_ALL_TESTS)


#endif // !RUN_ALL_TESTS
