#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include "graph.h"

/**
 * @brief Get a reference of the neighbor referenced at the index in the list,
 *        returns a tuple (CityNode, Distance to CityNode)
 */
std::pair<CityNode *, unsigned> CityNode::get_neighbor_at(int index)
{
   int i = 0;
   for (auto it = this->neighbors.begin(); it != this->neighbors.end(); it++, i++)
   {
      // std::cout << "Neighbor: " << it->first << ", Distance: " << it->second << std::endl;
      if (i == index)
         return *it;
   }
}

/**
 * @brief Iterate through the neighbors list and return the index it exists at,
 *        if it doesn't exist return -1
 */
int CityNode::search_neighbor(CityNode *city)
{

   int index = 0;
   for (auto it = this->neighbors.begin(); it != this->neighbors.end(); it++, index++)
   {
      // std::cout << "Neighbor: " << it->first << ", Distance: " << it->second << std::endl;

      if (it->first == city)
      {
         return index;
      }
   }

   return -1;
}

/**
 * @brief Delete the neighbor in the list referenced at the index
 */
bool CityNode::delete_neighbor_at(int index)
{

   int i = 0;
   for (auto it = this->neighbors.begin(); it != this->neighbors.end(); ++it, ++i)
   {
      if (i == index)
      {
         this->neighbors.erase(it); // Erase the element at the iterator position
         return true;
      }
   }

   return false;
}

/**
 * @brief Add a city to the list of cities
 */
void CityGraph::add_city(std::string id, std::string code, std::string name, unsigned int ppl, int elevation)
{
   CityNode *city = new CityNode(id, code, name, ppl, elevation);
   listCities[code] = city;
   id_to_code[id] = code;
}

/**
 * @brief Add multiple cities to the list of cities using a parsed string file
 */
void CityGraph::add_multiple_cities(std::vector<std::vector<std::string>> list_of_cities)
{
   for (const auto &city : list_of_cities)
   {
      std::string id = city.at(0);
      std::string code = city.at(1);
      std::string name = city.at(2);
      unsigned population = std::stoi(city.at(3));
      int elevation = std::stoi(city.at(4));

      this->add_city(id, code, name, population, elevation);
   }
}

/**
 * @brief Delete the city referenced by its id (letter code)
 */
void CityGraph::delete_city(std::string id)
{
   // Given a list, must delete a node using a id.
   CityNode *city = this->listCities[id];

   int neighbors = city->get_total_neighbors();

   for (int i = 0; i < neighbors; i++)
   {
      city->get_neighbor_at(i).first->delete_neighbor(city);
   }

   for (int i = 0; i < neighbors; i++)
   {
      city->delete_neighbor_at(i);
   }

   delete city;
}

/**
 * @brief Add a weighted edge between two cities
 */
void CityGraph::add_connection(unsigned from_city_id, unsigned to_city_id, unsigned distance)
{
   std::string from_city_code = this->id_to_code[std::to_string(from_city_id)];
   std::string to_city_code = this->id_to_code[std::to_string(to_city_id)];

   CityNode *from_city = this->listCities[from_city_code];
   CityNode *to_city = this->listCities[to_city_code];

   // Create a tuple with the qualities (target, weight)
   auto new_edge = std::make_pair(to_city, distance);

   // Add new connection to source node (directed-graph, so we don't need to do same for target node)
   from_city->add_neighbor(new_edge);
}

/**
 * @brief Add multiple weighted edges given by a parsed file
 */
void CityGraph::add_multiple_connections(std::vector<std::vector<unsigned>> list_of_routes)
{
   for (const auto &route : list_of_routes)
   {
      unsigned from_city = route.at(0);
      unsigned to_city = route.at(1);
      unsigned distance = route.at(2);

      this->add_connection(from_city, to_city, distance);
   }
}

/**
 * @brief Delete a weighted edge from source to target (directed graph)
 */
void CityGraph::delete_connection(std::string source_city_code, std::string target_city_code)
{
   // IMPLEMENT: Given two nodes erase the connection between them. Iterate thru source's neighbors to find target and reset it to something else

   CityNode *source = this->listCities[source_city_code];
   CityNode *target = this->listCities[target_city_code];

   int index = source->search_neighbor(target);
   if (index > -1)
   {
      source->delete_neighbor_at(index);
   }
}

/**
 * @brief Search a city by its id (letter code) and return true if it exists, false otherwise
 */
bool CityGraph::search_by_city_id(std::string id)
{
   for (const auto &city : this->listCities)
   {
      if (city.first == id)
      {
         return true;
      }
   }
   return false;
}

/**
 * @brief Search a city by its object (letter code) and return true if it exists, false otherwise
 */
bool CityGraph::search_by_city(CityNode *ctr)
{
   for (const auto &city : this->listCities)
   {
      if (city.second == ctr)
      {
         return true;
      }
   }
   return false;
}

/**
 * @brief Print the neighbors of a given city's id (letter code)
 */
void CityGraph::print_neighbors(std::string target_city_code)
{
   if (listCities.find(target_city_code) == listCities.end())
   {
      std::cout << "City with code " << target_city_code << " is invalid." << std::endl;
      return;
   }

   CityNode *city = this->listCities[target_city_code];

   for (const auto &neighbor : city->fetch_neighbors())
   {
      std::cout << neighbor.first->fetch_city_name() << " " << std::endl;
   }
   std::cout << "\n";
}

/**
 * @brief Print the shortest weighted route between two cities
 */
void CityGraph::print_shortest_path_between(std::string source_city_code, std::string target_city_code)
{
   // Grab the references to each city
   CityNode *source_city = this->listCities[source_city_code];
   CityNode *target_city = this->listCities[target_city_code];

   std::cout << "From City: " << source_city->fetch_city_name() << "\n";
   std::cout << "To City: " << target_city->fetch_city_name() << "\n\n";

   // Find the shortest path between source and target
   std::pair<std::vector<std::string>, unsigned> shortest_path_collection = find_shortest_path_between(source_city, target_city);
   std::vector<std::string> shortest_path = shortest_path_collection.first;
   unsigned shortest_distance = shortest_path_collection.second;

   // Print out the shortest route from the source city to the target city
   if (!shortest_path.size())
   {
      std::cout << "No route from " << source_city->fetch_city_name() << " to " << target_city->fetch_city_name() << "\n";
   }
   else
   {
      std::cout << "The shortest distance from " << source_city->fetch_city_name() << " to " << target_city->fetch_city_name() << " is " << std::to_string(shortest_distance) << "\n";
      std::string route;
      for (std::string city : shortest_path)
      {
         route.append(city);
         route.append("->");
      }
      route.erase(route.length() - 2);

      std::cout << route << "\n";
   }
}

/**
 * @brief Find the shortest weighted route between two cities, returns a tuple (path between cities, tentative distance)
 */
std::pair<std::vector<std::string>, unsigned> CityGraph::find_shortest_path_between(CityNode *source_city, CityNode *target_city)
{
   std::priority_queue<std::pair<unsigned, CityNode *>, std::vector<std::pair<unsigned, CityNode *>>, std::greater<std::pair<unsigned, CityNode *>>> cities_to_visit;
   std::unordered_set<CityNode *> cities_visited;
   std::unordered_map<CityNode *, unsigned> distance_from_source;
   std::unordered_map<CityNode *, CityNode *> previous_city;

   // Set all distances to infinity and previous to null
   for (const auto &city : this->listCities)
   {
      distance_from_source[city.second] = 999999;
      previous_city[city.second] = nullptr;
   }

   // Add the source to the queue to start Dijkstra's Algorithm
   distance_from_source[source_city] = 0;
   cities_to_visit.push(std::make_pair(0, source_city));

   while (cities_to_visit.size())
   {
      // Remove the current city from the queue
      CityNode *current_city = cities_to_visit.top().second;
      cities_to_visit.pop();

      // Add city to the visited set
      cities_visited.insert(current_city);

      // If the target city is found
      if (current_city == target_city)
      {
         std::vector<std::string> shortest_path = construct_shortest_path(previous_city, source_city, target_city);
         unsigned shortest_path_distance = distance_from_source[target_city];
         return make_pair(shortest_path, shortest_path_distance);
      }

      // Process each current city's neighbor
      for (const auto &neighbor_pair : current_city->fetch_neighbors())
      {
         CityNode *neighbor = neighbor_pair.first;
         unsigned distance_to_neighbor = neighbor_pair.second;

         if (cities_visited.find(neighbor) == cities_visited.end())
         {
            unsigned distance_to_neighbor_from_source = distance_from_source[current_city] + distance_to_neighbor;

            // Relaxation of nodes
            if (distance_to_neighbor_from_source < distance_from_source[neighbor])
            {
               distance_from_source[neighbor] = distance_to_neighbor_from_source;
               previous_city[neighbor] = current_city;
               cities_to_visit.push(std::make_pair(distance_to_neighbor_from_source, neighbor));
            }
         }
      }
   }

   // Return nothing if a route doesn't exist
   return {};
}

/**
 * @brief Create a vector of strings containing the path from the source city to the target city
 */
std::vector<std::string> CityGraph::construct_shortest_path(std::unordered_map<CityNode *, CityNode *> previous_city, CityNode *source_city, CityNode *target_city)
{
   std::vector<std::string> shortest_path;

   // Start at the target node and traverse backwards through shortest path
   CityNode *current_city = target_city;

   // Traverse through the shortest path, and append the city name to the shortest path
   while (current_city != nullptr)
   {
      shortest_path.push_back(current_city->fetch_city_name());
      current_city = previous_city[current_city];
   }

   // The shortest path is backwards, so reverse it before returning it
   std::reverse(shortest_path.begin(), shortest_path.end());
   return shortest_path;
}