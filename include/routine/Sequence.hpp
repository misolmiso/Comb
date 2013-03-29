#pragma once

#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include "../Routine.hpp"
#include "Unit.hpp"

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
    const F f_;
    const G g_;

public:
    Sequence(const Routine<F> & rf, const Routine<G> & rg)
        : Routine<Sequence<F, G> >(rf.getContentsSize() + rg.getContentsSize(), rf.getLinksSize() + rg.getLinksSize()),
          f_(static_cast<const F &>(rf)),
          g_(static_cast<const G &>(rg))
        {}

    template <typename D>
    inline void storeDataImpl(Contents<D> & cont) const
        {
            f_.storeData(cont);
            g_.storeData(cont);
        }

    template <typename A>
    inline void storeLinkImpl(Links<A> & cont) const
        {
            f_.storeLink(cont);
            g_.storeLink(cont);
        }
};


template <class T1, typename T2>
Sequence<T1, T2>
genSequence(
    const Routine<T1>& f,
    const Routine<T2>& g,
    typename boost::enable_if<boost::is_convertible<T2*, Routine<T2>*> >::type* = 0
    )
{
    return Sequence<T1, T2>(f, g);
}
    
template <class T1, typename D>
Sequence<T1, Unit<D> >
genSequence(
    const Routine<T1>& f,
    const D& g,
    typename boost::disable_if<boost::is_convertible<D*, Routine<D>*> >::type* = 0
    )
{
    return Sequence<T1, Unit<D> >(f, Unit<D>(g));
}
    


template <class T1, typename D>
Sequence<
    T1,
    typename boost::mpl::if_<
        boost::is_convertible<D*, Routine<D>*>,
        D,
        Unit<D>
        >::type
    >
operator>>(
    const Routine<T1>& f,
    const D& g
    )
{
    return genSequence(f, g);
}


