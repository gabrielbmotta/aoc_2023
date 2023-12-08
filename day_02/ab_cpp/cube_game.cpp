#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <fstream>

struct Cubes
{
    int red;
    int blue;
    int green;

    Cubes(int, int, int);

    Cubes();

    friend bool operator>(const Cubes &, const Cubes &);
};

Cubes::Cubes(int new_red, int new_blue, int new_green)
    : red{new_red},
      blue{new_blue},
      green{new_green}
{
}

Cubes::Cubes() : Cubes(0, 0, 0)
{
}

bool operator>(const Cubes &l, const Cubes &r)
{
    return (l.red > r.red) || (l.blue > r.blue) || (l.green > r.green);
}

int ParseGame(const std::string &, std::vector<Cubes> &);

bool IsGamePossible(const std::vector<Cubes> &);

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "No args" << std::endl;
        return EXIT_FAILURE;
    }
    if (argc > 2)
    {
        std::cout << "Too many args" << std::endl;
        return EXIT_FAILURE;
    }

    // Parse input file line by line
    std::ifstream input(argv[1]);
    std::string line;
    auto sum_ids = 0;
    while (std::getline(input, line))
    {
        std::vector<Cubes> game;
        auto game_number = ParseGame(line, game);
        if (IsGamePossible(game))
        {
            sum_ids += game_number;
        }
    }

    std::cout << sum_ids << std::endl;
}

int ParseGame(const std::string &line, std::vector<Cubes> &game)
{
    std::stringstream buf(line);

    std::string game_keyword;
    std::string game_number_str;

    // Get game keyword and number
    buf >> game_keyword >> game_number_str;
    if (game_keyword != "Game" || game_number_str.back() != ':')
    {
        throw std::invalid_argument("invalid game number");
    }

    // Convert number to integer
    game_number_str.pop_back();
    auto game_number = std::stoi(game_number_str);

    // Set game vector
    game = {Cubes()};

    while (!buf.eof())
    {
        // Parse cube number and color
        int number;
        std::string color;
        buf >> number >> color;

        // Pop separator if needed
        size_t offset_from_end = 1;
        switch (color.back())
        {
        case ';':
            game.push_back({});
            offset_from_end++;

        case ',':
            color.pop_back();
            break;
        }

        // Assign number to correct color
        auto it = game.end() - offset_from_end;
        if (color == "red")
        {
            it->red = number;
        }
        else if (color == "blue")
        {
            it->blue = number;
        }
        else if (color == "green")
        {
            it->green = number;
        }
    }

    return game_number;
}

bool IsGamePossible(const std::vector<Cubes> &game)
{
    const Cubes max = {12, 14, 13};
    for (auto it = game.begin(); it != game.end(); it++)
    {
        if (*it > max)
        {
            return false;
        }
    }

    return true;
}
