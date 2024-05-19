#pragma once

#include "time_unit.h"
#include "table.h"

class session {
    table* t;
    const time_unit start_time;

public:
    session(table* t, time_unit const& start_time) : t(t), start_time(start_time) {}

    void end_session(time_unit const& end_time) {
        t->unseat(end_time - start_time);
    }

    bool change_table(table* new_table, time_unit const & cur_time) {
        if (!new_table->can_seat()) {
            return false;
        }

        // TODO you stayed here!
        t->unseat_no_pay(cur_time);
    }
};
