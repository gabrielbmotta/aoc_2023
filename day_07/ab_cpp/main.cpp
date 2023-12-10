#include <camel_cards.hpp>
#include <main.h>

#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "CamelCardsWinner v" << CAMEL_CARDS_WINNER_VERSION_MAJOR << "."
              << CAMEL_CARDS_WINNER_VERSION_MINOR << std::endl;

    if (argc != 2)
    {
        std::cerr << "Expected exactly one argument" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Total winnings: " << camel_cards::WinCamelCards(argv[1]) << std::endl;
}
