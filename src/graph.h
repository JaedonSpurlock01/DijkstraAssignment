#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <algorithm>

class CityNode
{
private:
    std::string _ID = "";
    std::string _city_code = "";
    std::string _city_name = "";
    unsigned int _population = -1;
    int _elevation = -1;
    int _total_neighbors = 0;
    std::list<std::pair<CityNode *, unsigned>> neighbors;

public:
    CityNode(std::string id, std::string code, std::string name, unsigned int ppl, int elevation)
    {
        this->_city_code = code;
        this->_city_name = name;
        this->_ID = id;
        this->_population = ppl;
        this->_elevation = elevation;
    }
    void add_neighbor(std::pair<CityNode *, unsigned> new_edge)
    {
        this->neighbors.push_back(new_edge);
        this->_total_neighbors++;
    }
    std::list<std::pair<CityNode *, unsigned>> fetch_neighbors() { return this->neighbors; }
    std::string fetch_city_name() { return this->_city_name; }
    void delete_neighbor(CityNode *city) { this->delete_neighbor_at(this->search_neighbor(city)); }
    std::pair<CityNode *, unsigned> get_neighbor(CityNode *city) { return this->get_neighbor_at(this->search_neighbor(city)); }
    int get_total_neighbors() { return this->_total_neighbors; }
    std::string get_id() { return this->_ID; }
    std::string get_city_code() { return this->_city_code; }
    std::string get_city_name() const { return this->_city_name; }
    unsigned int get_population() const { return this->_population; }
    int get_elevation() const { return this->_elevation; }
    std::pair<CityNode *, unsigned> get_neighbor_at(int index);
    int search_neighbor(CityNode *city);
    bool delete_neighbor_at(int index);
};

class CityGraph
{
private:
    // A city code (e.g. AB, AN, CN) maps to a city node
    std::unordered_map<std::string, CityNode *> listCities;
    std::unordered_map<std::string, std::string> id_to_code;

public:
    void add_city(std::string id, std::string code, std::string name, unsigned int ppl, int elevation);
    void add_multiple_cities(std::vector<std::vector<std::string>> list_of_cities);
    void delete_city(std::string id);
    void add_connection(unsigned from_city_id, unsigned to_city_id, unsigned distance);
    void add_multiple_connections(std::vector<std::vector<unsigned>> list_of_routes);
    void delete_connection(std::string source_city_code, std::string target_city_code);
    bool search_by_city_id(std::string id);
    bool search_by_city(CityNode *ctr);
    void print_neighbors(std::string target_city_code);
    void print_shortest_path_between(std::string source_city_code, std::string target_city_code);
    std::pair<std::vector<std::string>, unsigned> find_shortest_path_between(CityNode *source_city, CityNode *target_city);
    std::vector<std::string> construct_shortest_path(std::unordered_map<CityNode *, CityNode *> previous_city, CityNode *source_city, CityNode *target_city);
};