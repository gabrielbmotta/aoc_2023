# CamelCardsWinner

This project solves the [Day 7](https://adventofcode.com/2023/day/7) puzzle on
[Advent of Code](https://adventofcode.com/). It determines the total winnings
from a set of Camel Cards hands ([the puzzle
input](https://adventofcode.com/2023/day/7/input)).

## Usage

This project provides a command-line executable, which expects a single
argument.

    CamelCardsWinner <list-of-hands>

In the above example, `<list-of-hands>` is a text file containing a list of
hands and bids. The program will print the total winnings of the list.

## Building

This project uses [CMake](https://cmake.org/) and can be built by invoking
[`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html).

## Testing

This project includes a unit test. It can be run by invoking
[`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html).

## License

This project is released under the same license of this repository.
