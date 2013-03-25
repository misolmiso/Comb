#pragma once

#include "../Routine.hpp"
#include "Jump.hpp"

template <typename Pred>
class WhileCondition_;

template <class R, typename Pred>
class While_;

template <class R, typename Pred>
class While_
    : public Routine<While_<R, Pred> >
{
    const R r_;
    
    const Pred & pred_;

public:
    explicit While_(
        const Routine<R> & r,
        const Pred & pred
        )
        : Routine<While_<R, Pred> >(r.getContentsSize(), r.getLinksSize() + 2),
          r_(static_cast<const R &>(r)),
          pred_(pred)
        {}


    template <typename Rf>
    IfElse_<R, Rf, Pred> operator[](const Routine<Rf> & rf)
        {
            return IfElse_<R, Rf, Pred>(r_, rf, pred_);
        }
    
    template <typename D>
    inline void storeData(Contents<D> & cont) const
        {
            r_.storeData(cont);
        }

    template <typename A>
    inline void storeLink(Links<A> & cont) const
        {
            cont.push_back(ConditionJumpLink<A, true>(pred_, r_.getContentsSize(), r_.getLinksSize() + 1));
            r_.storeLink(cont);
            cont.push_back(JumpLink(-r_.getContentsSize(), -r_.getLinksSize() - 2));
        }
};

template <typename Pred>
class WhileCondition_
{
    const Pred & pred_;

public:
    explicit WhileCondition_(const Pred& pred)
        : pred_(pred)
        {}

    template <class R>
    While_<R, Pred> operator[](const Routine<R> & r)
        {
            return While_<R, Pred>(r, pred_);
        }
};

namespace comb
{
    
    template <typename Pred>
        WhileCondition_<Pred>
        while_(
            const Pred & pred
            )
    {
        return WhileCondition_<Pred>(pred);
    }

}                            
