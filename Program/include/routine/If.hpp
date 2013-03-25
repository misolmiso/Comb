#pragma once

#include <boost/utility.hpp>
#include <boost/function.hpp>
#include <boost/call_traits.hpp>

#include "../Routine.hpp"

template <typename Arg>
class IfLink;

template <typename Pred>
class IfCondition_;

template <class R, typename Pred>
class If_;

template <class R1, class R2, typename Pred>
class IfElse_;

template <typename Arg>
class IfLink
{
    typedef boost::function<bool(typename Links<Arg>::func_param_type)> pred_type;
        
    pred_type pred_;

    const int if_contents_size_;
    const int if_links_size_;
                
public:
    IfLink(
        const pred_type& pred,
        int contents_size,
        int links_size
        )
        : pred_(pred), if_contents_size_(contents_size), if_links_size_(links_size)
        {}

        
    Distance operator()(typename Links<Arg>::func_param_type a)
        {
            return pred_(a) ?
                Distance(true, 0, 1) :
                Distance(true, if_contents_size_, if_links_size_);
        }
};

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
    inline void storeData(Contents<D> & cont) const
        {
            rt_.storeData(cont);
            rf_.storeData(cont);
        }

    template <typename A>
    inline void storeLink(Links<A> & cont) const
        {
            cont.push_back(IfLink<A>(pred_, rt_.getContentsSize(), rf_.getLinksSize() + 2));
            rt_.storeLink(cont);
            cont.push_back(JumpLink(true, rf_.getContentsSize(), rf_.getLinksSize() + 1));
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
    inline void storeData(Contents<D> & cont) const
        {
            r_.storeData(cont);
        }

    template <typename A>
    inline void storeLink(Links<A> & cont) const
        {
            cont.push_back(IfLink<A>(pred_, r_.getContentsSize(), r_.getLinksSize() + 1));
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
