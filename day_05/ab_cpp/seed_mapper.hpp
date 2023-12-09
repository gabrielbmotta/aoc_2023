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
    std::vector<int> seeds;
    // std::vector<int> locations;
    std::map<int, int> locations;
    std::map<std::string, std::tuple<std::string, SeedMap>> maps;

    void ReadMaps();

    int LocateSeed(int);

public:
    SeedMapper(const char *);

    void BuildMaps();

    void GetLocations();

    int GetLowestLocation();
};

#endif // SEED_MAPPER_HPP
