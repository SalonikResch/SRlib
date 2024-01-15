// Delete nodes in a tree to make a forest
// Uses unordered_map to efficiently search for nodes to delete


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

 #include <unordered_map>
 typedef unordered_map<int, bool> hashmap;
 typedef unordered_map<TreeNode*, bool> treemap;

// Search through the binary tree
void search(TreeNode* root, treemap& inRoots, hashmap& toDelete, TreeNode *parent){
    if(root == NULL)
        return;

    // Check if this node needs to be deleted
    if(toDelete.find(root->val) != toDelete.end()){
        // Add children to roots
        if(root->left != NULL)
            inRoots.insert({root->left, true});
        if(root->right != NULL)
            inRoots.insert({root->right, true});

        // Remove root from roots, if already a root
        if(inRoots.find(root) != inRoots.end())
            inRoots[root] = false;

        // Trim the tree (set parent node pointer to NULL)
        if(parent != NULL){
            if(parent->left == root){
                parent->left = NULL;
            }else{
                parent->right = NULL;
            }
        }
    }

    // Recursive calls
    search(root->left, inRoots, toDelete, root);
    search(root->right, inRoots, toDelete, root);
}


class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        // Vector of roots
        vector<TreeNode*> roots;
        // Hashmap of roots in the forest
        treemap inRoots;
        // Hashmap of deletes
        hashmap toDelete;
        // Fill hashmap of deletes
        for(int i=0;i<to_delete.size();i++){
            toDelete.insert({to_delete[i], true});
        }

        // Insert the root of the tree, unless it should be deleted
        if(toDelete.find(root->val) == toDelete.end()){
            inRoots[root] = true;
        }
        
        // Search the tree
        search(root, inRoots, toDelete, NULL);

        // Add roots from hashmap to vector
        for(auto it : inRoots){
            if(it.second)
                roots.push_back(it.first);
        }
        return roots;
    }
};