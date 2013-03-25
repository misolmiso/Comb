#pragma once

#include "../Routine.hpp"

template <class T1, class T2>
class Sequence;

template <class T1, class T2>
Sequence<T1, T2>
operator>>(
    const Routine<T1>&,
    const Routine<T2>&
    );

template <class F, class G>
class Sequence
    : public Routine<Sequence<F, G> >
{
    const F & f_;
    const G & g_;

public:
    Sequence(const Routine<F> & rf, const Routine<G> & rg)
        : Routine<Sequence<F, G> >(rf.getContentsSize() + rg.getContentsSize(), rf.getLinksSize() + rg.getLinksSize()),
          f_(static_cast<const F &>(rf)),
          g_(static_cast<const G &>(rg))
        {}

    template <typename D>
    inline void storeData(Contents<D> & cont) const
        {
            f_.storeData(cont);
            g_.storeData(cont);
        }

    template <typename A>
    inline void storeLink(Links<A> & cont) const
        {
            f_.storeLink(cont);
            g_.storeLink(cont);
        }
};

template <class T1, class T2>
Sequence<T1, T2>
operator>>(
    const Routine<T1>& f,
    const Routine<T2>& g
    )
{
    return Sequence<T1, T2>(f, g);
}



