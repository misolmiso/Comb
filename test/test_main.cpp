#include <iostream>
#include <algorithm>

#include "Comb.hpp"

#define BOOST_TEST_MODULE ProgramLibrary

using comb::lit;

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(iroiro)

bool fun(bool a)
{
    return a;
}

BOOST_AUTO_TEST_CASE(single)
{
    comb::Program<int> p =
        comb::entry_ >> 4 >> comb::times_(2)[lit(10) >> 20] >> 30;
    
    comb::Program<int>::Counter c1(p.getCounter());

    c1.advance();
    BOOST_CHECK_EQUAL(*c1, 4);
    
    c1.advance();
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance();
    BOOST_CHECK_EQUAL(*c1, 20);

    c1.advance();
    BOOST_CHECK_EQUAL(*c1, 10);

    c1.advance();
    BOOST_CHECK_EQUAL(*c1, 20);

    c1.advance();
    BOOST_CHECK_EQUAL(*c1, 30);

    BOOST_CHECK(c1 != p.getEndCounter());
    
    c1.advance();
    
    BOOST_CHECK(c1 == p.getEndCounter());

    BOOST_CHECK_THROW(c1.advance(), std::out_of_range);
    BOOST_CHECK_THROW(*c1, std::out_of_range);
    
    comb::Program<int>::Iterator it = p.begin();
    comb::Program<int>::Iterator end = p.end();

    BOOST_CHECK_EQUAL(*it, 4);
    
    ++it;
    BOOST_CHECK_EQUAL(*it, 10);

    ++it;
    BOOST_CHECK_EQUAL(*it, 20);

    ++it;
    BOOST_CHECK_EQUAL(*it, 10);

    ++it;
    BOOST_CHECK_EQUAL(*it, 20);

    ++it;
    BOOST_CHECK_EQUAL(*it, 30);

    BOOST_CHECK(it != end);
    ++it;
    BOOST_CHECK(it == end);
}


BOOST_AUTO_TEST_SUITE_END() 
