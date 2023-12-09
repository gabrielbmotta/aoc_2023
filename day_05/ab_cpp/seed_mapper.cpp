#include <seed_mapper.hpp>

SeedMapper::SeedMapper(const char *almanac_name) : almanac{almanac_name}
{
    // Check that seed keyword ("seeds:") is there
    std::string seed_keyword;
    almanac >> seed_keyword;
    if (seed_keyword != "seeds:")
    {
        throw std::invalid_argument("almanac doesn't start with list of seeds");
    }

    // Get the list of seeds from it
    unsigned seed;
    while (!almanac.fail())
    {
        almanac >> seed;
        if (!almanac.fail())
        {
            seeds.push_back(seed);
        }
    }

    // Clear error states
    almanac.clear();
}

void SeedMapper::BuildMaps()
{
    // Keep reading while there's still more to read
    while (!almanac.eof())
    {
        ReadMaps();
    }

    // Close the almanac
    almanac.close();
}

unsigned SeedMapper::GetLowestLocation()
{
    unsigned location = -1;
    for (auto it = seeds.begin(); it != seeds.end(); it += 2)
    {
        auto last_seed = *it + *(it + 1);
        for (auto seed = *it; seed < last_seed; seed++)
        {
            auto new_location = LocateSeed(seed);
            if (location > new_location)
            {
                location = new_location;
            }
        }
    }

    return location;
}

void SeedMapper::ReadMaps()
{
    // Get map name
    std::string map_name;
    while (map_name.empty())
    {
        almanac >> map_name;

        // To avoid infinite loop, return immediately if EOF is reached
        if (almanac.eof())
        {
            return;
        }
    }

    // Split map name by dash
    std::vector<std::string> map_name_parts;
    size_t offset = 0;
    size_t pos = 0;
    while (pos != std::string::npos)
    {
        // Determine substring length
        pos = map_name.find("-", offset);
        auto count = pos == std::string::npos ? std::string::npos : pos - offset;

        // Copy substring
        map_name_parts.push_back(map_name.substr(offset, count));
        offset += count + 1;
    }

    // Check that the parsed map name is valid
    if (map_name_parts.size() != 3 || map_name_parts[1] != "to")
    {
        throw std::invalid_argument("bad map name");
    }

    // Check that the map is, indeed, a map
    almanac >> map_name;
    if (map_name != "map:")
    {
        throw std::invalid_argument("no map name");
    }

    // Initialize map
    maps[map_name_parts[0]] = {map_name_parts[2], {}};

    // Add ranges to map
    std::array<unsigned, 3> range;
    auto it = range.begin();
    while (!almanac.fail())
    {
        // Get next range
        almanac >> *it;
        it++;

        // If all ranges have been read, add it to the map
        if (it == range.end())
        {
            std::get<SeedMap>(maps[map_name_parts[0]]).AddRange(range[0], range[1], range[2]);
            it = range.begin();
        }
    }

    // Clear error states
    almanac.clear();

    return;
}

unsigned SeedMapper::LocateSeed(unsigned seed)
{
    std::string source = "seed";
    unsigned location = seed;
    while (source != "location")
    {
        location = std::get<SeedMap>(maps[source]).MapSource(location);
        source = std::get<std::string>(maps[source]);
    }

    return location;
}
