#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

class CityNode
{

private:
   string _ID = "";
   string _city_code = "";
   string _city_name = "";
   unsigned int _population = -1;
   int _elevation = -1;
   int _total_neighbors = 0;

   /*
    * [IMPORTANT]
    *  Linked-list of neighbors
    *  Each node in the list has a tuple with (neighbor, distance_to_neighbor)
    */
   list<pair<CityNode *, unsigned>> neighbors;

public:
   CityNode(string id, string code, string name, unsigned int ppl, int elevation)
   {
      this->_city_code = code;
      this->_city_name = name;
      this->_ID = id;
      this->_population = ppl;
      this->_elevation = elevation;
   }

   list<pair<CityNode *, unsigned>> fetch_neighbors()
   {
      return this->neighbors;
   }

   std::string fetch_city_name()
   {
      return this->_city_name;
   }

   pair<CityNode *, unsigned> get_neighbor_at(int index)
   {

      int i = 0;
      for (auto it = this->neighbors.begin(); it != this->neighbors.end(); it++, i++)
      {
         // std::cout << "Neighbor: " << it->first << ", Distance: " << it->second << std::endl;
         if (i == index)
            return *it;
      }
   }

   int search_neighbor(CityNode *city)
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

   bool delete_neighbor_at(int index)
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

   void delete_neighbor(CityNode *city)
   {
      this->delete_neighbor_at(this->search_neighbor(city));
   }

   pair<CityNode *, unsigned> get_neighbor(CityNode *city)
   {
      return this->get_neighbor_at(this->search_neighbor(city));
   }

   void add_neighbor(pair<CityNode *, unsigned> new_edge)
   {
      this->neighbors.push_back(new_edge);
      this->_total_neighbors++;
   }

   int get_total_neighbors()
   {
      return this->_total_neighbors;
   }

   string get_id()
   {
      return this->_ID;
   }

   string get_city_code()
   {
      return this->_city_code;
   }

   string get_city_name()
   {
      return this->_city_name;
   }

   unsigned int get_population()
   {
      return this->_population;
   }

   int get_elevation()
   {
      return this->_elevation;
   }
};

/**
 * [IMPORTANT]
 *
 * 1) Sketch details of well thought OOP outline of the Graph data structure with every possible function
 * 2) Break down code in functions in such a way that any team member can collaborate to complete this without needing to grasp full picture.
 * 3) Label each function and make commits for each function completed.
 */
class CityGraph
{
private:
   // A city code (e.g. AB, AN, CN) maps to a city node
   unordered_map<string, CityNode *> NodeList;
   unordered_map<string, string> id_to_code;

public:
   // Add a city to the list of cities
   void add_city(string id, string code, string name, unsigned int ppl, int elevation)
   {
      CityNode *city = new CityNode(id, code, name, ppl, elevation);
      NodeList[code] = city;
      id_to_code[id] = code;
   }

   // Remove the city from the list of cities
   void delete_city(string id)
   {
      // Given a list, must delete a node using a id.
      CityNode *city = this->NodeList[id];

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

   // Add a route between cities
   void add_connection(unsigned from_city_id, unsigned to_city_id, unsigned distance)
   {
      std::string from_city_code = this->id_to_code[to_string(from_city_id)];
      std::string to_city_code = this->id_to_code[to_string(to_city_id)];

      CityNode *from_city = this->NodeList[from_city_code];
      CityNode *to_city = this->NodeList[to_city_code];

      // Create a tuple with the qualities (target, weight)
      auto new_edge = make_pair(to_city, distance);

      // Add new connection to source node (directed-graph, so we don't need to do same for target node)
      from_city->add_neighbor(new_edge);
   }

   // Remove a route between cities (HARD, requires removal from list)
   void delete_connection(string source_city_code, string target_city_code)
   {
      // IMPLEMENT: Given two nodes erase the connection between them. Iterate thru source's neighbors to find target and reset it to something else

      CityNode *source = this->NodeList[source_city_code];
      CityNode *target = this->NodeList[target_city_code];

      int index = source->search_neighbor(target);
      if (index > -1)
      {
         source->delete_neighbor_at(index);
      }
   }

   bool search_by_city_id(string id)
   {
      //[IMPLEMENT]: Given a string id traverse through NodeList structure to find a match
      for (const auto &city : this->NodeList)
      {
         if (city.first == id)
         {
            return true;
         }
      }
      return false;
   }

   bool search_by_city(CityNode *ctr)
   {
      //[IMPLEMENT]: Given a *ptr traverse thru nodelist structure to find a match
      for (const auto &city : this->NodeList)
      {
         if (city.second == ctr)
         {
            return true;
         }
      }
      return false;
   }

   void print_neighbors(string target_city_code)
   {
      if (NodeList.find(target_city_code) == NodeList.end())
      {
         std::cout << "City with code " << target_city_code << " is invalid." << std::endl;
         return;
      }

      CityNode *city = this->NodeList[target_city_code];

      for (const auto &neighbor : city->fetch_neighbors())
      {
         std::cout << neighbor.first->fetch_city_name() << " " << endl;
      }
      std::cout << "\n";
   }

   void print_shortest_path_between(string source_city_code, string target_city_code)
   {
      // Grab the references to each city
      CityNode *source_city = this->NodeList[source_city_code];
      CityNode *target_city = this->NodeList[target_city_code];

      std::cout << "From City: " << source_city->fetch_city_name() << "\n";
      std::cout << "To City: " << target_city->fetch_city_name() << "\n\n";

      // Find the shortest path between source and target
      std::pair<vector<std::string>, unsigned> shortest_path_collection = find_shortest_path_between(source_city, target_city);
      std::vector<std::string> shortest_path = shortest_path_collection.first;
      unsigned shortest_distance = shortest_path_collection.second;

      // Print out the shortest route from the source city to the target city
      if (!shortest_path.size())
      {
         std::cout << "No route from " << source_city->fetch_city_name() << " to " << target_city->fetch_city_name() << "\n";
      }
      else
      {
         std::cout << "The shortest distance from " << source_city->fetch_city_name() << " to " << target_city->fetch_city_name() << " is " << to_string(shortest_distance) << "\n";
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

   std::pair<std::vector<std::string>, unsigned> find_shortest_path_between(CityNode *source_city, CityNode *target_city)
   {
      priority_queue<pair<unsigned, CityNode *>, vector<pair<unsigned, CityNode *>>, greater<pair<unsigned, CityNode *>>> cities_to_visit;
      unordered_set<CityNode *> cities_visited;
      unordered_map<CityNode *, unsigned> distance_from_source;
      unordered_map<CityNode *, CityNode *> previous_city;

      // Set all distances to infinity and previous to null
      for (const auto &city : this->NodeList)
      {
         distance_from_source[city.second] = 999999;
         previous_city[city.second] = nullptr;
      }

      // Add the source to the queue to start Dijkstra's Algorithm
      distance_from_source[source_city] = 0;
      cities_to_visit.push(make_pair(0, source_city));

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
            vector<std::string> shortest_path = construct_shortest_path(previous_city, source_city, target_city);
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
                  cities_to_visit.push(make_pair(distance_to_neighbor_from_source, neighbor));
               }
            }
         }
      }

      // Return nothing if a route doesn't exist
      return {};
   }

   std::vector<std::string> construct_shortest_path(unordered_map<CityNode *, CityNode *> previous_city, CityNode *source_city, CityNode *target_city)
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
};