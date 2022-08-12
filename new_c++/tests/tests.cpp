// This tells doctest to provide a main() function
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
// #include "../include/example.h"


TEST_SUITE("First") {

    TEST_CASE("Addition") {
    //     constexpr Matrix<int, 3, 2> a{{1, 2, 3, 4, 5, 6}};
    //     constexpr Matrix<int, 3, 2> b{{2, 1, 0, 3, 4, 8}};

    //     constexpr Matrix<int, 3, 2> c = a + b;

    //     static_assert(c.at(0, 0) == 3);
    //     static_assert(c.at(0, 1) == 3);
    //     static_assert(c.at(1, 0) == 3);
    //     static_assert(c.at(1, 1) == 7);
    //     static_assert(c.at(2, 0) == 9);
    //     static_assert(c.at(2, 1) == 14);
	
		REQUIRE(add(2, 3) == 5);
    }
}

TEST_SUITE("Second") {
    TEST_CASE("template Add") {
    //     using MyList = List<1, List<2, List<3, List<4, Null>>>>;
    //     static_assert(ListFirst<MyList>::Value == 1);
    //     static_assert(ListFirst<List<5, Null>>::Value == 5);
//         static_assert(ListFirst<Null>::Value == 0); // should not compile
		REQUIRE(t_add<2, 3>() == 5);
    }
}

