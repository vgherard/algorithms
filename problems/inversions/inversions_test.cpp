#include "inversions.h"
#include "test/catch.hpp"
#include <iostream>

// Uncomment the following line to bypass the test guard below
// #define RUN_ALL_TESTS

TEST_CASE("merge: zero inversions")
{
	std::vector<int> a{1, 2, 3, 4, 5, 6};
    size_t l = 0;
    size_t r = 6;
    size_t m = l + (r - l) / 2;
    long long inversions = 0;
    
    std::vector<int> expected_vec{1, 2, 3, 4, 5, 6};
    long long expected_inversions = 0;
    
    
    merge(a, l, r, m, inversions);
    for(size_t i = 0; i < a.size(); i++) 
        REQUIRE(a[i] == expected_vec[i]);
    REQUIRE(inversions == expected_inversions);
    
}

TEST_CASE("merge: two inversions")
{
	std::vector<int> a{1, 2, 3, 1, 5, 6};
    size_t l = 0;
    size_t r = 6;
    size_t m = l + (r - l) / 2;
    long long inversions = 0;
    
    std::vector<int> expected_vec{1, 1, 2, 3, 5, 6};
    long long expected_inversions = 2;
    
    merge(a, l, r, m, inversions);
    
    for(auto & x : a) std::cout << x << " ";
    std::cout << "\n";
    
    for(size_t i = 0; i < a.size(); i++) 
        REQUIRE(a[i] == expected_vec[i]);
    REQUIRE(inversions == expected_inversions);
    
}


TEST_CASE("merge_sort with two inversions and repetitions")
{
	std::vector<int> a{2, 3, 9, 2 , 9};
    size_t l = 0;
    size_t r = 5;
    size_t m = l + (r - l) / 2;
    long long inversions = 0;
    
    std::vector<int> expected_vec{2, 2, 3, 9, 9};
    long long expected_inversions = 2;
    
    merge_sort(a, l, r, inversions);
    
    for(auto & x : a) std::cout << x << " ";
    std::cout << "\n";
    
    for(size_t i = 0; i < a.size(); i++) 
        REQUIRE(a[i] == expected_vec[i]);
    REQUIRE(inversions == expected_inversions);
    
}
#if defined(RUN_ALL_TESTS)


#endif // !RUN_ALL_TESTS
