#pragma once

#include "../Routine.hpp"
#include "Jump.hpp"

template <typename Pred>
class IfCondition_;

template <class R, typename Pred>
class If_;

template <class R1, class R2, typename Pred>
class IfElse_;


template <class Rt, class Rf, typename Pred>
class IfElse_
    : public Routine<IfElse_<Rt, Rf, Pred> >
{
    const Rt & rt_;
    const Rf & rf_;

    const Pred & pred_;

public:
    explicit IfElse_(
        const Routine<Rt> & rt,
        const Routine<Rf> & rf,
        const Pred & pred
        )
        : Routine<IfElse_<Rt, Rf, Pred> >(rt.getContentsSize() + rf.getContentsSize(), rt.getLinksSize() + rf.getLinksSize() + 2),
          rt_(static_cast<const Rt &>(rt)),
          rf_(static_cast<const Rf &>(rf)),
          pred_(pred)
        {}

    template <typename D>
    inline void storeDataImpl(Contents<D> & cont) const
        {
            rt_.storeData(cont);
            rf_.storeData(cont);
        }

    template <typename A>
    inline void storeLinkImpl(Links<A> & cont) const
        {
            cont.push_back(ConditionJumpLink<A, true>(pred_, rt_.getContentsSize(), rf_.getLinksSize() + 1));
            rt_.storeLink(cont);
            cont.push_back(JumpLink(rf_.getContentsSize(), rf_.getLinksSize()));
            rf_.storeLink(cont);
        }
};

template <class R, typename Pred>
class If_
    : public Routine<If_<R, Pred> >
{
    const R r_;
    
    const Pred & pred_;

public:
    explicit If_(
        const Routine<R> & r,
        const Pred & pred
        )
        : Routine<If_<R, Pred> >(r.getContentsSize(), r.getLinksSize() + 1),
          r_(static_cast<const R &>(r)),
          pred_(pred)
        {}


    template <typename Rf>
    IfElse_<R, Rf, Pred> operator[](const Routine<Rf> & rf)
        {
            return IfElse_<R, Rf, Pred>(r_, rf, pred_);
        }
    
    template <typename D>
    inline void storeDataImpl(Contents<D> & cont) const
        {
            r_.storeData(cont);
        }

    template <typename A>
    inline void storeLinkImpl(Links<A> & cont) const
        {
            cont.push_back(ConditionJumpLink<A, true>(pred_, r_.getContentsSize(), r_.getLinksSize()));
            r_.storeLink(cont);
        }
};

template <typename Pred>
class IfCondition_
{
    const Pred & pred_;

public:
    explicit IfCondition_(const Pred& pred)
        : pred_(pred)
        {}

    template <class R>
    If_<R, Pred> operator[](const Routine<R> & r)
        {
            return If_<R, Pred>(r, pred_);
        }
};

namespace comb
{
    
    template <typename Pred>
        IfCondition_<Pred>
        if_(
            const Pred & pred
            )
    {
        return IfCondition_<Pred>(pred);
    }

}                            
