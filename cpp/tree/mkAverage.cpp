// You are given two integers, m and k, and a stream of integers. You are tasked to implement a data structure that calculates the MKAverage for the stream.

// The MKAverage can be calculated using these steps:

// If the number of the elements in the stream is less than m you should consider the MKAverage to be -1. Otherwise, copy the last m elements of the stream to a separate container.
// Remove the smallest k elements and the largest k elements from the container.
// Calculate the average value for the rest of the elements rounded down to the nearest integer.
// Implement the MKAverage class:

// MKAverage(int m, int k) Initializes the MKAverage object with an empty stream and the two integers m and k.
// void addElement(int num) Inserts a new element num into the stream.
// int calculateMKAverage() Calculates and returns the MKAverage for the current stream rounded down to the nearest integer.
 

// Example 1:

// Input
// ["MKAverage", "addElement", "addElement", "calculateMKAverage", "addElement", "calculateMKAverage", "addElement", "addElement", "addElement", "calculateMKAverage"]
// [[3, 1], [3], [1], [], [10], [], [5], [5], [5], []]
// Output
// [null, null, null, -1, null, 3, null, null, null, 5]

// Explanation
// MKAverage obj = new MKAverage(3, 1); 
// obj.addElement(3);        // current elements are [3]
// obj.addElement(1);        // current elements are [3,1]
// obj.calculateMKAverage(); // return -1, because m = 3 and only 2 elements exist.
// obj.addElement(10);       // current elements are [3,1,10]
// obj.calculateMKAverage(); // The last 3 elements are [3,1,10].
//                           // After removing smallest and largest 1 element the container will be [3].
//                           // The average of [3] equals 3/1 = 3, return 3
// obj.addElement(5);        // current elements are [3,1,10,5]
// obj.addElement(5);        // current elements are [3,1,10,5,5]
// obj.addElement(5);        // current elements are [3,1,10,5,5,5]
// obj.calculateMKAverage(); // The last 3 elements are [5,5,5].
//                           // After removing smallest and largest 1 element the container will be [5].
//                           // The average of [5] equals 5/1 = 5, return 5

// Solution: Keep a binary tree for efficient insertion and retrieval of both max and min
// Keep a seperate vector of pointers to nodes to delete them from the tree

struct TreeNode{
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    int val;
}

void insert(TreeNode *newnode, TreeNode *node, TreeNode *parent){
    // Less than case
    if(newnode->val < node->val){
        if(node->left == NULL){
            node->left = newnode; // insert in empty spot
        }else{
            insert(newnode, node->left, node); // or go to next node
        }
    }else{ // Greater than case
        if(node->right == NULL){
            node->right = newnode; //insert in empty spot
        }else{
            insert(newnode, node->right, node);
        }
    }
}

void delNode(TreeNode *node){
    
}

class MKAverage {
public:
    MKAverage(int m, int k) {
        vector<TreeNode *> nodes;
        TreeNode *root;
        int M = m;
        int K = k;
    }
    
    void addElement(int num) {
        // Create new treenode
        TreeNode *newnode = new TreeNode();
        newnode->val = num;

        // Insert into vector
        nodes.push_back(newnode);

        //Insert into tree
        if(root != NULL){
            insert(newnode, root, NULL);
        }else{
            root = newnode;
        }

        // Delete old node
        if(nodes.size() >= M){
            delNode(nodes[0]); // Remove from tree
            nodes.erase(nodes.begin()); // Remove from vector
        }
    }
    
    int calculateMKAverage() {
        
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */