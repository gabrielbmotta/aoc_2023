#include <main.h>

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<std::array<int, 2>> GetRecords(const char *);

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

    auto records = GetRecords(argv[1]);

    auto margin_of_error = 0;
    for (auto it = records.begin(); it != records.end(); it++)
    {
        auto mie = GetMarginOfError(it->at(0), it->at(1));
        if (margin_of_error == 0)
        {
            margin_of_error = mie;
        }
        else
        {
            margin_of_error *= mie;
        }
    }

    std::cout << "Margin of error: " << margin_of_error << std::endl;
}

std::vector<std::array<int, 2>> GetRecords(const char *input)
{
    std::ifstream buf(input);

    std::string str;
    buf >> str;
    if (str != "Time:")
    {
        throw std::invalid_argument("no time indicator");
    }

    std::vector<std::array<int, 2>> records;
    while (!buf.fail())
    {
        auto val = 0;
        buf >> val;

        if (!buf.fail())
        {
            records.push_back({val, -1});
        }
    }
    buf.clear();

    buf >> str;
    if (str != "Distance:")
    {
        throw std::invalid_argument("no distance indicator");
    }

    for (auto it = records.begin(); it != records.end(); it++)
    {
        buf >> it->at(1);
    }

    return records;
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
