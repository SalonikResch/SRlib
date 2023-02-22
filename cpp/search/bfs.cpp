#include <iostream>
#include <vector>
#include "../../data/graphs/graph.cpp"
#define MAX_NEIGHBORS 4
using namespace std;

//Struct for nodes in graph
struct node{
    int id;
    int n_neighbors = 0;
    struct node *neighbors[MAX_NEIGHBORS];
};

bool in(int val, vector<node *> &v){
    for(int i=0;i<v.size();i++)
        if(v[i]->id == val)
            return true;
    return false;
}

class BFS{
    public:
        int search(node* root, int stop){
            // Nodes on the active edge of search
            vector <node*> active;
            // Nodes that have already been visited
            vector <node*> visited;
            // Nodes to be considered
            vector <node*> next_nodes;

            int n_iterations = 0;
            active.push_back(root);
            //Search until found
            while(1){
                n_iterations++;
                printf("Iteration %d\n", n_iterations);
                //For all activate nodes
                for(int a=0;a<active.size();a++){
                    printf("\nActive node: %d, has %d neighbors:", active[a]->id, active[a]->n_neighbors);
                    // Check neighbors
                    for(int n=0;n<active[a]->n_neighbors;n++){
                        node* neighbor = active[a]->neighbors[n];
                        int id = neighbor->id;
                        printf("%d,", id);
                        // If not already active or visited
                        if(!in(id, active) && !in(id, visited))
                            next_nodes.push_back(neighbor);
                    }
                }
                printf("\n");
                // Check to see if answer was in new nodes
                for(int i=0;i<next_nodes.size();i++)
                    if(next_nodes[i]->id == stop)
                        return n_iterations;
                // Else get ready for next round
                for(int i=0;i<active.size();i++)
                    visited.push_back(active[i]);
                active.clear();
                for(int i=0;i<next_nodes.size();i++)
                    active.push_back(next_nodes[i]);
                next_nodes.clear();
                cin.get();
            }

            return 0;
        }
};

int main(int argc, char **argv){
    node* nodes = new node[51];
    for(int i=0;i<51;i++)
        nodes[i].id = i;
    //Set up connections
    for(int i=0;i<51;i++){
        for(int j=0;j<MAX_NEIGHBORS;j++){
            if(graph[i][j] >= 0){
                nodes[i].n_neighbors = j+1;
                node* neighbor = &(nodes[graph[i][j]]);
                nodes[i].neighbors[j] = &(nodes[graph[i][j]]);
            }
        }
    }
    BFS bfs;
    int s = bfs.search(&(nodes[0]), 15);
    printf("Search took %d iterations",s);
    return s;
}