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

struct TNode{
    TNode *parent = NULL;
    TNode *left = NULL;
    TNode *right = NULL;
    int val;
};

TNode* findMax(TNode *node){
    if(node->right != NULL) // Keep going right until there is none
        return findMax(node->right);
    return node;
}

void printTree(TNode *node){
    if(node == NULL)
        return;
    printTree(node->left);
    cout << node->val << ", ";
    printTree(node->right);
}

void insert(TNode *newnode, TNode *node, TNode *parent){
    // Less than case
    if(newnode->val < node->val){
        if(node->left == NULL){
            node->left = newnode; // insert in empty spot
            newnode->parent = node;
        }else{
            insert(newnode, node->left, node); // or go to next node
        }
    }else{ // Greater than case
        if(node->right == NULL){
            node->right = newnode; //insert in empty spot
            newnode->parent = node;
        }else{
            insert(newnode, node->right, node);
        }
    }
}


TNode* delNode(TNode *node){
    TNode *replacement = NULL; // The node to replace this node
    // Check if it has less than 2 children (easy case)
    if(node->left == NULL || node->right == NULL){
        // Find one that is NULL
        if(node->left == NULL){
            replacement = node->right; // could be NULL, but doesn't matter
        }else{
            replacement = node->left;
        }
        // Set parent's pointers
        if(node->parent != NULL){ // Set parent's pointers
            if(node->parent->left == node){
                node->parent->left = replacement;
            }else{
                node->parent->right = replacement;
            }
        }
        // Set replacement pointers
        if(replacement != NULL){
            replacement->parent = node->parent;
        }
    }else{ // It has 2 children
        replacement = findMax(node->left); // Find max node in left subtree
        // Remove replacement from left subtree
        if(replacement->parent->left == replacement){ // NULL parent's pointer
            replacement->parent->left = NULL; // This only happens if replacement was root of left subtree
        }else{
            replacement->parent->right = NULL;
        }
        // Insert replacement into deleted node's position
        replacement->parent = node->parent; // Set replacement's pointers
        replacement->left = node->left;
        replacement->right = node->right;
        // Set right child's parents
        node->right->parent = replacement;
        // Set parent's pointers
        if(node->parent != NULL){ 
            if(node->parent->left == node){
                node->parent->left = replacement;
            }else{
                node->parent->right = replacement;
            }
        }
    }
    return replacement;
}

int sumKsmallest(TNode *node, int sum, int &count, int k){
    // Go left
    if(node->left != NULL){
        sum = sumKsmallest(node->left, sum, count, k);
    }
    // Add self if appropriate
    if(count < k){
        sum += node->val;
        count++;
    }
    // Go right if appropriate
    if(count < k && node->right != NULL){
        sum = sumKsmallest(node->right, sum, count, k);
    }
    return sum;
}

int sumKlargest(TNode *node, int sum, int &count, int k){
    // Go right
    if(node->right != NULL){
        sum = sumKlargest(node->right, sum, count, k);
    }
    // Add self if appropriate
    if(count < k){
        sum += node->val;
        count++;
    }
    // Go left if appropriate
    if(count < k && node->left != NULL){
        sum = sumKlargest(node->left, sum, count, k);
    }
    return sum;
}


class MKAverage {
public:
    vector<TNode *> nodes;
    TNode *root;
    int M;
    int K;
    int sum;

    MKAverage(int m, int k) {
        root = NULL;
        M = m;
        K = k;
        sum = 0;
    }
    
    void addElement(int num) {
        // Add to sum
        sum += num;

        // Create new TNode
        TNode *newnode = new TNode();
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
        if(nodes.size() > M){
            // Subtract from sum
            sum -= nodes[0]->val;

            // Remove from tree
            TNode *replacement = delNode(nodes[0]); 
            if(nodes[0] == root) // if we deleted the root
                root = replacement; // set the root to the node that replaced the root

            // Remove from vector
            nodes.erase(nodes.begin()); 
        }
    }
 
    int calculateMKAverage() {
        // Return -1 if fewer than M elements
        if(nodes.size() < M)
            return -1;

        // Counters to help sum nodes of tree
        int count0 = 0; // counts are shared by recursive calls to decide when to stop summing
        int count1 = 0;
        int s = sum - sumKsmallest(root, 0, count0, K) - sumKlargest(root, 0, count1, K); // sum of all minus k largest and smallest
        return s / (M-2*K); // average
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */