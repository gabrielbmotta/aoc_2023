#ifndef SEED_MAPPER_HPP
#define SEEED_MAPPER_HPP

#include <seed_map.hpp>

#include <array>
#include <fstream>
#include <map>
#include <string>
#include <vector>

class SeedMapper
{
    std::ifstream almanac;
    std::vector<unsigned> seeds;
    std::map<std::string, std::tuple<std::string, SeedMap>> maps;

    void ReadMaps();

    unsigned LocateSeed(unsigned);

public:
    SeedMapper(const char *);

    void BuildMaps();

    unsigned GetLowestLocation();
};

#endif // SEED_MAPPER_HPP
