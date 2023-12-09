#ifndef SEED_MAP_HPP
#define SEED_MAP_HPP

#include <array>
#include <map>

class SeedMap
{
    std::map<unsigned, std::array<unsigned, 2>> seed_map;

public:
    SeedMap();

    void AddRange(unsigned, unsigned, unsigned);

    unsigned MapSource(unsigned);
};

#endif //SEED_MAP_HPP
