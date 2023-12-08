#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

typedef std::unordered_map<char, int> Ruleset;

class Card{
public:
    Card(char card_symbol):_symbol(card_symbol){};

    friend bool operator==(const Card& c1, const Card& c2);
    friend bool operator!=(const Card& c1, const Card& c2);
    friend bool operator<(const Card& c1, const Card& c2);
    friend bool operator>(const Card& c1, const Card& c2);
    friend bool operator<=(const Card& c1, const Card& c2);
    friend bool operator>=(const Card& c1, const Card& c2);

    int value() const {return _value;};
    char symbol() const {return _symbol;};

    void scoreCard(){_value = _ruleset[_symbol];};

    void print() const {
        std::cout << _symbol;
    }

    static void setRules(const Ruleset& rules){_ruleset = rules;};

private:
    char _symbol;
    int _value;

    static Ruleset _ruleset;
};

Ruleset Card::_ruleset = {};

bool operator==(const Card& c1, const Card& c2) {return c1._value == c2._value;};
bool operator!=(const Card& c1, const Card& c2) {return c1._value != c2._value;};
bool operator<(const Card& c1, const Card& c2) {return c1._value < c2._value;};
bool operator>(const Card& c1, const Card& c2) {return c1._value > c2._value;};
bool operator<=(const Card& c1, const Card& c2) {return c1._value <= c2._value;};
bool operator>=(const Card& c1, const Card& c2) {return c1._value >= c2._value;};

class Hand{
public:
    Hand(int size=6){_cards.reserve(size);};

    friend bool operator==(const Hand& c1, const Hand& c2);
    friend bool operator!=(const Hand& c1, const Hand& c2);
    friend bool operator<(const Hand& c1, const Hand& c2);
    friend bool operator>(const Hand& c1, const Hand& c2);
    friend bool operator<=(const Hand& c1, const Hand& c2);
    friend bool operator>=(const Hand& c1, const Hand& c2);

    void addCard(const Card& card){_cards.emplace_back(card);};
    void addCard(Card&& card){_cards.emplace_back(card);};

    void setWager(int wager){_wager = wager;};
    int wager() const {return _wager;};

    void scoreHand(char joker = ' '){
        for(auto& card : _cards){
            card.scoreCard();
        }
        std::unordered_map<char, int> cardCount;
        for (const auto& card : _cards){
            if(cardCount.find(card.symbol()) != cardCount.end()){
                cardCount[card.symbol()] += 1;
            } else {
                cardCount.insert({card.symbol(), 1});
            }
        }

        auto max_map_value = [](const auto &x, const auto &y){return x.second < y.second;};

        if(joker != ' '){
            auto jok_ind = cardCount.find(joker);
            if(jok_ind != cardCount.end()){
                int joker_num = jok_ind->second;
                if(joker_num != _cards.size()){ // <- if hand is all jokers, we do nothing.
                    cardCount.extract(jok_ind);
                    auto highest_tuple = std::max_element(cardCount.begin(), cardCount.end(), max_map_value);
                    int new_high = highest_tuple->second + joker_num;
                    cardCount[highest_tuple->first] = new_high;
                }
            }
        }

        // Full house (3 + 2)
        auto highest_tuple = std::max_element(cardCount.begin(), cardCount.end(), max_map_value);
        int score = 10 * (highest_tuple->second);
        if (highest_tuple->second == 3){
            cardCount.extract(highest_tuple);
            auto second_highest = std::max_element(cardCount.begin(), cardCount.end(), max_map_value)->second;
            if(second_highest == 2){
                score += 1;
            }
        }
        // Two pair (2 + 2)
        if (highest_tuple->second == 2){
            cardCount.extract(highest_tuple);
            auto second_highest = std::max_element(cardCount.begin(), cardCount.end(), max_map_value)->second;
            if(second_highest == 2){
                score += 1;
            }
        }
        _score = score;
    }

    int score() const {return _score;};

    void print() const {
        for(const auto& card : _cards){
            card.print();
            std::cout << " ";
        }
    }

private:
    std::vector<Card> _cards;
    int _wager;
    int _score;
};

bool operator==(const Hand& h1, const Hand& h2){ return h1._cards == h2._cards; };
bool operator!=(const Hand& h1, const Hand& h2){ return h1._cards != h2._cards; };

bool operator<(const Hand& h1, const Hand& h2){
    if(h1._score != h2._score){
        return h1._score < h2._score;
    }
	return h1._cards < h2._cards;
};

bool operator>(const Hand& h1, const Hand& h2){
    if(h1._score != h2._score){
        return h1._score > h2._score;
    }
	return h1._cards > h2._cards;
};

bool operator<=(const Hand& h1, const Hand& h2){
    if(h1._score != h2._score){
        return h1._score <= h2._score;
    }
	return h1._cards <= h2._cards;
};

bool operator>=(const Hand& h1, const Hand& h2){
    if(h1._score != h2._score){
        return h1._score >= h2._score;
    }
	return h1._cards >= h2._cards;
};

std::vector<Hand> loadHands(std::istream& input){
    std::vector<Hand> hands;
    std::string line;
    while(std::getline(input, line)){
        hands.emplace_back(Hand());
        int ind = 0;
        for(char c : line){
            if(c == ' '){
                break;
            }
            ++ind;
            hands.back().addCard({c});
        }
        int wager = std::stoi(line.substr(ind + 1));
        hands.back().setWager(wager);
    }
    return hands;
}

int scoreHands(std::vector<Hand>& hands, const Ruleset& rules, char joker=' '){
    Card::setRules(rules);
    for(auto& hand : hands){
        hand.scoreHand(joker);
    }

    std::sort(hands.begin(), hands.end());
    long int runningScore = 0;
    for(int i = 0; i < hands.size(); ++i){
        runningScore += (i + 1) * hands[i].wager();
    }

    return runningScore;
}

const Ruleset partOneRules {
    {'A', 14}, {'K', 13}, {'Q', 12},
    {'J', 11}, {'T', 10}, {'9', 9},
    {'8', 8},  {'7', 7},  {'6', 6},
    {'5', 5},  {'4', 4},  {'3', 3},
    {'2', 2}
};

const Ruleset partTwoRules {
    {'A', 14}, {'K', 13}, {'Q', 12},
    {'T', 10}, {'9', 9},  {'8', 8},
    {'7', 7},  {'6', 6},  {'5', 5},
    {'4', 4},  {'3', 3},  {'2', 2},
    {'J', 1}
};

int main(int argc, char* argv[])
{
    std::string inpath = argc > 1 ? argv[1] : "input.txt";
    auto infile = std::ifstream(inpath);
    if(!infile.is_open()){
        std::cerr << "Unable to open file.\n";
        return 1;
    }

    auto hands = loadHands(infile);

    int partOneScore = scoreHands(hands, partOneRules);
    std::cout << "Part 1: " << partOneScore << "\n";
    
    int partTwoScore = scoreHands(hands, partTwoRules, 'J');
    std::cout << "Part 2: " << partTwoScore << "\n";

    return 0;
}

