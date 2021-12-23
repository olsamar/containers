
#include "catch.hpp"

#include "../map/map.hpp"
#include <map>

// clang++ tests/map_test.cpp -std=c++11 -o testMap && ./testMap

TEST_CASE("Testing map constructors", "[integer keys]")
{
	std::map<int,int> firstMap;
	ft::map<int, int> second;
}
