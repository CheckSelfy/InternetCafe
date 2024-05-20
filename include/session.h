#pragma once

#include <stdexcept>
#include "time_unit.h"
#include "table.h"

class session {
    table* t;
    const time_unit start_time;

public:
    session(table* t, time_unit const& start_time);

    void end_session(time_unit const& end_time);

    table* getTable() const;
};
