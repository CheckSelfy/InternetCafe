#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <set>
#include <numeric>
#include <map>
#include <algorithm>
#include <list>
#include "table.h"
#include "client.h"

class cafe {
    const time_unit start;
    const time_unit end;
    const unsigned price;
    std::ostream &os;

    std::vector<table> tables;
    std::list<client *> waiting_clients; // best practice here is using intrusive semantics here (for O(1) deleting),
    // but using boost if forbidden, so deleting here is O(n)
    std::map<std::string, client> clients;

    enum class CAFE_ERROR {
        NOT_OPENED,
        ALREADY_HERE,
        UNKNOWN_CLIENT,
        PLACE_IS_BUSY,
        FREE_TABLE
    };

    template<class... T>
    void log(time_unit const &t, unsigned id, T &&... args) {
        os << t << " " << id;
        ((os << " " << args), ...);
        os << std::endl;
    }

public:
    cafe(unsigned table_count, time_unit const &start, time_unit const &end, unsigned price, std::ostream &os);

    void client_come(time_unit const &time, std::string const &client_name);

    void client_seat(time_unit const &time, std::string const &client_name, unsigned int table_id);

    void client_wait(time_unit const &time, std::string const &client_name);

    void client_gone(time_unit const &time, std::string const &client_name);

    void kick_visitors();

    void write_statistics();

private:
    void client_seat(time_unit const &time, std::string const &client_name, unsigned table_id, bool by_force);

    void client_gone(time_unit const &time, std::string const &client_name, bool by_force);

    void print_error(time_unit const &t, CAFE_ERROR state);

};

