#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

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

    int FindPartNumbers();

    bool AreSymbolsAdjacent(size_t, size_t);

    int FindGearRatios();

public:
    EngineSchematic(const char *);

    int AddPartNumbers();

    int AddGearRatios();

    std::vector<int> GetGearRatio(size_t, Line);

    size_t GetFrontPos(size_t, Line);

    size_t GetBackPos(size_t, Line);
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

int EngineSchematic::AddGearRatios()
{
    auto sum = 0;

    while (std::getline(schematic, lines[NEXT]))
    {
        sum += FindGearRatios();
        lines[PREV] = lines[CURR];
        lines[CURR] = lines[NEXT];
    }

    sum += FindGearRatios();
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

    if (front_pos != std::string::npos)
    {
        if (AreSymbolsAdjacent(front_pos, back_pos))
        {
            sum += std::stoi(lines[CURR].substr(front_pos, back_pos - front_pos));
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
        auto back_line = line->begin() + (back_pos + 1 >= line->size() ? line->size() - 1 : back_pos + 1);

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

int EngineSchematic::FindGearRatios()
{
    auto sum = 0;
    size_t pos = lines[CURR].find("*");
    while (pos != std::string::npos)
    {
        auto numbers = GetGearRatio(pos, PREV);

        auto next_numbers = GetGearRatio(pos, CURR);
        numbers.insert(numbers.end(), next_numbers.begin(), next_numbers.end());

        next_numbers = GetGearRatio(pos, NEXT);
        numbers.insert(numbers.end(), next_numbers.begin(), next_numbers.end());

        if (numbers.size() == 2)
        {
            sum += numbers[0] * numbers[1];
        }

        pos = lines[CURR].find("*", pos + 1);
    }

    return sum;
}

std::vector<int> EngineSchematic::GetGearRatio(size_t pos, Line line)
{
    std::vector<int> numbers;

    if (isdigit(lines[line][pos]))
    {
        auto front_pos = GetFrontPos(pos, line);
        auto back_pos = GetBackPos(pos, line);

        numbers.push_back(std::stoi(lines[line].substr(front_pos, back_pos - front_pos)));
        return numbers;
    }

    if (pos > 0)
    {
        if (isdigit(lines[line][pos - 1]))
        {
            auto back_pos = pos;
            auto front_pos = GetFrontPos(pos - 1, line);

            numbers.push_back(std::stoi(lines[line].substr(front_pos, back_pos - front_pos)));
        }
    }

    if (pos < lines[line].size() - 1)
    {
        if (isdigit(lines[line][pos + 1]))
        {
            auto front_pos = pos + 1;
            auto back_pos = GetBackPos(pos + 1, line);

            numbers.push_back(std::stoi(lines[line].substr(front_pos, back_pos - front_pos)));
        }
    }

    return numbers;
}

size_t EngineSchematic::GetFrontPos(size_t pos, Line line)
{
    auto front_pos = pos + 1;

    while (isdigit(lines[line][front_pos - 1]))
    {
        front_pos--;
        if (front_pos == 0)
        {
            break;
        }
    }

    return front_pos;
}

size_t EngineSchematic::GetBackPos(size_t pos, Line line)
{
    auto back_pos = pos;
    while (isdigit(lines[line][back_pos]))
    {
        back_pos++;
        if (back_pos == lines[line].size())
        {
            break;
        }
    }

    return back_pos;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Expected exactly one argument" << std::endl;
        return EXIT_FAILURE;
    }

    EngineSchematic engine_schematic(argv[1]);
    std::cout << "Sum of gear ratios: " << engine_schematic.AddGearRatios() << std::endl;
}
