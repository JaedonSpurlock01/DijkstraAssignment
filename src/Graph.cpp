#include <stdio.h>
#include <string>
#include <vector>

using namespace std; 


class CityNode {
    
    private:

    string _ID = ""; //ID, City_Code(2 letters), City_Name, Population, and Elevation.
    string _city_code = "";
    string _city_name = "";
    unsigned int _population = -1; 
    int _elevation = -1; 
    int shortest_distance = NULL;

    public:
    
};


class CityGraph {
   
   private:
   vector<CityNode> NodeList;
   
   public:

   void add_node(CityNode* node){

   }

   void delete_node(){

   }



};