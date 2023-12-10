#ifndef HAND_HPP
#define HAND_HPP

#include <array>
#include <string>
#include <vector>

class Hand
{
    enum Type
    {
        HIGH_CARD,
        ONE_PAIR,
        TWO_PAIR,
        THREE_OF_A_KIND,
        FULL_HOUSE,
        FOUR_OF_A_KIND,
        FIVE_OF_A_KIND
    };

#ifdef _DEBUG
    static const std::array<std::string, FIVE_OF_A_KIND + 1> types;
#endif // _DEBUG

    static const std::array<char, 13> suits;

    std::array<int, 5> hand;
    int bid;

    Type type;

    void UpdateType(std::array<int, 5>::iterator, std::vector<int> &);

public:
    Hand(const std::string &, int);

    Hand(const std::string &, const std::string &);

    int GetBid();

    friend bool operator<(const Hand &, const Hand &);

    friend bool operator>(const Hand &, const Hand &);
};

#endif // HAND_HPP
