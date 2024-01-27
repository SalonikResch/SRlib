/*
You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.

You may jump forward from index i to index j (with i < j) in the following way:

During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
It may be the case that for some index i, there are no legal jumps.
A starting index is good if, starting from that index, you can reach the end of the array (index arr.length - 1) by jumping some number of times (possibly 0 or more than once).

Return the number of good starting indices.

 

Example 1:

Input: arr = [10,13,12,14,15]
Output: 2
Explanation: 
From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
From starting index i = 4, we have reached the end already.
In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
jumps.
Example 2:

Input: arr = [2,3,1,1,4]
Output: 3
Explanation: 
From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:
During our 1st jump (odd-numbered), we first jump to i = 1 because arr[1] is the smallest value in [arr[1], arr[2], arr[3], arr[4]] that is greater than or equal to arr[0].
During our 2nd jump (even-numbered), we jump from i = 1 to i = 2 because arr[2] is the largest value in [arr[2], arr[3], arr[4]] that is less than or equal to arr[1]. arr[3] is also the largest value, but 2 is a smaller index, so we can only jump to i = 2 and not i = 3
During our 3rd jump (odd-numbered), we jump from i = 2 to i = 3 because arr[3] is the smallest value in [arr[3], arr[4]] that is greater than or equal to arr[2].
We can't jump from i = 3 to i = 4, so the starting index i = 0 is not good.
In a similar manner, we can deduce that:
From starting index i = 1, we jump to i = 4, so we reach the end.
From starting index i = 2, we jump to i = 3, and then we can't jump anymore.
From starting index i = 3, we jump to i = 4, so we reach the end.
From starting index i = 4, we are already at the end.
In total, there are 3 different starting indices i = 1, i = 3, and i = 4, where we can reach the end with some
number of jumps.
Example 3:

Input: arr = [5,1,3,4,2]
Output: 3
Explanation: We can reach the end from starting indices 1, 2, and 4.
*/


// Build from right to left
// Right side is base case, find jumps back to pre-existing success paths
// Need to look up values/indices already seen (to the right)
// A tree structure works


#include <vector>

// A node to store values seen so far
struct Node{
    int val; // value
    int idx; // lowest index it has been seen at (moving from right to left)
    Node *left = NULL;
    Node *right = NULL;
};

void insert(Node *n, int val, int idx){
    if(n->val == val){
        n->idx = idx; // update index (we only care about the lowest index of this value)
    }else if(val > n->val){
        if(n->right != NULL){
            insert(n->right, val, idx);
        }else{
            n->right = new Node();
            n->right->val = val;
            n->right->idx = idx;
            //n->right->parent = n;
        }
    }else{ // val < n->val
        if(n->left != NULL){
            insert(n->left, val, idx);
        }else{
            n->left = new Node();
            n->left->val = val;
            n->left->idx = idx;
            //n->left->parent = n;
        }
    }
}

int findNextLarger(Node *n, int val){
    if(n == NULL){
        return -1;
    }
    // If match, return index immediately
    if(n->val == val){
        return n->idx;
    }else if(n->val > val){
        // It is a candidate
        // Left children could also be candidates
        int L = findNextLarger(n->left, val);
        // If valid, left child would be more optimal
        if(L >= 0){
            return L;
        }
        // Else, this is only reasonable candidate
        return n->idx;
    }else{ // n->val < val
        // Not a candidate but right children might me
        return findNextLarger(n->right, val);
    }
}

int findNextSmaller(Node *n, int val){
    if(n == NULL){
        return -1;
    }
    // If match, return index immediately
    if(n->val == val){
        return n->idx;
    }else if(n->val < val){
        // It is a candidate
        // Right children could also be candidates
        int R = findNextSmaller(n->right, val);
        // If valid, left child would be more optimal
        if(R >= 0){
            return R;
        }
        // Else, this is only reasonable candidate
        return n->idx;
    }else{ //n->val > val
        // Not a candidate but left children might me
        return findNextSmaller(n->left, val); 
    }
}

// find lowest index of smallest number equal to or larger than current
int oddJump(vector<int> &arr, int idx, Node *root){
    int F = arr[idx]; // Value to compare to
    int I = findNextLarger(root, F);
    return I;
}

// find lowest index of smallest number equal to or larger than current
int evenJump(vector<int> &arr, int idx, Node *root){
    int F = arr[idx]; // Value to compare to
    int I = findNextSmaller(root, F);
    return I;
}


// int evenJump(vector<int> &arr, int idx){
//     int F = arr[idx];
//     int L = -1;
//     int I = -1;
//     for(int i=idx+1;i<arr.size();i++){
//         if((arr[i] <= F) && (arr[i] > L)){
//             L = arr[i];
//             I = i;
//         }
//     }
//     return I;
// }

// int oddJump(vector<int> &arr, int idx){
//     int F = arr[idx];
//     int S = ~(1 << 31);
//     int I = -1;
//     for(int i=idx+1;i<arr.size();i++){
//         if((arr[i] >= F) && (arr[i] < S)){
//             S = arr[i];
//             I = i;
//         }
//     }
//     return I;
// }

class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int count = 0;

        // Bools indicating if you can make it from here with even/odd jump
        vector<bool> even = vector<bool>(arr.size(), false);
        vector<bool> odd = vector<bool>(arr.size(), false);

        // Last spot is success by construction
        even[even.size()-1] = true;
        odd[odd.size()-1] = true;

        // Tree of values to efficiently look up next-largest and next-smaller
        Node *root = new Node();
        root->val = arr[arr.size()-1];
        root->idx = arr.size()-1;

        // Go backwards, if we jump to an index we already know works
        // This index will work too
        int t;
        for(int i=arr.size()-2;i>=0;i--){
            // odd jumps
            t = oddJump(arr, i, root);
            if( (t >= 0) && even[t] ){ // Can jump to even success
                odd[i] = true; // So odd jump from this index also works
                count++; // Start with odd jump (1st), so every odd jump to success is a "good" index
            }
            // even jumps
            t = evenJump(arr, i, root); 
            if( (t >= 0) && odd[t] ){ // Can jump to odd success
                even[i] = true; // So even jump from this index also works
            }

            // Insert value, index pair into tree for lookup
            insert(root, arr[i], i);
        }

        return count+1;
    }
};