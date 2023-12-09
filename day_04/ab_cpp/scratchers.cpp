#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <fstream>

int PlayScratchers(const std::string &);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Expected exactly one argument" << std::endl;
        return EXIT_FAILURE;
    }

    std::fstream input(argv[1]);
    std::string card;
    // auto points = 0;
    std::vector<int> number_of_cards;
    auto game_number = 0;
    while (std::getline(input, card))
    {
        if (number_of_cards.size() == game_number)
        {
            number_of_cards.push_back(1);
        }

        auto cards = PlayScratchers(card);
        while (number_of_cards.size() < game_number + cards + 1)
        {
            number_of_cards.push_back(1);
        }

        for (auto i = game_number + 1; i < game_number + cards + 1; i++)
        {
            number_of_cards[i] += number_of_cards[game_number];
        }

        game_number++;
    }

    auto sum = 0;
    for (auto it = number_of_cards.begin(); it != number_of_cards.end(); it++)
    {
        sum += *it;
    }
    std::cout << "Total cards: " << sum << std::endl;
}

int PlayScratchers(const std::string &card)
{
    // Convert to stream, but skip card ID
    auto colon_pos = card.find(":");
    if (colon_pos == std::string::npos)
    {
        colon_pos = 0;
    }
    else
    {
        colon_pos += 1;
    }
    std::stringstream buf(card.substr(colon_pos));

    // Get winning numbers
    std::vector<int> winning_numbers;
    std::string str;
    buf >> str;
    while (str != "|")
    {
        winning_numbers.push_back(std::stoi(str));
        buf >> str;
    }

    // Now look at what we have
    // auto points = 0;
    auto cards = 0;
    while (std::getline(buf, str, ' '))
    {
        if (str.empty())
        {
            continue;
        }

        auto number = std::stoi(str);

        for (auto it = winning_numbers.begin(); it != winning_numbers.end(); it++)
        {
            if (number == *it)
            {
                cards++;
                // if (points == 0)
                // {
                //     points = 1;
                // }
                // else
                // {
                //     points *= 2;
                // }
            }
        }
    }

    // return points;
    return cards;
}
