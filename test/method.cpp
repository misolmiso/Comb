#include "Comb.hpp"

using comb::lit;

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(While)

bool fun(bool a)
{
    return a;
}

BOOST_AUTO_TEST_CASE(single)
{
    comb::Method<int, bool> m =
        comb::entry_
        >> comb::while_(fun)[lit(10) >> 20] >> 30 >> 40;

    comb::Program<int, bool> p = m;

    comb::Program<int,bool>::Counter c1(p.getCounter());

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

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, 30);

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, 40);
    
    c1.advance(false);
    BOOST_CHECK_THROW(*c1, std::out_of_range);
}

BOOST_AUTO_TEST_CASE(multi)
{
    comb::Method<int, bool> m1 =
        comb::entry_
        >> 1 >> 2;

    comb::Method<int, bool> m2 =
        comb::entry_
        >> 3 >> 4;
    
    comb::Program<int, bool> p =
        comb::entry_
        >> m1 >> m2;
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, 1);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 2);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 3);

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, 4);

    c1.advance(false);
    BOOST_CHECK_THROW(*c1, std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END() // While
