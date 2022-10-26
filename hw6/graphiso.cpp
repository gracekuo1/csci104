#include <iostream>
#include <sstream>
#include "graphiso.h"

using namespace std;

// ================= Complete - Begin Graph class implementation ===================
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


bool Graph::edgeExists(const VERTEX_T& u, const VERTEX_T& v) const
{
    if((adj_.find(u) != adj_.end()) && (adj_.at(u).find(v) != adj_.at(u).end()))
    {
        return true;
    }
    return false;
}
const VERTEX_SET_T& Graph::neighbors(const VERTEX_T& v) const
{
    if(adj_.find(v) == adj_.end()){
        throw std::invalid_argument("Neighbors: invalid vertex - not in  map");
    }
    return adj_.at(v);
}
VERTEX_LIST_T Graph::vertices() const
{
    VERTEX_LIST_T verts;
    for(const auto& p : adj_)
    {
        verts.push_back(p.first);
    }
    return verts;
}
// ================= Complete - End Graph class implementation ===================

// Prototype and helper functions here

// To be completed
bool isConsistent(VERTEX_T& g1u, VERTEX_T& g2u, const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    // Feel free to change or remove this starter code

    if (g1.neighbors(g1u).size() != g2.neighbors(g2u).size()){
        return false;
    }

    //loops thru g1u neighbors
    VERTEX_SET_T::iterator it;
    for (it = g1.neighbors(g1u).begin(); it != g1.neighbors(g1u).end(); ++it){
    // for(const VERTEX_T& g1v : g1.neighbors(g1u)) {
        VERTEX_T g1v = *it;
        //does it exist in thr map?
        if (mapping.find(g1v) != nullptr){
            VERTEX_T g2v = mapping[g1v];
            if (!g2.edgeExists(g2u, g2v)){
                return false;
            }
        }
    }

    return true;
    
    /*VERTEX_LIST_T g1verts = g1.vertices();
    VERTEX_LIST_T g2verts = g2.vertices();

    for(const auto& g1u : g1verts)
    {
        // Check mappings for necessary vertices to see if there is any violation
        bool found = false;
        for (const auto& g2u : g2verts){
            if (g1.neighbors(g1u).size() == g2.neighbors(g2u).size()){
                found = true;
            }
        }
        //check edges
        for(const auto& g1v : g1.neighbors(g1u)) {
            VERTEX_T g2u = mapping[g1u];
            VERTEX_T g2v = mapping[g1v];

            if (!g2.edgeExists(g2u, g2v)){
                return false;
            }
        }
        if (!found)
            return false;
    }
    return true;*/
}

// Add any helper functions you deem useful

bool mapThis (int i, int j, const Graph& g1, const Graph& g2, VERTEX_LIST_T& g1verts, VERTEX_LIST_T& g2verts, VERTEX_ID_MAP_T& mapping){
    if (mapping.size() >= g1verts.size()) {
        return true;
    }
    VERTEX_T g1u = g1verts[i];
    bool validmap = false;
        
    for (size_t k = 0; k <g2verts.size(); k++){
        VERTEX_T g2u = g2verts[k];
        bool alreadyThere = false;
        for (size_t i = 0; i < mapping.size(); i ++){
            if (mapping.find(g1verts[i]) != NULL){
                if (mapping.find(g1verts[i])->second == g2u){
                    alreadyThere = true;
                    break;
                }  
            }
        }
        if (!alreadyThere && isConsistent(g1u, g2u, g1, g2, mapping)){
            mapping.insert(make_pair(g1u, g2u));             
            validmap = mapThis(i+1, k, g1, g2, g1verts, g2verts, mapping);
            if (validmap)
                return true;
            mapping.remove(g1u); 
        }
    }
    return false;
   
   
   /*if (i == g1verts.size() && j == g2verts.size() ) 
        return isConsistent(g1, g2, mapping);
    
    for (size_t k = 0; k <g2verts.size(); k++){
        mapping.insert(make_pair(g1verts[i], g2verts[k])); 
        if (mapThis(i+1, k, g1, g2, g1verts, g2verts, mapping))
            return true;
        else
            mapping.remove(g1verts[i]); 
    }
    return false;*/
}

// To be completed
bool graphIso(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    VERTEX_LIST_T g1verts = g1.vertices();
    VERTEX_LIST_T g2verts = g2.vertices();

    if(g1verts.size() != g2.vertices().size())
    {
        return false;
    }
    // Add code here
    return mapThis (0, 0, g1, g2, g1verts, g2verts, mapping);

    // Delete this and return the correct value...
    // This is just placeholder to allow compilation
    return false;
}

