#include <unordered_map> // Hash table
#include <vector>
#include <iostream>
using namespace std;

class Node{
  public:
    int val = -1; // Value stored in node
    vector <Node *> neighbors = {}; // Vector of pointers to neighbor
};

typedef unordered_map<Node *, Node*> nodeMap;

void printMap(nodeMap map){
  for(auto i=map.cbegin();i != map.cend(); i++){
    cout << i->first << " to " << i->second << endl;
  }
}

void recurseClone(Node* node, Node* clone, nodeMap visited){
  printMap(visited);
  cout << "In node " << node->val << endl;
  // Indicate this node has been visited
  // and also make record of the copy
  visited[node] = clone;
  // Set same value in clone
  clone->val = node->val;

  // Go over each of its neighbors
  for(int i=0;i<node->neighbors.size();i++){
    Node *neighbor = node->neighbors[i];
    // If neighbor is a visited node
    if(visited.find(neighbor) != visited.end()){
      cout << "See pre-existing neighbor " << visited[neighbor]->val << endl;
      clone->neighbors.push_back(visited[neighbor]);
    }else{
      cout << "Making new neighbor " << neighbor->val << endl;
      Node *new_node = new Node();
      recurseClone(neighbor, new_node, visited);
      clone->neighbors.push_back(new_node);
    }
  }
}

Node* clone(Node* root) {
  // Create hash table
  nodeMap visited;
  //TODO: Write - Your - Code
  // New root
   Node *clone_root = new Node();

   recurseClone(root, clone_root, visited);
   return clone_root;
}


int main(int argc, char **argv){
  // Directed graph from https://www.educative.io/blog/apple-coding-interview-questions
  Node **nodes = new Node*[5];
  for(int i=0;i<5;i++){
    nodes[i] = new Node();
    nodes[i]->val = i;
  }
  nodes[0]->neighbors.push_back(nodes[2]);
  nodes[0]->neighbors.push_back(nodes[3]);
  nodes[0]->neighbors.push_back(nodes[4]);
  nodes[1]->neighbors.push_back(nodes[2]);
  nodes[2]->neighbors.push_back(nodes[0]);
  nodes[3]->neighbors.push_back(nodes[2]);
  nodes[4]->neighbors.push_back(nodes[0]);
  nodes[4]->neighbors.push_back(nodes[1]);
  nodes[4]->neighbors.push_back(nodes[3]);

  Node *cloned = clone(nodes[0]);
}