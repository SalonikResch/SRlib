/*Given the root of a binary tree, return the number of nodes where the value of the node is equal to the average of the values in its subtree.

Note:

The average of n elements is the sum of the n elements divided by n and rounded down to the nearest integer.
A subtree of root is a tree consisting of root and all of its descendants.
 

Example 1:


Input: root = [4,8,5,0,1,null,6]
Output: 5
Explanation: 
For the node with value 4: The average of its subtree is (4 + 8 + 5 + 0 + 1 + 6) / 6 = 24 / 6 = 4.
For the node with value 5: The average of its subtree is (5 + 6) / 2 = 11 / 2 = 5.
For the node with value 0: The average of its subtree is 0 / 1 = 0.
For the node with value 1: The average of its subtree is 1 / 1 = 1.
For the node with value 6: The average of its subtree is 6 / 1 = 6.
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// Passing multiple values back from function
// Two by a struct
// And one global counter with pass by reference

 struct treeStats{
     int nNodes = 0;
     int sum = 0;
 };

treeStats testSubtree(TreeNode *node, int &count){
    // Look at statistics of left and right subtrees
    treeStats left;
    treeStats right;

    if(node->left != NULL)
        left = testSubtree(node->left, count);
    if(node->right != NULL)
        right = testSubtree(node->right, count);

    // Evaluate this subtree
    int nNodes = left.nNodes + right.nNodes + 1;
    int sum = left.sum + right.sum + node->val;
    if( node->val == sum/nNodes )
        count++;
    
    // Return treestats
    treeStats thistree;
    thistree.nNodes = nNodes;
    thistree.sum = sum;

    return thistree;
}


class Solution {
public:
    int averageOfSubtree(TreeNode* root) {
        int count = 0;
        treeStats t = testSubtree(root, count);

        return count;
    }
};