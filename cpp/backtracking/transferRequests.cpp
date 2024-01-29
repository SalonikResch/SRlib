/*
We have n buildings numbered from 0 to n - 1. Each building has a number of employees. It's transfer season, and some employees want to change the building they reside in.

You are given an array requests where requests[i] = [fromi, toi] represents an employee's request to transfer from building fromi to building toi.

All buildings are full, so a list of requests is achievable only if for each building, the net change in employee transfers is zero. This means the number of employees leaving is equal to the number of employees moving in. For example if n = 3 and two employees are leaving building 0, one is leaving building 1, and one is leaving building 2, there should be two employees moving to building 0, one employee moving to building 1, and one employee moving to building 2.

Return the maximum number of achievable requests.
*/

// Brute Force

class Solution {
public:
    void processRequests(int r, int n, vector<vector<int>>& requests, int *enter, int *leave, int &maxRequests){
        // If it end, evaluate
        if(r == requests.size()){
            bool success = true;
            int nRequests = 0;
            for(int i=0;i<n;i++){
                nRequests += enter[i];
                if(enter[i] != leave[i]){
                    success = false;
                }
            }
            if(success && nRequests > maxRequests){
                maxRequests = nRequests;
            }
            return;
        }
        // Try both cases
        // not granting
        processRequests(r+1, n, requests, enter, leave, maxRequests); 
        // granting
        leave[requests[r][0]]++;
        enter[requests[r][1]]++;
        processRequests(r+1, n, requests, enter, leave, maxRequests); 
        leave[requests[r][0]]--;
        enter[requests[r][1]]--;
    }

    int maximumRequests(int n, vector<vector<int>>& requests) {
        // Requests to enter each building
        int *enter = new int[n]();
        // Requests to leave each building
        int *leave = new int[n]();

        int maxRequests = 0;
        processRequests(0, n, requests, enter, leave, maxRequests);
        return maxRequests;
    }
};