#include <iostream>
#include <sstream>
#include "graphiso.h"

using namespace std;

Graph::Graph(std::istream& istr)
{
    string aline;
    while(getline(istr,aline))
    {
        istringstream iss(aline);
        string u, v;
        if(iss >> u){
            VERTEX_SET_T neighbors;
            while(iss >> v)
            {
                neighbors.insert(v);
            }
            adj_.insert(std::make_pair(u,neighbors));
        }
    }
}


bool Graph::edgeExists(const VERTEX_T& u, const VERTEX_T& v) const // checks whether v is a neighbor for u, meaning there is an edge between u and v
{
    if((adj_.find(u) != adj_.end()) && (adj_.at(u).find(v) != adj_.at(u).end()))
    {
        return true;
    }
    return false;
}
const VERTEX_SET_T& Graph::neighbors(const VERTEX_T& v) const //   returns a set of a vertex's neighbors
{
    if(adj_.find(v) == adj_.end()){
        throw std::invalid_argument("Neighbors: invalid vertex - not in  map");
    }
    return adj_.at(v);
}
VERTEX_LIST_T Graph::vertices() const //    gets all the vertices in a graph
{
    VERTEX_LIST_T verts;
    for(const auto& p : adj_)
    {
        verts.push_back(p.first);
    }
    return verts;
}

// To check if the mapping is consistent, if not return false
bool isConsistent(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping, VERTEX_T g1v)
{   

    VERTEX_LIST_T g1verts = g1.vertices(); // gets all of g1 vertices to check is graph is still consistent
    VERTEX_T mapped = mapping[g1v]; //  to get the mapped g2 vertex to current g1 vertex
    VERTEX_SET_T neighbor1 = g1.neighbors(g1v); // find the neighbors of the current g1 vertex
    VERTEX_SET_T neighbor2 = g2.neighbors(mapped); // find the neighbors of the current g2 vertex

    if(neighbor1.size() != neighbor2.size()){ // if the vertices have different degrees then return false
        return false;
    }
    for(const auto& g1u : g1verts){ // goes through all the vertices to make sure there is a bijection/ edge exising
        VERTEX_SET_T n = g1.neighbors(g1u);
        for(const auto& gn : n){
            try{
                VERTEX_T g2v = mapping[gn];
                if(!g2.edgeExists(mapping[g1u], g2v)){ // can only stop if there is a mapping different, cannot if matching is the same
                    return false;
                }
            }
            catch(...){
                continue;
            }
        }
    }
    
    // at this point the current graph means the bijection holds
    return true;
}

bool helperFunction(const Graph& g1, VERTEX_LIST_T& g1_verts, const Graph& g2, VERTEX_ID_MAP_T& mapping, unsigned int placement, set<string>& used){ // generates all possible combinations of mapping for the g2 vertices on g1 vertices

    if(placement == g1_verts.size()){
        return true;
    }

    VERTEX_T to_map = g1_verts[placement]; // a variable that stores the key to be mapped with in graph 2

    VERTEX_LIST_T g2_verts = g2.vertices(); // a vector of g2 vertices

    //  the loop generates all possible values for mapping might end early before the loop's termination
    for(unsigned int i = 0; i < g1_verts.size(); ++i){
        
        //  checks if vert can be checked
        if(used.find(g2_verts[i]) == used.end()){

            //  creates a pair inserts into mapping then checks using isConsistent
            mapping.insert(pair<string,string>(to_map, g2_verts[i]));
            if(!isConsistent(g1, g2, mapping, to_map)){ //  if consistency fails remove the mapping and iterate
                mapping.remove(to_map);
            }
            else{
                used.insert(g2_verts[i]); // insert the used g2 vertex
                if(helperFunction(g1, g1_verts, g2, mapping, placement+1, used)){ //    if the recursion afterwards prove to be true return true
                    return true;
                }
                else{ //    if the previous had a fail remove this used g2 vertex
                    used.erase(g2_verts[i]);
                }
            }
        }
    }

    return false;

}

bool graphIso(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    VERTEX_LIST_T g1verts = g1.vertices();
    if(g1verts.size() != g2.vertices().size())
    {
        return false;
    }

    // sets up a set of used g2 vertices so when generating combinations we don't get duplicates
    set<string> used;

    // calls the helper then returns its value
    return helperFunction(g1, g1verts, g2, mapping, 0, used);
}

