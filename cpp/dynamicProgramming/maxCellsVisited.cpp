/*
Given a 1-indexed m x n integer matrix mat, you can select any cell in the matrix as your starting cell.

From the starting cell, you can move to any other cell in the same row or column, but only if the value of the destination cell is strictly greater than the value of the current cell. You can repeat this process as many times as possible, moving from cell to cell until you can no longer make any moves.

Your task is to find the maximum number of cells that you can visit in the matrix by starting from some cell.

Return an integer denoting the maximum number of cells that can be visited.

 

Example 1:



Input: mat = [[3,1],[3,4]]
Output: 2
Explanation: The image shows how we can visit 2 cells starting from row 1, column 2. It can be shown that we cannot visit more than 2 cells no matter where we start from, so the answer is 2. 
Example 2:



Input: mat = [[1,1],[1,1]]
Output: 1
Explanation: Since the cells must be strictly increasing, we can only visit one cell in this example. 
Example 3:



Input: mat = [[3,1,6],[-9,5,7]]
Output: 4
Explanation: The image above shows how we can visit 4 cells starting from row 2, column 1. It can be shown that we cannot visit more than 4 cells no matter where we start from, so the answer is 4. 
*/


// Time limit exceeded
// Iterate, checking every cell
// Check if a path to this cell from any other cells is longer than the one already to it
// Build up from distance 1 paths

class Solution {
public:
    int maxIncreasingCells(vector<vector<int>>& mat) {
        int nRow = mat.size();
        int nCol = mat[0].size();
        vector<vector<int>> maxPath;
        for(int i=0;i<nRow;i++){
            maxPath.push_back(vector<int>(nCol, 1));
        }

        int globalMax = 1;
        bool improvement = true;
        while(improvement){
            improvement = false;
            // Check each cell
            for(int i=0;i<nRow;i++){
                for(int j=0;j<nCol;j++){
                    // Check other cells in its col
                    for(int k=0;k<nRow;k++){
                        if(k == i)
                            continue;
                        // A path ending at k,j and going to i,j is longer than longest already ending at i,j
                        if(mat[k][j] < mat[i][j] && maxPath[k][j] + 1 > maxPath[i][j]){
                            improvement = true;
                            maxPath[i][j] = maxPath[k][j] + 1;
                            if(maxPath[i][j] > globalMax)
                                globalMax = maxPath[i][j];
                        }
                    }
                    // Check other cells in its row
                    for(int k=0;k<nCol;k++){
                        if(k == j)
                            continue;
                        // A path ending at k,j and going to i,j is longer than longest already ending at i,j
                        if(mat[i][k] < mat[i][j] && maxPath[i][k] + 1 > maxPath[i][j]){
                            improvement = true;
                            maxPath[i][j] = maxPath[i][k] + 1;
                            if(maxPath[i][j] > globalMax)
                                globalMax = maxPath[i][j];
                        }
                    }
                }
            }
        }

        return globalMax;
    }
};