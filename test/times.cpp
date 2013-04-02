#include "Comb.hpp"

using comb::lit;

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Times_)

BOOST_AUTO_TEST_CASE(single)
{
    comb::Program<int, bool> p =
        comb::entry_
        >> comb::times_(3)[lit(10) >> 20] >> 30 >> 40;

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
    
    BOOST_CHECK_THROW(c1.advance(false), const char *);

}

BOOST_AUTO_TEST_CASE(nest)
{
    comb::Program<int, bool> p =
        comb::entry_ 
        >> 1
        >>
        comb::times_(2)
        [
            comb::times_(2)
            [
                comb::entry_
                >> 2
                >> 3
                ] >>
            comb::entry_
            >> 4
            >> 5
            ]
        >> 6;

    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 1);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 2);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 3);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 2);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 3);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 4);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 5);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 2);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 3);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 2);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 3);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 4);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 5);

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, 6);

    BOOST_CHECK_THROW(c1.advance(true), const char *);
}

BOOST_AUTO_TEST_SUITE_END() // Times
