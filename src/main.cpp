#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/cafe.h"

namespace {
    unsigned parse_table_count(std::ifstream& fin, std::string& line, unsigned & number_line) {
        std::getline(fin, line);
        unsigned result = std::stoul(line);
        number_line++;
        return result;
    }

    std::pair<time_unit, time_unit> parse_work_time(std::ifstream &fin, std::string& line, unsigned &number_line) {
        std::getline(fin, line);
        std::istringstream input(line);

        time_unit s1 = time_unit();
        time_unit s2 = time_unit();
        input >> s1 >> s2;
        number_line++;
        return std::make_pair(s1, s2);
    }

    unsigned parse_price(std::ifstream &fin, std::string& line, unsigned & number_line) {
        std::getline(fin, line);
        unsigned result = std::stoul(line);
        number_line++;
        return result;
    }

    enum class event_type {
        COME = 1,
        SEAT = 2,
        WAIT = 3,
        GONE = 4
    };

    std::istream &operator>>(std::istream &is, event_type &type) {
        int t;
        is >> t;
        type = static_cast<event_type>(t);
        return is;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Expected 2 arguments, found " << argc << "\nUsage: " << argv[0] << " <test_file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream file = std::ifstream(argv[1]);
    if (!file.is_open()) {
        std::cout << "Unable to open file \"" << argv[1] << "\". Exiting..." << std::endl;
        return EXIT_FAILURE;
    }

    unsigned event_number = 1;
    std::string line;
    try {
        auto table_count = parse_table_count(file, line, event_number);
        auto [start, end] = parse_work_time(file, line, event_number);
        auto price = parse_price(file, line, event_number);

        std::cout << start << std::endl;

        cafe cafe_instance = cafe(table_count, start, end, price, std::cout);
        while (std::getline(file, line)) {
            std::istringstream stream = std::istringstream(line);
            time_unit unit;
            event_type event;
            std::string client_name;

            stream >> std::ws >> unit >> event >> client_name;

            if (event == event_type::COME) {
                cafe_instance.client_come(unit, client_name);
            } else if (event == event_type::SEAT) {
                unsigned table_id;
                stream >> table_id;
                table_id--;
                cafe_instance.client_seat(unit, client_name, table_id);
            } else if (event == event_type::WAIT) {
                cafe_instance.client_wait(unit, client_name);
            } else if (event == event_type::GONE) {
                cafe_instance.client_gone(unit, client_name);
            }

            if (stream.peek() != EOF) {
                std::cout << "Line " << event_number << " have extra symbols at the end: \"" << line
                          << "\"\nExiting..." << std::endl;
                return EXIT_FAILURE;
            }

            event_number++;
        }

        cafe_instance.kick_visitors();
        std::cout << end << std::endl;
        cafe_instance.write_statistics();
    } catch (std::invalid_argument const &e) {
        std::cout << "Error parsing line " << event_number << " due to: " << e.what() <<
                  "\nLine: \"" << line << "\"\nExiting..." << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        throw;
    }

    return 0;
}
