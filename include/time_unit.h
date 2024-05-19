#pragma once

#include <cassert>
#include <iosfwd>
#include <utility>

struct time_unit {
private:
    unsigned minutes; // minutes since start of day
public:
    explicit time_unit(unsigned hour = 0, unsigned minutes = 0);

    void setMinutes(unsigned hour, unsigned minutes);

    friend std::istream& operator>>(std::istream& is, time_unit& t);
    friend std::ostream& operator<<(std::ostream& os, time_unit const& t);
};