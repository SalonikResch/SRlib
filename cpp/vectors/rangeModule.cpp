class RangeModule {
public:
    RangeModule() {
        // Will store intervals will a pair of two vectors, indicating stop and starts (sorted)
        vector <int> start;
        vector <int> stop;
    }
    // Helper
    // Index of first range that starts before at same time
    int findBefore(int time){
        int l = 0;
        int r = start.size();
        if(r == 0)
            return -1;

        int m = r/2;
        while(r > l){
            if(start[m] > time){
                r = m - 1;
            }else{
                l = m;
            }
        }

        if(start[l] <= time)
            return l;
        
        // None were found
        return -1
    }

    int findAfter(int time){
        int l = 0;
        int r = start.size();
        if(r == 0)
            return -1;

        int m = r/2;
        while(r > l){
            if(end[m] < time){
                l = m + 1;
            }else{
                r = m;
            }
        }

        if(end[r] >= time)
            return r;
        
        // None were found
        return -1
    }

    // Functionality
    void addRange(int left, int right) {
        int before = findBefore(left);
        int after = findAfter(right);

        // Get rid of case where it is completely encapuslated
        if( (before >= 0) && (before == after) ) // there is a range before and after, and it's the same one
            return;

        bool overlapsLeft = ( (before >= 0) && (stop[before] >= (left-1)) );
        bool overlapsRight = ( (after >= 0) && (start[after] <= (right+1)) );


        // New range overlaps with the left of a prexisting range
        if(overlapsLeft && !overlapsRight){
            stop[before] = right; // merge with left interval
            return;
        }
        // New range overlaps with the right of a prexisting range
        if(!overlapsLeft && overlapsRight){
            start[after] = left; // merge with right interval
            return;
        }
        // New range overlaps with both left and right ranges
        if(overlapsLeft && overlapsRight){
            // Merge left and right intervals
            stop[before] = stop[after]; // stop of right becomes stop of left

            start.erase(start.begin() + after); // remove the right interval
            stop.erase(stop.begin() + after);
            return;
        }

        // New range has no overlap
        if(!overlapsLeft && !overlapsRight){
            int idx = max(before+1, 0); // insert after whatever range started before, if any
            start.insert(start.begin()+idx, left);
            stop.insert(stop.begin()+idx, right);
        }
    }
    
    bool queryRange(int left, int right) {
        int idx = findBefore(left);
        if( (idx >= 0) && (stop[idx] >= right) ){
            return true;
        }
        return false;
    }
    
    void removeRange(int left, int right) {
        
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */


/*
A Range Module is a module that tracks ranges of numbers. Design a data structure to track the ranges represented as half-open intervals and query about them.

A half-open interval [left, right) denotes all the real numbers x where left <= x < right.

Implement the RangeModule class:

RangeModule() Initializes the object of the data structure.
void addRange(int left, int right) Adds the half-open interval [left, right), tracking every real number in that interval. Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval [left, right) that are not already tracked.
boolean queryRange(int left, int right) Returns true if every real number in the interval [left, right) is currently being tracked, and false otherwise.
void removeRange(int left, int right) Stops tracking every real number currently being tracked in the half-open interval [left, right).
 

Example 1:

Input
["RangeModule", "addRange", "removeRange", "queryRange", "queryRange", "queryRange"]
[[], [10, 20], [14, 16], [10, 14], [13, 15], [16, 17]]
Output
[null, null, null, true, false, true]

Explanation
RangeModule rangeModule = new RangeModule();
rangeModule.addRange(10, 20);
rangeModule.removeRange(14, 16);
rangeModule.queryRange(10, 14); // return True,(Every number in [10, 14) is being tracked)
rangeModule.queryRange(13, 15); // return False,(Numbers like 14, 14.03, 14.17 in [13, 15) are not being tracked)
rangeModule.queryRange(16, 17); // return True, (The number 16 in [16, 17) is still being tracked, despite the remove operation)
 
*/