//
// Created by artyom on 19.05.2024.
//

#include <stdexcept>
#include "../include/table.h"

void table::seat() {
    if (!table::can_seat()) {
        throw std::logic_error("table is seated by another user");
    }
    this->state = table_state::BUSY;
}

void table::unseat(unsigned amount) {
    this->state = table_state::FREE;
    this->money_hours += (amount + 59) / 60;
    this->summary_time += amount;
}

bool table::can_seat() const {
    return this->state == table_state::FREE;
}

unsigned table::get_money_hours() const {
    return money_hours;
}

time_unit table::get_used_time() const {
    return summary_time;
}
