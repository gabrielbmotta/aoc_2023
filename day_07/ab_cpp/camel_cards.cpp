#include <camel_cards.hpp>
#include <hand.hpp>

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#ifdef _DEBUG
#include <cstdio>
#endif // _DEBUG

int camel_cards::WinCamelCards(const char *input)
{
    std::ifstream buf(input);
    std::string line;
    std::vector<Hand> hands;

    while (std::getline(buf, line))
    {
        hands.push_back({line.substr(0, 5), line.substr(6)});
    }

    std::sort(hands.begin(), hands.end());

#ifdef _DEBUG
    std::remove("debug");
#endif // _DEBUG

    auto score = 0;
    for (auto i = 0; i < hands.size(); i++)
    {
        score += hands[i].GetBid() * (i + 1);
    }

    return score;
}
