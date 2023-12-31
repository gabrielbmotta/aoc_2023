#include <seed_map.hpp>

SeedMap::SeedMap() {}

void SeedMap::AddRange(unsigned drs, unsigned srs, unsigned rl)
{
    seed_map[srs] = {drs, rl};
}

unsigned SeedMap::MapSource(unsigned source)
{
    auto it = seed_map.lower_bound(source);
    if (it == seed_map.end() || !(it->first == source || it == seed_map.begin()))
    {
        it--;
    }

    if (source >= it->first && (source - it->first < it->second[1]))
    {
        return source - (it->first - it->second[0]);
    }
    else
    {
        return source;
    }
}
