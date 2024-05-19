#pragma once

#include "time_unit.h"

class table {
private:
    enum class table_state {
        FREE,
        BUSY
    } state;

    unsigned money_hours;
    time_unit summary_time;
public:
    table() : state(table_state::FREE), money_hours(0), summary_time() {}

    [[nodiscard]] bool can_seat() const;

    void seat();

    void unseat(unsigned amount);
};