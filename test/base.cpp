#include <iostream>
#include <string>

#include "Comb.hpp"

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

    c.advance(true);
    BOOST_CHECK_THROW(*c, std::out_of_range);
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

    c.advance(true);
    BOOST_CHECK_THROW(*c, std::out_of_range);
}


BOOST_AUTO_TEST_SUITE_END() // Base
