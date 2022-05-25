#include <map>
#include <fstream>
#include <algorithm>
#include <utility>

#define Graph std::map<std::pair<int,int>, int>

// working on implementing N^2 * Logn Runtime using Dijkstra and a dummy vertex

// void add_dummy_source(const int num, Graph& input){

//    pair <int ,int > dummyEdges;
//     for(int i = 1; i <= num; ++i){
//         input.insert(make_pair(dummyEdges, 0));
//     }

// }

int bellmanford(const int numV, const int numE, Graph& input, int src){

    // add_dummy_source(numV, input);
    int dist[numV+1];
    for (int i = 1; i <=numV; ++i) dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= numV - 1; ++i) {
        for (auto j: input) {
            int u = j.first.first;
            int v = j.first.second;
            int weight = j.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
            }
        }
    }
    for (auto j: input) {
        int u = j.first.first;
        int v = j.first.second;
        int weight = j.second;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
            return INT_MAX;
        }
    }

    return *std::min_element(dist, dist+numV+1);
}

int APSP(std::string filename){

    int numNode, numEdge;
    std::fstream f;
    Graph graph;
    int source, dest, cost;

    std::string tp;
    f.open(filename,std::ios::in);
    if (f.is_open()){ //  reads in all the data from jobs.txt
        getline(f, tp);
        sscanf(tp.c_str(),"%d %d", &numNode, &numEdge);
        while(getline(f, tp)){
            sscanf(tp.c_str(),"%d %d %d", &source, &dest, &cost);
            std::pair<int, int> edge;
            edge.first = source;
            edge.second = dest;
            graph.insert(make_pair(edge, cost));
        }
        f.close();
    }

    int shortest = INT_MAX;
    int retval = 0;

    for(int i = 1; i <= numNode; ++i){
        retval = bellmanford(numNode, numEdge, graph, i);
        if(retval == INT_MAX){
            throw std::runtime_error("Input Graph Contains A Negative Cycle, no shortest path to be found");
        }
        else{
            shortest = (retval < shortest) ? retval: shortest;
        }
    }

    return shortest;

}