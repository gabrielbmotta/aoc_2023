#include <main.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::array<int, 2> GetRecord(const char *);

int GetMarginOfError(int, int);

int main(int argc, char **argv)
{
    std::cout << "BoatingSchool v" << BOATING_SCHOOL_VERSION_MAJOR << "."
              << BOATING_SCHOOL_VERSION_MINOR << std::endl;

    if (argc != 2)
    {
        std::cerr << "Expected exactly 1 argument" << std::endl;
        return EXIT_FAILURE;
    }

    auto record = GetRecord(argv[1]);
    auto margin_of_error = GetMarginOfError(record[0], record[1]);

    std::cout << "Margin of error: " << margin_of_error << std::endl;
}

std::array<int, 2> GetRecord(const char *input)
{
    std::ifstream buf(input);

    std::string str;
    buf >> str;
    if (str != "Time:")
    {
        throw std::invalid_argument("no time indicator");
    }

    std::array<int, 2> record;
    std::string number;
    while (!buf.eof())
    {
        // auto val = 0;
        buf >> str;
        if (buf.eof())
        {
            break;
        }

        if (str == "Distance:")
        {
            record[0] = std::stoi(number);
            number.clear();
            continue;
        }

        number += str;
    }

    record[1] = std::stoi(number);
    buf.close();

    return record;
}

int GetMarginOfError(int time, int record)
{
    auto margin_of_error = 0;
    for (int speed = 1; speed < time; speed++)
    {
        auto distance = speed * (time - speed);
        if (distance > record)
        {
            margin_of_error++;
        }
    }

    return margin_of_error;
}
