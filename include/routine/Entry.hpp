#pragma once

#include "../Routine.hpp"

namespace comb
{
    static const struct Entry
        : public Routine<Entry>
    {
        Entry()
            : Routine<Entry>(0, 0)
            {}
        
        template <typename D>
        inline void storeDataImpl(Contents<D> & cont) const
            {}

        template <typename A>
        inline void storeLinkImpl(Links<A> & cont) const
            {}
    } entry_;
}
