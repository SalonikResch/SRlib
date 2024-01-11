#include <unordered_map> // Hash table
#include <vector>
#include <iostream>
using namespace std;


typedef unordered_map<int, bool> hashmap;


// A function equivalent to np.unique, return a vector of all the unique elements
vector<int> unique(vector<int> &array){

  // Create a hash table
  hashmap uniqueItems;

  // Iterate over the input array
  for(int i=0; i<array.size(); i++){
    // Check if it is not already in hashmap
    if(uniqueItems.find(array[i]) == uniqueItems.end()){
      uniqueItems.insert({array[i], true}); // add it
    }
  }

  // Copy unique items to new vector
  vector <int> u;
  for(auto it : uniqueItems){
    u.push_back(it.first);
  }
  return u;
}

int main(){
  vector<int> elements = {5, 5, 5, 5, 0, 1, 2, 3, 4};
  vector<int> u = unique(elements);

  for(int i=0;i<u.size();i++){
    cout << u[i] << " ";
  }
  cout << endl;

  return 0;
}

