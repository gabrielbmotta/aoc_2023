#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <string>
#include <stdexcept>
#include <cstdlib>

class EngineSchematic
{
    enum Line
    {
        PREV,
        CURR,
        NEXT
    };

    std::ifstream schematic;

    std::array<std::string, 3> lines;
    std::array<std::map<size_t, int *>, 2> part_numbers;

    int FindPartNumbers();

    bool AreSymbolsAdjacent(size_t, size_t);

public:
    EngineSchematic(const char *);

    int AddPartNumbers();
};

EngineSchematic::EngineSchematic(const char *input) : schematic{input}
{
    std::getline(schematic, lines[CURR]);
}

int EngineSchematic::AddPartNumbers()
{
    auto sum = 0;

    while (std::getline(schematic, lines[NEXT]))
    {
        sum += FindPartNumbers();
        lines[PREV] = lines[CURR];
        lines[CURR] = lines[NEXT];
    }

    sum += FindPartNumbers();
    return sum;
}

int EngineSchematic::FindPartNumbers()
{
    auto sum = 0;
    auto front_pos = std::string::npos;
    auto back_pos = std::string::npos;

    for (auto it = lines[CURR].begin(); it != lines[CURR].end(); it++)
    {
        if (isdigit(*it))
        {
            if (front_pos == std::string::npos)
            {
                front_pos = it - lines[CURR].begin();
                back_pos = front_pos;
            }
            back_pos++;
        }
        else if (front_pos != std::string::npos)
        {
            if (AreSymbolsAdjacent(front_pos, back_pos))
            {
                sum += std::stoi(lines[CURR].substr(front_pos, back_pos - front_pos));
            }

            front_pos = std::string::npos;
        }
    }

    return sum;
}

bool EngineSchematic::AreSymbolsAdjacent(size_t front_pos, size_t back_pos)
{
    auto front_search = front_pos == 0 ? 0 : front_pos - 1;

    for (auto line = lines.begin(); line != lines.end(); line++)
    {
        if (line->empty())
        {
            continue;
        }

        auto front_line = line->begin() + (front_pos == 0 ? 0 : front_pos - 1);
        auto back_line = line->begin() + (back_pos > line->size() ? line->size() : back_pos + 1);

        for (auto it = front_line; it != back_line; it++)
        {
            if (!(*it == '.' || isdigit(*it)))
            {
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Expected exactly one argument" << std::endl;
        return EXIT_FAILURE;
    }

    EngineSchematic engine_schematic(argv[1]);
    std::cout << "Sum of part numbers: " << engine_schematic.AddPartNumbers() << std::endl;
}
