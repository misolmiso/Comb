#pragma once


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
}
