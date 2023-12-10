#include <hand.hpp>

#include <algorithm>
#include <stdexcept>

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
      type{HIGH_CARD},
      type_suit{0},
      type_suit_secondary{0}
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

    // Sort them
    std::sort(hand.begin(), hand.end(), std::greater<int>());

    // Determine hand type based on cards
    auto card = hand.begin();
    while (card != hand.end())
    {
        card = UpdateType(card);
    }
}

Hand::Hand(const std::string &new_hand, const std::string &new_bid)
    : Hand(new_hand, std::stoi(new_bid))
{
}

int Hand::GetBid()
{
        return bid;
}

bool operator<(const Hand &l, const Hand &r)
{
    if (l.type != r.type)
    {
        return l.type < r.type;
    }

    if (l.type_suit != r.type_suit)
    {
        return l.type_suit < r.type_suit;
    }

    // If both are a five of a kind and have the same suit, then they're the
    // same hand
    if (l.type == Hand::FIVE_OF_A_KIND)
    {
        return false;
    }

    // Only some types support secondary suits
    if (l.type_suit_secondary != r.type_suit_secondary && (l.type == Hand::FULL_HOUSE || l.type == Hand::TWO_PAIR))
    {
        return l.type_suit_secondary < r.type_suit_secondary;
    }

    // If both are a full house and have the same suits, then they're the same
    // hand
    if (l.type == Hand::FULL_HOUSE)
    {
        return false;
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

std::array<int, 5>::iterator Hand::UpdateType(std::array<int, 5>::iterator card)
{
    // Count number of times this card appears in the hand
    auto count = std::count(card, hand.end(), *card);

    // Handle each case
    switch (count)
    {
    case 5:
        type = FIVE_OF_A_KIND;
        type_suit = *card;

        // No room for any other hands
        return hand.end();

    case 4:
        type = FOUR_OF_A_KIND;
        type_suit = *card;

        // No room for any other hands
        return hand.end();

    case 3:
        // Could be a full house if a pair was already found
        if (type == ONE_PAIR)
        {
            type = FULL_HOUSE;

            // This suit is the primary one
            type_suit_secondary = type_suit;
            type_suit = *card;

            // No room for any other hands
            return hand.end();
        }

        // Regular three of a kind
        type = THREE_OF_A_KIND;
        type_suit = *card;
        break;

    case 2:
        // Could be a full house if a three of a kind was already found
        if (type == THREE_OF_A_KIND)
        {
            type = FULL_HOUSE;

            // This suit is the secondary one
            type_suit_secondary = *card;

            // No room for any other hands
            return hand.end();
        }

        // Could be a two pair if a pair was already found
        if (type == ONE_PAIR)
        {
            type = TWO_PAIR;

            // Check which pair is stronger
            if (*card > type_suit)
            {
                type_suit_secondary = type_suit;
                type_suit = *card;
            }
            else
            {
                type_suit_secondary = *card;
            }

            // No room for any other hands
            return hand.end();
        }

        // Regular one pair
        type = ONE_PAIR;
        type_suit = *card;
        break;

    case 1:
        // High card is the default, so no need to set it
        if (*card > type_suit && type == HIGH_CARD)
        {
            type_suit = *card;
        }
        break;
    }

    // Skip matches
    return card + count;
}
