//
// Created by artyom on 20.05.2024.
//

#include "../include/session.h"

session::session(table *t, const time_unit &start_time) : t(t), start_time(start_time) {
    t->seat();
}

void session::end_session(const time_unit &end_time) {
    t->unseat(end_time - start_time);
}

table *session::getTable() const {
    return t;
}
