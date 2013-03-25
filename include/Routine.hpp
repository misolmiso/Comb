#pragma once

#include "Link.hpp"

template <class Derived>
class Routine
{
    const int contents_size_;
    const int links_size_;
    
public:
    Routine(int contents_size, int links_size)
        : contents_size_(contents_size),
          links_size_(links_size)
        {}

    virtual ~Routine() {}
    
    const int getContentsSize() const
        {
            return contents_size_;
        }

    const int getLinksSize() const
        {
            return links_size_;
        }

    template <typename D>
    inline void storeData(Contents<D> & cont) const
        {
            static_cast<const Derived*>(this)->storeData(cont);
        }

    template <typename A>
    inline void storeLink(Links<A> & cont) const
        {
            static_cast<const Derived*>(this)->storeLink(cont);
        }
};

struct UnitContent
{
    const void * const p_;

public:
    explicit UnitContent(const void * const p)
        : p_(p)
        {}

    const void * const get() const
        {
            return p_;
        }
};

struct UnitLink
{
    Distance operator()(...) const
        {
            return Distance(false, 1, 1);
        }
};

class JumpLink
{
    const bool is_meta_;
    const int contents_distance_;
    const int links_distance_;
    
public:
    JumpLink(bool is_meta, int contents_distance, int links_distance)
        : is_meta_(is_meta),
          contents_distance_(contents_distance),
          links_distance_(links_distance)
        {}
    
    Distance operator()(...) const
        {
            return Distance(is_meta_, contents_distance_, links_distance_);
        }
};
      

template <typename C>
class Unit
    : public Routine<Unit<C> >,
      private UnitContent
{

public:
    Unit(const C & c)
        : Routine<Unit<C> >(1, 1),
          UnitContent(&c)
        {}

    template <typename D>
    inline void storeData(Contents<D> & cont) const
        {
            cont.push_back(*(static_cast<const C * const>(UnitContent::get())));
        }

    template <typename A>
    inline void storeLink(Links<A> & cont) const
        {
            cont.push_back(UnitLink());
        }
};    


namespace comb
{
    
    template <typename C>
    Unit<C> lit(const C& c)
    {
        return Unit<C>(c);
    }

    struct Entry
        : public Routine<Entry>
    {
        Entry()
            : Routine<Entry>(0, 0)
            {}
        
        template <typename D>
        inline void storeData(Contents<D> & cont) const
            {}

        template <typename A>
        inline void storeLink(Links<A> & cont) const
            {}
    };

    static const Entry entry_;
    
}
