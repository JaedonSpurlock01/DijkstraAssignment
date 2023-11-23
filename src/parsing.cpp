#include <iostream>
#include <vector>
#include <fstream>
#include <string>

/**
 * @brief Parses a text file containing city data, returns an array of arrays,
 *        where each single array contains id, letter code, name, population, and elevation
 */
std::vector<std::vector<std::string>> parse_cities_file(std::istream &file)
{
    std::vector<std::vector<std::string>> cities;
    std::string id, code, name, population, elevation;

    while (file >> id >> code >> name >> population >> elevation)
    {
        std::vector<std::string> city;
        city.push_back(id);
        city.push_back(code);
        city.push_back(name);
        city.push_back(population);
        city.push_back(elevation);
        cities.push_back(city);
    }

    return cities;
}

/**
 * @brief Parses a text file containing route data, returns an array of arrays,
 *        where each single array contains from_city (source), to_city (target), distance (weight)
 */
std::vector<std::vector<unsigned>> parse_routes_file(std::istream &file)
{
    std::vector<std::vector<unsigned>> routes;
    unsigned from_city = 0, to_city = 0, distance = 0;

    while (file >> from_city >> to_city >> distance)
    {
        std::vector<unsigned> route;
        route.push_back(from_city);
        route.push_back(to_city);
        route.push_back(distance);
        routes.push_back(route);
    }

    return routes;
}