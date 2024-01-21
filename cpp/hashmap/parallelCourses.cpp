/*
You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where relations[i] = [prevCoursei, nextCoursei], representing a prerequisite relationship between course prevCoursei and course nextCoursei: course prevCoursei has to be taken before course nextCoursei.

In one semester, you can take any number of courses as long as you have taken all the prerequisites in the previous semester for the courses you are taking.

Return the minimum number of semesters needed to take all courses. If there is no way to take all the courses, return -1.

 

Example 1:


Input: n = 3, relations = [[1,3],[2,3]]
Output: 2
Explanation: The figure above represents the given graph.
In the first semester, you can take courses 1 and 2.
In the second semester, you can take course 3.
Example 2:


Input: n = 3, relations = [[1,2],[2,3],[3,1]]
Output: -1
Explanation: No course can be studied because they are prerequisites of each other.
*/

// Features
// Hashmap of vectors
// Deleting vector element by value
// Swapping vector pointers


#include <unordered_map>

typedef unordered_map<int, vector<int>> hmap;

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        // Build 2 hashmaps 1 for pre-req, 1 for following
        hmap prereq;
        hmap follow;

        for(int i=0;i<relations.size();i++){
            int c1 = relations[i][0];
            int c2 = relations[i][1];

            // Follow
            if(follow.find(c1) != follow.end()){ // c1 is in follow
                follow[c1].push_back(c2);
            }else{
                follow[c1] = vector<int>(1,c2); // Insert vector of length 1 with c2
            }

            // Pre-req
            if(prereq.find(c2) != prereq.end()){ // c1 is in follow
                prereq[c2].push_back(c1);
            }else{
                prereq[c2] = vector<int>(1,c1); // Insert vector of length 1 with c2
            }
        }

        // Keep track of these as we go
        int nSemesters = 0;
        int nClasses = 0;
        // Queue to hold classes will take this and next semester
        vector<int> thisSemester;
        vector<int> nextSemester;
        for(int i=0;i<n;i++){ // first populate with courses with no prereqs
            if(prereq.find(i+1) == prereq.end()){
                thisSemester.push_back(i+1);
            }
        }
        // If no solution
        if(thisSemester.size() == 0){
            return -1;
        }

        while(nClasses < n){
            nSemesters++;
            if(thisSemester.size() == 0){
                return -1;
            }
            // Take classes
            for(int i=0;i<thisSemester.size();i++){
                int classTaken = thisSemester[i];
                nClasses++;
                // Check for success
                if(nClasses == n){
                    return nSemesters;
                }
                // Free up prereq for other courses
                if(follow.find(classTaken) != follow.end()){ // if it has follows
                    vector<int> followingCourses = follow[classTaken];
                    for(int j=0;j<followingCourses.size();j++){
                        int followingCourse = followingCourses[j];
                        // Remove classTaken from prereq for following course
                        prereq[followingCourse].erase(std::remove(prereq[followingCourse].begin(), prereq[followingCourse].end(), classTaken), prereq[followingCourse].end());
                        // If there are no prereqs left, this class can be taken next semester
                        if(prereq[followingCourse].size() == 0){
                            nextSemester.push_back(followingCourse);
                        }
                    }
                }      
            }
            // Done taking classes, switch to next semester
            thisSemester.clear();
            vector<int> temp = thisSemester;         
            thisSemester = nextSemester;
            nextSemester = temp;
        }
        return -1;
    }
};

//vec.erase(std::remove(vec.begin(), vec.end(), 8), vec.end());