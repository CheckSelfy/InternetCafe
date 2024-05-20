#pragma once

#include <cassert>
#include <iosfwd>
#include <utility>

struct time_unit {
private:
    unsigned minutes;
public:
    explicit time_unit(unsigned hour = 0, unsigned minutes = 0);

    void setMinutes(unsigned hour, unsigned minutes);

    unsigned operator-(time_unit const & other) const;

    auto operator<=>(time_unit const & rhs) const = default;

    time_unit& operator+= (unsigned delta);

    friend std::istream &operator>>(std::istream &is, time_unit &t);

    friend std::ostream &operator<<(std::ostream &os, time_unit const &t);
};