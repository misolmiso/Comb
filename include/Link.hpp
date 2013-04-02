#pragma once

#include <vector>
#include <iostream>
#include <stack>

#include <stdexcept>

#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/call_traits.hpp>

class Index;

class Distance;

template <typename C>
class Contents;

template <typename A>
class Links;

struct CounterCondition;

class Distance
{
    bool is_meta_;
    int contents_distance_;
    int link_distance_;

public:
    Distance(bool is_meta, int contents_distance, int link_distance)
        : is_meta_(is_meta),
          contents_distance_(contents_distance),
          link_distance_(link_distance)
        {}

    int getContentsDistance() const
        {
            return contents_distance_;
        }

    int getLinkDistance() const
        {
            return link_distance_;
        }

    const bool isMeta() const
        {
            return is_meta_;
        }
};

class Index
{
    int contents_index_;
    int link_index_;

public:
    Index()
        : contents_index_(-1), link_index_(0)
        {}

    Index(const int contents_index, const int link_index)
        : contents_index_(contents_index), link_index_(link_index)
        {}

    const bool advance(const Distance & d)
        {
            contents_index_ += d.getContentsDistance();
            link_index_ += d.getLinkDistance();
            return d.isMeta();
        }

    const int getContentsIndex() const
        {
            return contents_index_;
        }

    const int getLinkIndex() const
        {
            return link_index_;
        }
};



template <typename C>
class Contents
{
    typedef typename boost::call_traits<C>::param_type param_type;
    
    std::vector<C> v_;

public:
    explicit Contents(size_t size)
        : v_()
        {}

    void push_back(param_type a)
        {
            v_.push_back(a);
        }

    void add(const Contents & cont)
        {
            std::copy(cont.v_.begin(), cont.v_.end(), std::back_inserter(v_));
        }
            
    
    C & operator[](const Index & i)
        {
            if (i.getContentsIndex() >= v_.size())
                throw std::out_of_range("comb::Program::counter operator* range_check");
            return v_[i.getContentsIndex()];
        }
};

template <typename A>
class Links
{
public:
    typedef typename boost::call_traits<A>::param_type func_param_type;
    typedef typename boost::function<const Distance(CounterCondition&, func_param_type)> func_type;

private:
    std::vector<func_type> v_;

public:
    explicit Links(size_t size)
        : v_()
        {}

    void push_back(const func_type & a)
        {
            v_.push_back(a);
        }

    void add(const Links & cont)
        {
            std::copy(cont.v_.begin(), cont.v_.end(), std::back_inserter(v_));
        }

    func_type & operator[](const Index & i)
        {
            if (i.getLinkIndex() >= v_.size())
                throw std::out_of_range("comb::Program::counter advance range_check");
            return v_[i.getLinkIndex()];
        }
};

template <>
class Links<void>
{
public:
    typedef typename boost::function<const Distance(CounterCondition&)> func_type;

private:
    std::vector<func_type> v_;

public:
    explicit Links(size_t size)
        : v_()
        {}

    void push_back(const func_type & a)
        {
            v_.push_back(a);
        }

    void add(const Links & cont)
        {
            std::copy(cont.v_.begin(), cont.v_.end(), std::back_inserter(v_));
        }

    func_type & operator[](const Index & i)
        {
            return v_[i.getLinkIndex()];
        }
};


struct CounterCondition
{
    std::stack<unsigned> times_counter;
};
