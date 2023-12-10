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
    '2', // lowest
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'T',
    'J',
    'Q',
    'K',
    'A' // highest
};

Hand::Hand(const std::string &new_hand, int new_bid)
    : bid{new_bid},
      type{HIGH_CARD}
{
    // Convert characters to suits
    for (auto i = 0; i < new_hand.size(); i++)
    {
        auto it = std::find(suits.begin(), suits.end(), new_hand[i]);
        if (it == suits.end())
        {
            throw std::invalid_argument("invalid card");
        }

        hand[i] = std::distance(suits.begin(), it);
    }

    std::vector<int> counted_cards;

    for (auto card = hand.begin(); card != hand.end(); card++)
    {
        UpdateType(card, counted_cards);
    }
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

void Hand::UpdateType(std::array<int, 5>::iterator card, std::vector<int> &counted_cards)
{
    if (std::find(counted_cards.begin(), counted_cards.end(), *card) != counted_cards.end() || type == FIVE_OF_A_KIND || type == FOUR_OF_A_KIND || type == FULL_HOUSE || type == TWO_PAIR)
    {
        return;
    }

    // Count number of times this card appears in the hand
    auto count = std::count(hand.begin(), hand.end(), *card);

    // Handle each case
    switch (count)
    {
    case 5:
        type = FIVE_OF_A_KIND;
        break;

    case 4:
        type = FOUR_OF_A_KIND;
        break;

    case 3:
        // Could be a full house if a pair was already found
        type = type == ONE_PAIR ? FULL_HOUSE : THREE_OF_A_KIND;
        break;

    case 2:
        // Could be a full house if a three of a kind was already found
        type = type == THREE_OF_A_KIND ? FULL_HOUSE : type == ONE_PAIR ? TWO_PAIR
                                                                       : ONE_PAIR;

        break;
    }

    counted_cards.push_back(*card);
    return;
}
