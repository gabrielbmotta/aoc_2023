#ifndef SEED_MAP_HPP
#define SEED_MAP_HPP

#include <array>
#include <map>

class SeedMap
{
    std::map<int, std::array<int, 2>> seed_map;

public:
    SeedMap();

    void AddRange(int, int, int);

    int MapSource(int);
};

#endif //SEED_MAP_HPP
