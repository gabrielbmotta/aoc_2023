#ifndef SEED_MAPPER_HPP
#define SEEED_MAPPER_HPP

#include <seed_map.hpp>

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class SeedMapper
{
    std::ifstream almanac;
    std::vector<unsigned> seeds;
    std::map<unsigned, unsigned> locations;
    std::map<std::string, std::tuple<std::string, SeedMap>> maps;

    void ReadMaps();

    unsigned LocateSeed(unsigned);

public:
    SeedMapper(const char *);

    void BuildMaps();

    void GetLocations();

    unsigned GetLowestLocation();
};

#endif // SEED_MAPPER_HPP
