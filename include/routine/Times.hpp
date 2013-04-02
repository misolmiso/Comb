#pragma once

#include <boost/functional.hpp>
#include <boost/bind.hpp>

#include "../Link.hpp"
#include "../Routine.hpp"

struct TimesInitLink
{
    Distance operator()(CounterCondition& c, ...) const
        {
            c.times_counter.push(0);
            return Distance(true, 0, 1);
        }
};

class TimesConditionLink
{
    const unsigned count_;

    const int contents_size_;
    const int links_size_;
                
public:
    TimesConditionLink(
        const unsigned count,
        int contents_size,
        int links_size
        )
        : count_(count), contents_size_(contents_size), links_size_(links_size)
        {}

        
    Distance operator()(CounterCondition& condition, ...)
        {
            if (condition.times_counter.top() < count_) {
                ++(condition.times_counter.top());
                return Distance(true, 0, 1);
            }
            else {
                condition.times_counter.pop();
                return Distance(true, contents_size_, links_size_ + 1);
            }
        }
};

template <class R>
class Times
    : public Routine<Times<R> >
{
    const R r_;
    const unsigned count_;
    
public:
    
    explicit Times(
        const Routine<R> & r,
        const unsigned count
        )
        : Routine<Times<R> >(r.getContentsSize(), r.getLinksSize() + 3),
          r_(static_cast<const R &>(r)),
          count_(count)
        {}

    template <typename D>
    inline void storeDataImpl(Contents<D> & cont) const
        {
            r_.storeData(cont);
        }

    template <typename A>
    inline void storeLinkImpl(Links<A> & cont) const
        {
            cont.push_back(TimesInitLink());
            cont.push_back(TimesConditionLink(count_, r_.getContentsSize(), r_.getLinksSize() + 1));
            r_.storeLink(cont);
            cont.push_back(JumpLink(-r_.getContentsSize(), -r_.getLinksSize() - 2));
        }
};

class TimesCondition
{
    const unsigned count_;

public:
    explicit TimesCondition(const unsigned count)
        : count_(count)
        {}

    template <class R>
    Times<R> operator[](const Routine<R> & r) const
        {
            return Times<R>(r, count_);
        }
};


namespace comb
{
    
    TimesCondition
    inline times_(
        const unsigned count
        )
    {
        return TimesCondition(count);
    }

}                            
