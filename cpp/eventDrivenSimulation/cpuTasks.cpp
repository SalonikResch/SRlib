/*
You are given n​​​​​​ tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the i​​​​​​th​​​​ task will be available to process at enqueueTimei and will take processingTimei to finish processing.

You have a single-threaded CPU that can process at most one task at a time and will act in the following way:

If the CPU is idle and there are no available tasks to process, the CPU remains idle.
If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
Once a task is started, the CPU will process the entire task without stopping.
The CPU can finish a task then start a new one instantly.
Return the order in which the CPU will process the tasks.

 

Example 1:

Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]
Explanation: The events go as follows: 
- At time = 1, task 0 is available to process. Available tasks = {0}.
- Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
- At time = 2, task 1 is available to process. Available tasks = {1}.
- At time = 3, task 2 is available to process. Available tasks = {1, 2}.
- Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
- At time = 4, task 3 is available to process. Available tasks = {1, 3}.
- At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
- At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
- At time = 10, the CPU finishes task 1 and becomes idle.
Example 2:

Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
Output: [4,3,2,0,1]
Explanation: The events go as follows:
- At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
- Also at time = 7, the idle CPU starts processing task 4. Available tasks = {0,1,2,3}.
- At time = 9, the CPU finishes task 4 and starts processing task 3. Available tasks = {0,1,2}.
- At time = 13, the CPU finishes task 3 and starts processing task 2. Available tasks = {0,1}.
- At time = 18, the CPU finishes task 2 and starts processing task 0. Available tasks = {1}.
- At time = 28, the CPU finishes task 0 and starts processing task 1. Available tasks = {}.
- At time = 40, the CPU finishes task 1 and becomes idle.
*/

#define NEWJOB 0
#define JOBFINISH 1

struct job{
    unsigned long int duration;
    int id;
};

struct event{
    int eventType;
    unsigned long int time;
    job *j = NULL;
};

// Operator to order events by time
struct OrderByTime{
    bool operator()(event *lhs, event *rhs){
        return lhs->time > rhs->time;
    }
};

// Operator to order tasks by duration
struct OrderByDuration{
    bool operator()(job *lhs, job *rhs){
        if( lhs->duration > rhs->duration ){ // first by duration
            return true;
        }else if( lhs->duration == rhs->duration ){ // sort tie by id
            return lhs->id > rhs->id;
        }else{
            return false;
        }
    }
};

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        // Vector storing jobs as they finish
        vector<int> order;

        // A priority queue to hold events
        priority_queue<event *, vector<event *>, OrderByTime> events;
        // A priority queue to hold jobs by shortest duration
        priority_queue<job *, vector<job *>, OrderByDuration> jobs;

        // Fill the event queue with the tasks
        for(int i=0;i<tasks.size();i++){
            event *e = new event();
            e->eventType = NEWJOB;
            e->time = tasks[i][0]; // time it shows up
            e->j = new job();
            e->j->duration = tasks[i][1]; // how long it lasts
            e->j->id = i;
            events.push(e);
        }

        // Keep track of whether CPU is busy
        bool idle = true;

        // Keep going while stuff is still happening
        while(!events.empty()){
            // The time of the next event
            unsigned long int time = events.top()->time;
            // Pull all events out that happen at the same time
            while(!events.empty() && events.top()->time == time){
                event *e = events.top();
                events.pop();
                // React based on type
                if(e->eventType == NEWJOB){
                    jobs.push(e->j); // put into queue
                }else{ //e->eventType == JOBFINISH
                    idle = true; // free CPU
                }
            }

            // After pulling all events, schedule new job if idle
            if(idle && !jobs.empty()){
                idle = false; // not idle anymore
                job *j = jobs.top(); // take shortest (with lowest id) job
                jobs.pop();
                order.push_back(j->id); // Since CPU will finish a task once it starts, can mark as completed
                event *e = new event();  // there will now be an event in the future when this jobs finishes
                e->eventType = JOBFINISH; // finish type
                e->time = time + j->duration; // duration into the future
                events.push(e);
            }
        }

        return order;
    }
};