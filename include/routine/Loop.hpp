#pragma once

template <class R>
class Loop_
    : public Routine<Loop_<R> >
{
    const R r_;
    
public:
    explicit Loop_(const Routine<R> & r)
        : Routine<Loop_>(r.getContentsSize(), r.getLinksSize() + 1),
          r_(static_cast<const R &>(r))
        {}
        
    template <typename D>
    inline void storeDataImpl(Contents<D> & cont) const
        {
            r_.storeData(cont);
        }

    template <typename A>
    inline void storeLinkImpl(Links<A> & cont) const
        {
            r_.storeLink(cont);
            cont.push_back(JumpLink(-r_.getContentsSize(), -r_.getLinksSize() - 1));
        }
};

namespace comb
{
    static const struct LoopGenerator_
    {
        template <class R>
        Loop_<R> operator[](const Routine<R> & r) const
            {
                return Loop_<R>(r);
            }
    } loop_;
}
