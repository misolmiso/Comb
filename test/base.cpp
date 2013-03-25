#include <iostream>
#include <string>

#include "routine/Sequence.hpp"
#include "Program.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Base)

BOOST_AUTO_TEST_CASE(lit)
{
    comb::Program<int, bool> p =
        comb::lit(4) >> 5 >> 10;

    comb::Program<int, bool>::Counter c(p);

    
    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 4);
    
    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 5);

    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 10);

    BOOST_CHECK_THROW(c.advance(true), const char *);
}


BOOST_AUTO_TEST_CASE(entry)
{
    comb::Program<int, bool> p =
        comb::entry_ >> 4 >> 5 >> 10;
    
    comb::Program<int, bool>::Counter c(p);

    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 4);
    
    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 5);

    c.advance(true);
    BOOST_CHECK_EQUAL(*c, 10);

    BOOST_CHECK_THROW(c.advance(true), const char *);
}


BOOST_AUTO_TEST_SUITE_END() // Base
