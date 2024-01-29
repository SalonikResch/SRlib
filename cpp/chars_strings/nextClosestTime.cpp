/*
Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.

You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.

 

Example 1:

Input: time = "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.
It is not 19:33, because this occurs 23 hours and 59 minutes later.
Example 2:

Input: time = "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22.
It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.
 

Constraints:

time.length == 5
time is a valid time in the form "HH:MM".
0 <= HH < 24
0 <= MM < 60
*/

using namespace std;

int minutesBetween(int hourA, int minA, int hourB, int minB){
    if(hourB >= 24 || minB > 59){
        return 25*60;
    }
    if(hourA == hourB && minA == minB){
        return 24*60;
    }
    int A = 60*hourA+minA;
    int B = 60*hourB+minB;
    int D = B-A;
    if(D < 0){
        D += 24*60;
    }
    return D;
}

class Solution {
public:
    string nextClosestTime(string time) {
        int hourA = stoi(time.substr(0,2));
        int minA = stoi(time.substr(3,2));
        
        int *digits = new int[4];
        digits[0] = time[0] - '0';
        digits[1] = time[1] - '0';
        digits[2] = time[3] - '0';
        digits[3] = time[4] - '0';

        int maxDiff = 25*60;
        string s;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                for(int k=0;k<4;k++){
                    for(int l=0;l<4;l++){
                        int hourB = digits[i]*10+digits[j];
                        int minB = digits[k]*10+digits[l];
                        int diff = minutesBetween(hourA, minA, hourB, minB);
                        if(diff < maxDiff){
                            maxDiff = diff;
                            ostringstream ss;
                            ss << digits[i] << digits[j] << ":" << digits[k] << digits[l];
                            s = ss.str();
                        }
                    }
                }
            }
        }
        return s;
    }
};