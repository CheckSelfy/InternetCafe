//
// Created by artyom on 19.05.2024.
//

#include "../include/table.h"

void table::seat() {
    this->state = table_state::BUSY;
}

void table::unseat(unsigned amount) {
    this->state = table_state::FREE;
    this->money_hours = (amount + 59) / 60;
    this->summary_time += amount;
}

bool table::can_seat() const {
    return this->state == table_state::FREE;
}

