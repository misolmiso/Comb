#pragma once

#include "../Link.hpp"

class JumpLink
{
    const int contents_distance_;
    const int links_distance_;
    
public:
    JumpLink(int contents_distance, int links_distance)
        : contents_distance_(contents_distance),
          links_distance_(links_distance)
        {}
    
    Distance operator()(CounterCondition&, ...) const
        {
            return Distance(true, contents_distance_, links_distance_ + 1);
        }
};
      
template <typename Arg, bool InvertFlag>
class ConditionJumpLink
{
    typedef boost::function<bool(typename Links<Arg>::func_param_type)> pred_type;
        
    pred_type pred_;

    const int contents_size_;
    const int links_size_;
                
public:
    ConditionJumpLink(
        const pred_type& pred,
        int contents_size,
        int links_size
        )
        : pred_(pred), contents_size_(contents_size), links_size_(links_size)
        {}

        
    Distance operator()(CounterCondition&, typename Links<Arg>::func_param_type a)
        {
            return pred_(a) != InvertFlag ?
                Distance(true, contents_size_, links_size_ + 1) :
                Distance(true, 0, 1);
        }
};

