#include <iostream>
#include <stdexcept>

#include "../include/time_unit.h"

void time_unit::setMinutes(unsigned int hour, unsigned int minutes) {
    unsigned new_minutes = hour * 60 + minutes;
    if (new_minutes >= 60 * 24) {
        throw std::invalid_argument("Bad minutes count");
    }
    this->minutes = new_minutes;
}

time_unit::time_unit(unsigned hour, unsigned minutes) {
    setMinutes(hour, minutes);
}

std::istream& operator>> (std::istream& is, time_unit& t) {
    unsigned hour, minutes;
    char colon;
    is >> hour >> colon >> minutes;
    t.setMinutes(hour, minutes);
    return is;
}

std::ostream &operator<<(std::ostream &os, const time_unit &t) {
    return os << t.minutes / 60 << ':' << t.minutes % 60;
}
