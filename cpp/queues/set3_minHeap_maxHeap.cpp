/*
You are given an integer array nums.

In one move, you can choose one element of nums and change it to any value.

Return the minimum difference between the largest and smallest value of nums after performing at most three moves.

 

Example 1:

Input: nums = [5,3,2,4]
Output: 0
Explanation: We can make at most 3 moves.
In the first move, change 2 to 3. nums becomes [5,3,3,4].
In the second move, change 4 to 3. nums becomes [5,3,3,3].
In the third move, change 5 to 3. nums becomes [3,3,3,3].
After performing 3 moves, the difference between the minimum and maximum is 3 - 3 = 0.
Example 2:

Input: nums = [1,5,0,10,14]
Output: 1
Explanation: We can make at most 3 moves.
In the first move, change 5 to 0. nums becomes [1,0,0,10,14].
In the second move, change 10 to 0. nums becomes [1,0,0,0,14].
In the third move, change 14 to 1. nums becomes [1,0,0,0,1].
After performing 3 moves, the difference between the minimum and maximum is 1 - 0 = 1.
It can be shown that there is no way to make the difference 0 in 3 moves.
Example 3:

Input: nums = [3,100,20]
Output: 0
Explanation: We can make at most 3 moves.
In the first move, change 100 to 7. nums becomes [3,7,20].
In the second move, change 20 to 7. nums becomes [3,7,7].
In the third move, change 3 to 7. nums becomes [7,7,7].
After performing 3 moves, the difference between the minimum and maximum is 7 - 7 = 0.
*/


// Use min and max heap to keep track of smallest and largest elements
// Test removing them to find optimal solution

#include <bits/stdc++.h>

class Solution {
public:
    int minDifference(vector<int>& nums) {
        // If length is 3 or less, difference is 0
        if(nums.size() <= 3){
            return 0;
        }

        // Priority queues to implement max and min heaps
        priority_queue <int> largest; // max heap
        priority_queue <int, vector<int>, greater<int>> smallest; // min heap

        // Put them in queues
        for(int i=0;i<nums.size();i++){
            largest.push(nums[i]);
            smallest.push(nums[i]);
        }

        // Get 4 largest and smallest (unless array is less than 8)
        int nFromSmall = std::min(4, (int)std::ceil(nums.size()/2.0)); // Then take fewer from each
        int nFromLarge = std::min(4, (int)std::floor(nums.size()/2.0)); // to prevent overlap

        // A vector that has the smallest and largest elements
        vector<int> extremes;
        // Take the smallest
        for(int i=0;i<nFromSmall;i++){
            if(!smallest.empty()){
                extremes.push_back(smallest.top());
                smallest.pop();
            }
        }
        // And insert largest
        for(int i=0;i<nFromLarge;i++){
            if(!largest.empty()){
                extremes.insert(extremes.begin()+nFromSmall,largest.top());
                largest.pop();
            }
        }

        unsigned int smallestDiff = (unsigned int)-1;
        // Extremes is a sorted vector of up to 4 smallest and lagest
        for(int i=0;i<=3;i++){ // The best will be removing 3 elements, from the ends
            int removeFromFront = i; // Remove this many from the smallest
            int removeFromBack = 3-i; // And this many from the largest
            int newSmallest = extremes[removeFromFront]; // New smallest and largest
            int newLargest = extremes[extremes.size()-1-removeFromBack];
            if(newLargest-newSmallest < smallestDiff){
                smallestDiff = newLargest-newSmallest;
            }
        }
        return smallestDiff;
    }
};