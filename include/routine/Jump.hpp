#pragma once

#include "../Link.hpp"

class JumpLink
{
    const bool is_meta_;
    const int contents_distance_;
    const int links_distance_;
    
public:
    JumpLink(bool is_meta, int contents_distance, int links_distance)
        : is_meta_(is_meta),
          contents_distance_(contents_distance),
          links_distance_(links_distance)
        {}
    
    Distance operator()(...) const
        {
            return Distance(is_meta_, contents_distance_, links_distance_);
        }
};
      
