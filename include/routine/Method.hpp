#pragma once

#include <algorithm>
#include <iterator>

#include "Link.hpp"
#include "Routine.hpp"

namespace comb
{
    template <typename Dat, typename Arg>
    class Method
        : public Routine<Method<Dat, Arg> >
    {
        Contents<Dat> contents_;
        Links<Arg> links_;

    public:
        template <class R>
        Method(const Routine<R>& r)
            : Routine<Method<Dat, Arg> >(r.getContentsSize(), r.getLinksSize()),
              contents_(r.getContentsSize()),
              links_(r.getLinksSize())
            {
                r.storeData(contents_);
                r.storeLink(links_);
            }

        template <typename D>
        inline void storeDataImpl(Contents<D> & cont) const
            {
                cont.add(contents_);
            }

        template <typename A>
        inline void storeLinkImpl(Links<A> & cont) const
            {
                cont.add(links_);
            }
    };
}
