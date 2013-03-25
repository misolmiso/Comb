#include "routine/Sequence.hpp"
#include "routine/If.hpp"
#include "Program.hpp"

bool fun(bool a)
{
    return a;
}

using comb::lit;

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(If)

BOOST_AUTO_TEST_CASE(single)
{
    comb::Program<int, bool> p =
        lit(4) >> comb::if_(fun)[lit(10)] >> lit(20);
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 20);

    BOOST_CHECK_THROW(c1.advance(true), const char *);

    comb::Program<int,bool>::Counter c2(p.getCounter());

    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 4);
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 20);

    BOOST_CHECK_THROW(c2.advance(false), const char *);
    BOOST_CHECK_EQUAL(*c2, 20);
}


BOOST_AUTO_TEST_CASE(multi)
{
    comb::Program<int, bool> p =
        lit(4) >>
        comb::if_(fun)[
            lit(10) >> lit(15)
            ] >>
        lit(20);
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 15);

    c1.advance(false);
    BOOST_CHECK_EQUAL(*c1, 20);

    BOOST_CHECK_THROW(c1.advance(true), const char *);

    comb::Program<int,bool>::Counter c2(p.getCounter());
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 4);
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 20);

    BOOST_CHECK_THROW(c2.advance(true), const char *);
}

BOOST_AUTO_TEST_CASE(nest)
{
    comb::Program<int, bool> p =
        lit(4) >>
        
        comb::if_(fun)
        [
            lit(10) >>
            
            comb::if_(fun)
            [
                lit(15)
                ]
            
            ] >>
        
        lit(20);
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 15);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 20);

    BOOST_CHECK_THROW(c1.advance(true), const char *);

    comb::Program<int,bool>::Counter c2(p.getCounter());
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 4);
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 20);

    BOOST_CHECK_THROW(c2.advance(true), const char *);

    comb::Program<int,bool>::Counter c3(p.getCounter());
    
    c3.advance(false);
    BOOST_CHECK_EQUAL(*c3, 4);
    
    c3.advance(true);
    BOOST_CHECK_EQUAL(*c3, 10);

    c3.advance(false);
    BOOST_CHECK_EQUAL(*c3, 20);

    BOOST_CHECK_THROW(c3.advance(true), const char *);
}

BOOST_AUTO_TEST_SUITE_END() // If

BOOST_AUTO_TEST_SUITE(IfElse)


BOOST_AUTO_TEST_CASE(if_else)
{
    comb::Program<int, bool> p =
        lit(4) >>
        comb::if_(fun)
        [
            lit(10) >>
            lit(15)
            ]
        [
            lit(-10) >>
            lit(-15)
            ] >>
        lit(20);
    
    comb::Program<int,bool>::Counter c1(p.getCounter());

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 15);

    c1.advance(true);
    BOOST_CHECK_EQUAL(*c1, 20);

    BOOST_CHECK_THROW(c1.advance(true), const char *);

    comb::Program<int,bool>::Counter c2(p.getCounter());
    
    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 4);

    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, -10);

    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, -15);

    c2.advance(false);
    BOOST_CHECK_EQUAL(*c2, 20);

    BOOST_CHECK_THROW(c2.advance(true), const char *);
}


BOOST_AUTO_TEST_SUITE_END() // IfElse
