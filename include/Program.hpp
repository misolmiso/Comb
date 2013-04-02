#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include <boost/operators.hpp>

#include "Link.hpp"
#include "Routine.hpp"


struct ExitLink
{
    Distance operator()(CounterCondition&, ...) const
    {
        return Distance(false, 1, 1);
    }
};

namespace comb
{
    template <typename Dat, typename Arg = void>
    class Program;
    
    template <typename Dat, typename Arg>
    class Program
    {
    public:
        class Counter
            : boost::operators<Program<Dat, Arg>::Counter>
        {
            Contents<Dat> & contents_;
            Links<Arg>  & links_;
            CounterCondition condition_;
            Index i_;

        public:
            explicit Counter(
                Program & p
                )
                : contents_(p.contents_), links_(p.links_)
                {}

            Counter(const Program<Dat, Arg>::Counter &c)
                : contents_(c.contents_), links_(c.links_), i_(c.i_)
                {}

            static
            const Program<Dat, Arg>::Counter
            end(
                Program & p,
                const Index & i
                )
                {
                    Program<Dat, Arg>::Counter temp(p);
                    temp.i_ = i;
                    return temp;
                }

            
            Dat & operator*() const
                {
                    return contents_[i_];
                }

            void advance(typename Links<Arg>::func_param_type a)
                {
                    while (i_.advance(links_[i_](condition_, a))){
                    }
                }

            bool operator==(const Program<Dat, Arg>::Counter &c) const
                {
                    return c.i_.getLinkIndex() == i_.getLinkIndex();
                }
        };

    private:
        Contents<Dat> contents_;
        Links<Arg> links_;

        Index end_index_;

    
    public:
        template <class R>
        Program(const Routine<R> & r)
            : contents_(r.getContentsSize()),
              links_(r.getLinksSize() + 1),
              end_index_(r.getContentsSize() - 1, r.getLinksSize() + 1)
            {
                r.storeData(contents_);
                r.storeLink(links_);
                links_.push_back(ExitLink());
            }

        Counter getCounter()
            {
                return Counter(*this);
            }

        Counter getEndCounter()
            {
                return Counter::end(*this, end_index_);
            }
    };

    template <typename Dat>
    class Program<Dat, void>
    {
    public:
        class Counter
            : boost::operators<Program<Dat, void>::Counter>
        {
            Contents<Dat> & contents_;
            Links<void>  & links_;
            CounterCondition condition_;
            Index i_;

        public:
            explicit Counter(
                Program & p
                )
                : contents_(p.contents_), links_(p.links_)
                {}

            Counter(const Program<Dat, void>::Counter &c)
                : contents_(c.contents_), links_(c.links_), i_(c.i_)
                {}

            static
            const Program<Dat, void>::Counter
            end(
                Program & p,
                const Index & i
                )
                {
                    Program<Dat, void>::Counter temp(p);
                    temp.i_ = i;
                    return temp;
                }

            
            Dat & operator*() const
                {
                    return contents_[i_];
                }

            void advance()
                {
                    while (i_.advance(links_[i_](condition_))){
                    }
                }

            bool operator==(const Program<Dat, void>::Counter &c) const
                {
                    return c.i_.getLinkIndex() == i_.getLinkIndex();
                }
        };

        class Iterator
            : public boost::iterator_facade<
            Program<Dat, void>::Iterator,
            Dat,
            boost::forward_traversal_tag
            >
        {
            Counter c_;
            
        public:
            explicit Iterator(const Counter & c)
                : c_(c)
                {}
            
        private:
            friend class boost::iterator_core_access;
            
            void increment() {
                c_.advance();
            }

            bool equal(const Iterator& other) const
                {
                    return c_ == other.c_;
                }
            
            Dat& dereference() const
                {
                    return *c_;
                }
        };

    private:
        Contents<Dat> contents_;
        Links<void> links_;

        Index end_index_;

    
    public:
        template <class R>
        Program(const Routine<R> & r)
            : contents_(r.getContentsSize()),
              links_(r.getLinksSize() + 1),
              end_index_(r.getContentsSize() - 1, r.getLinksSize() + 1)
            {
                r.storeData(contents_);
                r.storeLink(links_);
                links_.push_back(ExitLink());
            }

        Counter getCounter()
            {
                return Counter(*this);
            }

        Counter getEndCounter()
            {
                return Counter::end(*this, end_index_);
            }
        
        Iterator begin()
            {
                Counter c(getCounter());
                c.advance();
                return Iterator(c);
            }

        Iterator end()
            {
                return Iterator(Counter::end(*this, end_index_));
            }
    };
}
