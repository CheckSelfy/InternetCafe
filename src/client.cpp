//
// Created by artyom on 19.05.2024.
//

#include "../include/client.h"

client::client(std::string name) : state(client_state::INSIDE), name(std::move(name)), sess(nullptr) {
}

void client::wait() {
    this->state = client_state::WAITING;
}

void client::seat(table *table, const time_unit &time) {
    if (sess != nullptr) { // changing seat
        sess->end_session(time);
    }
    this->sess = std::make_unique<session>(table, time);
    this->state = client_state::PLAYING;
}

table *client::unseat(const time_unit &time) {
    if (sess == nullptr) {
        return nullptr;
    }
    table* result = sess->getTable();
    sess->end_session(time);
    return result;
}

std::string const &client::get_name() const {
    return name;
}

bool client::is_playing() const {
    return this->state == client_state::PLAYING;
}

bool client::is_waiting() const {
    return this->state == client_state::WAITING;
}
