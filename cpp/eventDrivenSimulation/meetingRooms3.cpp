#include <bits/stdc++.h>
using namespace std;

// An event structure so we can do event-driven simulation
struct event{
    bool start; // true for a meeting start, false for a meeting end
    int room; // room that the meeting will be in
    long unsigned int time; // time of event
    long unsigned int duration; // length of meeting, only meaningful for starts
};

// Define an operator so we can sort meetings by end time
// bool operator<( const event *lhs, const event *rhs){
//     return lhs->time < rhs->time;
// }
bool eventcompare( event *lhs, event *rhs){
    return lhs->time < rhs->time;
}

struct OrderByTime{
    bool operator()(event *lhs, event *rhs){
        return lhs->time > rhs->time;
    }
};


class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Initialize count for each room
        long unsigned int *bookings = new long unsigned int[n]();

        // A priority queue for meetings
        priority_queue <event*, vector<event*>, OrderByTime> pq_meetings;
        // Populate with starts 
        for(int i=0;i<meetings.size();i++){
            // Meeting start
            event *e = new event();
            e->start = true;
            e->time = meetings[i][0];
            e->duration = meetings[i][1]-meetings[i][0];
            pq_meetings.push(e);
        }
        // A priority queue for meeting rooms
        priority_queue <int, vector<int>, greater<int> > pq_rooms;
        for(int i=0;i<n;i++)
            pq_rooms.push(i);

        long unsigned int time = 0;
        vector<event*> waiting_meetings; // meetings that were delayed and waiting
        // While events still in queue
        while(pq_meetings.empty() == false){
            // Take event from front
            event *e = pq_meetings.top();
            // Process all events that happen at this time
            time = e->time;
            while(!pq_meetings.empty() && pq_meetings.top()->time == time){
                e = pq_meetings.top();
                pq_meetings.pop();
                // If it is a meeting end, free up a room
                if(!e->start){
                    pq_rooms.push(e->room);
                }else{
                    // It is a meeting start - put it into the waiting queue
                    waiting_meetings.push_back(e);
                }
            }

            // Schedule any waiting meetings that we can
            while(!pq_rooms.empty() && waiting_meetings.size() > 0){
                int room = pq_rooms.top(); // Will give the lowest room nmber
                pq_rooms.pop();
                bookings[room] += 1; // Increment room usage
                event *t = new event(); // A new event for the meeting end
                t->start = false;
                t->room = room;
                t->time = time + waiting_meetings[0]->duration;
                pq_meetings.push(t); // Push it into the meeting queue
                waiting_meetings.erase(waiting_meetings.begin()); // Clear the scheduled meeting
            } 
        }

        // Return the room with most meetings
        int maxBookings = bookings[0];
        int idx = 0;
        for(int i=0;i<n;i++){
            if(bookings[i] > maxBookings){
                maxBookings = bookings[i];
                idx = i;
            }
        }
        return idx;
    }

};

// You are given an integer n. There are n rooms numbered from 0 to n - 1.

// You are given a 2D integer array meetings where meetings[i] = [starti, endi] means that a meeting will be held during the half-closed time interval [starti, endi). All the values of starti are unique.

// Meetings are allocated to rooms in the following manner:

// Each meeting will take place in the unused room with the lowest number.
// If there are no available rooms, the meeting will be delayed until a room becomes free. The delayed meeting should have the same duration as the original meeting.
// When a room becomes unused, meetings that have an earlier original start time should be given the room.
// Return the number of the room that held the most meetings. If there are multiple rooms, return the room with the lowest number.

// A half-closed interval [a, b) is the interval between a and b including a and not including b.

 

// Example 1:

// Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
// Output: 0
// Explanation:
// - At time 0, both rooms are not being used. The first meeting starts in room 0.
// - At time 1, only room 1 is not being used. The second meeting starts in room 1.
// - At time 2, both rooms are being used. The third meeting is delayed.
// - At time 3, both rooms are being used. The fourth meeting is delayed.
// - At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
// - At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
// Both rooms 0 and 1 held 2 meetings, so we return 0. 
// Example 2:

// Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
// Output: 1
// Explanation:
// - At time 1, all three rooms are not being used. The first meeting starts in room 0.
// - At time 2, rooms 1 and 2 are not being used. The second meeting starts in room 1.
// - At time 3, only room 2 is not being used. The third meeting starts in room 2.
// - At time 4, all three rooms are being used. The fourth meeting is delayed.
// - At time 5, the meeting in room 2 finishes. The fourth meeting starts in room 2 for the time period [5,10).
// - At time 6, all three rooms are being used. The fifth meeting is delayed.
// - At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting starts in room 1 for the time period [10,12).
// Room 0 held 1 meeting while rooms 1 and 2 each held 2 meetings, so we return 1. 
 

// Constraints:

// 1 <= n <= 100
// 1 <= meetings.length <= 105
// meetings[i].length == 2
// 0 <= starti < endi <= 5 * 105
// All the values of starti are unique.