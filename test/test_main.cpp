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

    comb::Program<int>::Iterator it = p.begin();
    
    comb::Program<int>::Iterator end = p.end();

    std::copy(it, end, std::ostream_iterator<int>(std::cout, "\n"));
}


BOOST_AUTO_TEST_SUITE_END() 
