#include "Comb.hpp"

using comb::lit;

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Loop)

bool fun(bool a)
{
    return a;
}

BOOST_AUTO_TEST_CASE(single)
{
    comb::Program<int, bool> p =
        comb::entry_ >> 4 >> comb::loop_[lit(10) >> 20] >> 30;
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 20);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 20);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 20);
}


BOOST_AUTO_TEST_SUITE_END() // Loop
