#pragma once

#include "Link.hpp"
#include "Routine.hpp"


struct ExitLink
{
    Distance operator()(...) const
    {
        throw "exit";
    }
};

namespace comb
{
    template <typename Dat, typename Arg>
        class Program
    {
        Contents<Dat> contents_;
        Links<Arg> links_;

    
    public:
        template <class R>
        Program(const Routine<R> & r)
            : contents_(r.getContentsSize()),
              links_(r.getLinksSize())
            {
                r.storeData(contents_);
                r.storeLink(links_);
                links_.push_back(ExitLink());
            }

    
        class Counter
        {
            Contents<Dat> & contents_;
            Links<Arg>  & links_;
            Index i_;

        public:
            explicit Counter(
                Program & p
                )
                : contents_(p.contents_), links_(p.links_)
                {}

            Counter(const Program<Dat,Arg>::Counter &c)
                : contents_(c.contents_), links_(c.links_), i_(c.i_)
                {}

            Dat & operator*()
                {
                    return contents_[i_];
                }

            void advance(typename Links<Arg>::func_param_type a)
                {
                    while (i_.advance(links_[i_](a))){
                    }
                }
        };


        Counter getCounter()
            {
                return Counter(*this);
            }
    };

}
