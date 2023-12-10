#include <hand.hpp>

#include <algorithm>
#include <stdexcept>

#ifdef _DEBUG
#include <fstream>
#include <iomanip>
#endif // _DEBUG

#ifdef _DEBUG
const std::array<std::string, Hand::FIVE_OF_A_KIND + 1> Hand::types = {
    "high card",
    "one pair",
    "two pair",
    "three of a kind",
    "full house",
    "four of a kind",
    "five of a kind"};
#endif // _DEBUG

const std::array<char, 13> Hand::suits = {
    'J', // lowest
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'T',
    'Q',
    'K',
    'A' // highest
};

Hand::Hand(const std::string &new_hand, int new_bid)
    : bid{new_bid},
      type{HIGH_CARD},
      jokers{0}
{
    // Convert characters to suits
    std::array<int, 13> count = {0};
    auto max_card = -1;
    for (auto i = 0; i < new_hand.size(); i++)
    {
        auto it = std::find(suits.begin(), suits.end(), new_hand[i]);
        if (it == suits.end())
        {
            throw std::invalid_argument("invalid card");
        }

        hand[i] = std::distance(suits.begin(), it);
        count[hand[i]]++;
        if (hand[i] != 0 && (max_card == -1 || count[hand[i]] > count[max_card]))
        {
            max_card = hand[i];
        }
    }

    // Get maximum number of any one card (along with jokers)
    auto max_count = count[0] + (max_card > 0 ? count[max_card] : 0);
    switch (max_count)
    {
    case 5:
        type = FIVE_OF_A_KIND;
        return;

    case 4:
        type = FOUR_OF_A_KIND;
        return;

    case 3:
        type = THREE_OF_A_KIND;
        break;

    case 2:
        type = ONE_PAIR;
        break;
    }

    // Clear it and jokers to avoid repeats
    if (max_count > 1)
    {
        count[max_card] = 0;
    }
    count[0] = 0;

    // Find any additional pairs
    if (std::find(count.begin(), count.end(), 2) != count.end())
    {
        switch (type)
        {
        case THREE_OF_A_KIND:
            type = FULL_HOUSE;
            break;

        case ONE_PAIR:
            type = TWO_PAIR;
            break;
        }
    }

    return;
}

Hand::Hand(const std::string &new_hand, const std::string &new_bid)
    : Hand(new_hand, std::stoi(new_bid))
{
}

int Hand::GetBid()
{
#ifdef _DEBUG
    std::ofstream debug("debug", std::ios::app);

    for (auto card = hand.begin(); card != hand.end(); card++)
    {
        debug << suits[*card];
    }

    debug << " "
          << std::setw(2) << bid << " "
          << types[type] << std::endl;
#endif // _DEBUG
    return bid;
}

bool operator<(const Hand &l, const Hand &r)
{
    if (l.type != r.type)
    {
        return l.type < r.type;
    }

    // Now just check which hand has the highest cards
    for (auto i = 0; i < l.hand.size(); i++)
    {
        if (l.hand[i] != r.hand[i])
        {
            return l.hand[i] < r.hand[i];
        }
    }

    // They're the same hand
    return false;
}

bool operator>(const Hand &l, const Hand &r)
{
    return !(l < r);
}
