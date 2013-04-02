#include "Comb.hpp"


using comb::lit;

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(If)

bool fun(bool a)
{
    return a;
}

BOOST_AUTO_TEST_CASE(single)
{
    comb::Program<int, bool> p =
        comb::entry_ >> 4 >> comb::if_(fun)[lit(10)] >> 20;
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 20);

    c1.advance(true);
    BOOST_CHECK_THROW(*c1, std::out_of_range);

    comb::Program<int,bool>::Counter c2(p.getCounter());

    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 4);
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 20);

    c2.advance(false);
    BOOST_CHECK_THROW(*c2, std::out_of_range);
}


BOOST_AUTO_TEST_CASE(multi)
{
    comb::Program<int, bool> p =
        comb::entry_ 
        >> 4
        >>
        comb::if_(fun)
        [
            comb::entry_
            >> 10
            >> 15
            ]
        >> 20;
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 15);

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, 20);

    c1.advance(true);
    BOOST_CHECK_THROW(*c1, std::out_of_range);

    comb::Program<int,bool>::Counter c2(p.getCounter());
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 4);
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 20);

    c2.advance(true);
    BOOST_CHECK_THROW(*c2, std::out_of_range);
}

BOOST_AUTO_TEST_CASE(nest)
{
    comb::Program<int, bool> p =
        comb::entry_ 
        >> 4
        >>
        comb::if_(fun)
        [
            comb::entry_
            >> 10
            >> comb::if_(fun)[lit(15)]
            ]
        >> 20;
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 15);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 20);

    c1.advance(true);
    BOOST_CHECK_THROW(*c1, std::out_of_range);

    comb::Program<int,bool>::Counter c2(p.getCounter());
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 4);
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 20);

    c2.advance(true);
    BOOST_CHECK_THROW(*c2, std::out_of_range);

    comb::Program<int,bool>::Counter c3(p.getCounter());
    
    c3.advance(false);
    BOOST_CHECK_EQUAL(*c3, 4);
    
    c3.advance(true);
    BOOST_CHECK_EQUAL(*c3, 10);

    c3.advance(false);
    BOOST_CHECK_EQUAL(*c3, 20);

    c3.advance(true);
    BOOST_CHECK_THROW(*c3, std::out_of_range);
}


BOOST_AUTO_TEST_CASE(if_else)
{
    comb::Program<int, bool> p =
        comb::entry_
        >> 4
        >>
        comb::if_(fun)
        [
            comb::entry_
            >> 10
            >> 15
            ]
        .else_
        [
            comb::entry_
            >> -10
            >> -15
            ]
        >>
        comb::if_(fun)
        [
            comb::entry_
            >> 30
            >> 45
            ]
        .else_
        [
            comb::entry_
            >> -30
            >> -45
            ]
        >> 20;
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 15);

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, -30);

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, -45);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 20);

    c1.advance(true);
    BOOST_CHECK_THROW(*c1, std::out_of_range);
}


BOOST_AUTO_TEST_SUITE_END() // If
