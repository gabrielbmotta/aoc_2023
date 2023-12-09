# Day 4

This project solves the [Day 4](https://adventofcode.com/2023/day/4) puzzle on
[Advent of Code](https://adventofcode.com/). The goal is to compute the number
of points a collection of
[scratchcards](https://adventofcode.com/2023/day/4/input) are worth.

## Building

This project uses [CMake](https://cmake.org/). Create a build directory and
generate the project build system in it. For example:

    mkdir build; cd build
    cmake <path-to-project>

Then build it.

    cmake --build [--config <cfg>]

Note that multi-configuration tools (such as MSVC) require a configuration (ie.
`Debug` or `Release`) to be specified.

## Testing

From the build directory, run
[`ctest`](https://cmake.org/cmake/help/latest/manual/ctest.1.html).

    ctest [-C <cfg>]

Keep in mind that you need to specify the configuration for some tools.

## License

This project inherits the license of this repository.
