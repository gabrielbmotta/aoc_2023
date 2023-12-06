#include <algorithm>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

void loadSeedsAndMaps(std::ifstream& infile,
                      std::vector<long int>& seeds,
                      std::vector<std::vector<std::vector<long int>>>& maps);

long int traverseMaps(const std::vector<std::vector<std::vector<long int>>>& maps,
                      long int val);

int main()
{
    auto infile = std::ifstream("input.txt");
    if(!infile.is_open()){
        std::cerr << "Unable to open file.\n";
        return 1;
    }

    std::vector<long int> seeds;
    std::vector<std::vector<std::vector<long int>>> maps;

    loadSeedsAndMaps(infile, seeds, maps);
    
    long int minPart1 = INT64_MAX;
    for(const auto& seed : seeds){
        long int result = traverseMaps(maps, seed);
        if(result < minPart1){
            minPart1 = result;
        }
    }
    std::cout << "Part 1: " << minPart1 << "\n";
    
    std::vector<long int> resultsPart2(seeds.size() / 2, INT64_MAX);

    #pragma omp parallel for
    for(size_t i = 0; i < resultsPart2.size(); ++i){
        std::cout << "Processing " << seeds[i*2] << " size " << seeds[i*2 + 1] << "\n";
        for(long int j = seeds[i*2]; j < seeds[i*2] + seeds[i*2 + 1]; ++j){
            long int result = traverseMaps(maps, j);
            if(result < resultsPart2[i]){
                resultsPart2[i] = result;
            }
        }
    }

    long int minPart2 = *std::min_element(resultsPart2.begin(), resultsPart2.end());

    std::cout << "Part 2: " << minPart2 << "\n";
    return 0;
}

void loadSeedsAndMaps(std::ifstream& infile,
                      std::vector<long int>& seeds,
                      std::vector<std::vector<std::vector<long int>>>& maps)
{
    std::string line;
    std::getline(infile, line);
    line = line.substr(line.find(':') + 1);
    std::stringstream stream{line};
    long int seed;

    while(stream >> seed){
        seeds.push_back(seed);
    }

    while(std::getline(infile, line)){
        if(line.empty()){
            maps.push_back({});
            continue;
        } else if(!std::isdigit(line.front())){
            continue;
        }
        std::vector <long int> entry;
        entry.reserve(3);
        std::stringstream entry_stream(line);
        long int val;

        while(entry_stream >> val){
            entry.push_back(val);
        }

        maps.back().push_back(entry);
    }
}


long int traverseMaps(const std::vector<std::vector<std::vector<long int>>>& maps,
                      long int val)
{
    for(const auto& mp : maps){
        bool found = false;
        for (const auto& en : mp){
            if(val>= en[1] && val < en[1] + en[2]){
                val = val - en[1] + en[0];
                break;
            }
        }
    }

    return val;
}

