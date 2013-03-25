#include <iostream>
#include <string>

#include "routine/Sequence.hpp"
#include "Program.hpp"

using namespace comb;

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Base)

BOOST_AUTO_TEST_CASE(command)
{
    Program<int, bool> p(lit(5));
    Program<int, bool>::Counter c(p);

    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 5);

    BOOST_CHECK_THROW(c.advance(true), const char *);
}


BOOST_AUTO_TEST_CASE(sequence)
{
    Program<int, bool> p =
        lit(4) >> lit(5) >> lit(10);
    
    Program<int, bool>::Counter c(p);

    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 4);
    
    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 5);

    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 10);

    BOOST_CHECK_THROW(c.advance(true), const char *);
}


BOOST_AUTO_TEST_SUITE_END() // Base
