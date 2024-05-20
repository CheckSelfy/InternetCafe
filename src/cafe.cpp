#include "../include/cafe.h"

void cafe::print_error(const time_unit &t, cafe::CAFE_ERROR state) {
    std::string error_message;
    if (state == CAFE_ERROR::NOT_OPENED) {
        error_message = "NotOpenYet";
    } else if (state == CAFE_ERROR::ALREADY_HERE) {
        error_message = "YouShallNotPass";
    } else if (state == CAFE_ERROR::UNKNOWN_CLIENT) {
        error_message = "ClientUnknown";
    } else if (state == CAFE_ERROR::PLACE_IS_BUSY) {
        error_message = "PlaceIsBusy";
    } else if (state == CAFE_ERROR::FREE_TABLE) {
        error_message = "ICanWaitNoLonger!";
    }

    log(t, 13, error_message);
}

void cafe::client_gone(const time_unit &time, const std::string &client_name, bool by_force) {
    log(time, by_force ? 11 : 4, client_name);
    client &goner = clients.at(client_name);
    table *t = goner.unseat(time);

    clients.erase(client_name);

    if (!by_force && t != nullptr && !waiting_clients.empty()) { // give table to another
        client *newcomer = waiting_clients.front();
        waiting_clients.pop_front();
        client_seat(time, newcomer->get_name(), std::distance(tables.data(), t), true);
    }
}

void cafe::client_seat(const time_unit &time, const std::string &client_name, unsigned int table_id, bool by_force) {
    log(time, by_force ? 12 : 2, client_name, table_id + 1);
    table &t = tables.at(table_id);

    if (!clients.contains(client_name)) {
        print_error(time, CAFE_ERROR::UNKNOWN_CLIENT);
        return;
    }

    client &cl = clients.at(client_name);
    if (!t.can_seat()) {
        print_error(time, CAFE_ERROR::PLACE_IS_BUSY);
        return;
    }

    cl.seat(&t, time);
}

void cafe::kick_visitors() {
    for (auto &[name, client]: clients) {
        client_gone(end, name, true);
    }
}

void cafe::client_gone(const time_unit &time, const std::string &client_name) {
    client_gone(time, client_name, false);
}

void cafe::client_wait(const time_unit &time, const std::string &client_name) {
    log(time, 3, client_name);
    client &cl = clients.at(client_name);
    if (std::any_of(tables.begin(), tables.end(),
                    [](table const &t) { return t.can_seat(); })) {
        // there is free table
        print_error(time, CAFE_ERROR::FREE_TABLE);
        return;
    }

    if (waiting_clients.size() >= tables.size()) {
        client_gone(time, client_name, true); // immediate go away
    } else {
        waiting_clients.push_back(&cl);
    }
}

void cafe::client_seat(const time_unit &time, const std::string &client_name, unsigned int table_id) {
    client_seat(time, client_name, table_id, false);
}

void cafe::client_come(const time_unit &time, const std::string &client_name) {
    log(time, 1, client_name);

    if (time < start || time > end) {
        print_error(time, CAFE_ERROR::NOT_OPENED);
        return;
    }
    if (clients.contains(client_name)) {
        print_error(time, CAFE_ERROR::ALREADY_HERE);
        return;
    }

    clients.insert({client_name, client(client_name)});
}

cafe::cafe(unsigned int table_count, const time_unit &start, const time_unit &end, unsigned int price, std::ostream &os)
        :
        start(start), end(end), price(price), os(os), tables(table_count) {
    if (start > end) {
        throw std::invalid_argument("Start time can't be later than end");
    }
}

void cafe::write_statistics() {
    for (int table_idx = 0; table_idx < tables.size(); table_idx++) {
        os << table_idx + 1 << " "
           << tables.at(table_idx).get_money_hours() * price << " "
           << tables.at(table_idx).get_used_time() << std::endl;
    }
}
