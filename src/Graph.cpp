#include <stdio.h>
#include <string>
#include <vector>

using namespace std; 


class CityNode {
    
    private:

    string _ID = ""; 
    string _city_code = "";
    string _city_name = "";
    unsigned int _population = -1; 
    int _elevation = -1; 
    int shortest_distance = NULL;

    public:
    
    CityNode(string id, string code, string name, unsigned int ppl, int elevation){
        this->_city_code = code; 
        this->_city_name = name; 
        this->_ID = id; 
        this->_population = ppl; 
        this->_elevation = elevation; 
    }

};

/**
 * [IMPORTANT]
 * 
 * 1) Sketch details of well thought OOP outline of the Graph data structure with every possible function
 * 2) Break down code in functions in such a way that any team member can collaborate to complete this without needing to grasp full picture. 
 * 3) Label each function and make commits for each function completed. 
*/
class CityGraph {
   
   private:
   vector<CityNode*> NodeList;
   
   public:
    
   //Commit G-0
   void add_city(string id, string code, string name, unsigned int ppl, int elevation){
      CityNode* city = new CityNode(id, code, name, ppl, elevation);
      NodeList.push_back(city);
   }
   
   //Commit 1
   void delete_city(string id){
      //Given a list, must delete a node using a id. 
   }
   
   //Commit 2
   void add_connection(){
     //Establish connection using getters and setters between two nodes.
   }
   
   //Commit 3
   void delete_connection(){
     //Given two nodes, erase the connection between them
     //Access the info using nodes. 
   }

   

};