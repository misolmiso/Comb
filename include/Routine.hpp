#pragma once

#include "Link.hpp"



template <class Derived>
class Routine
{
    const int contents_size_;
    const int links_size_;
    
public:
    Routine(int contents_size, int links_size)
        : contents_size_(contents_size),
          links_size_(links_size)
        {}

    virtual ~Routine() {}
    
    const int getContentsSize() const
        {
            return contents_size_;
        }

    const int getLinksSize() const
        {
            return links_size_;
        }

    template <typename D>
    inline void storeData(Contents<D> & cont) const
        {
            static_cast<const Derived*>(this)->storeData(cont);
        }

    template <typename A>
    inline void storeLink(Links<A> & cont) const
        {
            static_cast<const Derived*>(this)->storeLink(cont);
        }
};

