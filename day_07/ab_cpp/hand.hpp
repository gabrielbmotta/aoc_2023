#ifndef HAND_HPP
#define HAND_HPP

#include <array>
#include <string>

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

    static const std::array<char, 13> suits;

    std::array<int, 5> hand;
    int bid;

    Type type;
    int type_suit;
    int type_suit_secondary;

    std::array<int, 5>::iterator UpdateType(std::array<int, 5>::iterator);

public:
    Hand(const std::string &, int);

    Hand(const std::string &, const std::string &);

    int GetBid();

    friend bool operator<(const Hand &, const Hand &);

    friend bool operator>(const Hand &, const Hand &);
};

#endif // HAND_HPP
