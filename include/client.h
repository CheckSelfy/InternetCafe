#pragma once

#include <memory>
#include "time_unit.h"
#include "table.h"
#include "session.h"

class client {
public:
    // CLIENT LIFE:
    // ctor -> INSIDE -> WAITING -> DESTRUCTION (не дождался)
    // ctor -> INSIDE -> WAITING -> PLAYING -> DESTRUCTION (поиграл)
    // ctor -> INSIDE -> PLAYING -> DESTRUCTION (сразу сел за стол)
    enum class client_state {
        /* OUTSIDE is state before construction */
        INSIDE,
        WAITING,
        PLAYING
        /* GOING_AWAY is immediate state before destruction */
    };

private:
    client_state state;
    std::unique_ptr<session> session;

public:
    explicit client() : state(client_state::INSIDE), session(nullptr) {
    }

    void wait() {
        this->state = client_state::WAITING;
    }

    void seat(table * table, time_unit const& start_time) {
    }


};
