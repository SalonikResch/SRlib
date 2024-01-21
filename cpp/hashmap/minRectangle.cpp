/*
You are given an array of points in the X-Y plane points where points[i] = [xi, yi].

Return the minimum area of a rectangle formed from these points, with sides parallel to the X and Y axes. If there is not any such rectangle, return 0.
*/


// Inefficient solution
// Features
// Hashmaps and vectors



#include <unordered_map>
#include <string>
#include <sstream>
using namespace std;

typedef unordered_map<int, vector<int>> pmap;
typedef unordered_map<string, bool> table;

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        // Store points in two hash maps, one indexed by x, other indexed by y
        pmap byX;
        pmap byY;
        table P;
        for(int i=0;i<points.size();i++){
            int x = points[i][0];
            int y = points[i][1];
            // Insert into x
            if(byX.find(x) != byX.end()){
                byX[x].push_back(y); // add y to vector
            }else{
                byX[x] = vector<int>(1,y); // insert vector of len 1 filled with y
            }
            // Insert into y
            if(byY.find(y) != byY.end()){
                byY[y].push_back(x); // add y to vector
            }else{
                byY[y] = vector<int>(1,x); // insert vector of len 1 filled with y
            }
            // Insert into point table
            string s;
            ostringstream out;
            out << x << "," << y;
            s = out.str();
            P[s] = true;
        }

        unsigned long minArea = (unsigned long)-1; // Set to maximum value of unsigned long
        bool found = false;
        // Now go through points and search for rectangles
        for(int i=0;i<points.size();i++){
            int x = points[i][0];
            int y = points[i][1];

            // Check matching points
            for(int j=0;j<byX[x].size();j++){
                int otherY = byX[x][j]; // other points with same x
                if(otherY == y) // if same point, skip
                    continue;
                for(int k=0;k<byY[y].size();k++){
                    int otherX = byY[y][k];
                    if(otherX == x)
                        continue;

                    // See if a 4th point exists to complete rectangle
                    string s;
                    ostringstream out;
                    out << otherX << "," << otherY;
                    s = out.str();
                    if(P.find(s) != P.end()){
                        unsigned long area = abs(otherX-x) * abs(otherY-y);
                        if(area < minArea){
                            minArea = area;
                            found = true;
                        }
                    }
                }
            }
        }
        if(found){
            return minArea;
        }
        return 0;
    }
};