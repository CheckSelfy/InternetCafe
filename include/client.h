#pragma once

#include <memory>
#include <utility>
#include "time_unit.h"
#include "table.h"
#include "session.h"

class client {
public:
    enum class client_state {
        /* OUTSIDE is state before construction */
        INSIDE,
        WAITING,
        PLAYING
        /* GOING_AWAY is immediate state before destruction */
    };

private:
    const std::string name;
    client_state state;
    std::unique_ptr<session> sess;

public:
    explicit client(std::string name);

    void wait();

    void seat(table * table, time_unit const& time);

    table* unseat(time_unit const& time);

    [[nodiscard]] std::string const & get_name() const;

    [[nodiscard]] bool is_playing() const;

    [[nodiscard]] bool is_waiting() const;
};
