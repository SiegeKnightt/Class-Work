#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

struct Task {
    int task_id;
    int arrival_time;
    int service_time;
    int remaining_time;
    int response_time;
    int completion_time;
    int wait_time;
};

int main() {
    int current_time = 0;
    std::string policy = "fifo"; // Change this to the desired policy

    // Updated tasks with arrival and service times
    std::vector<Task> tasks = {
        {1, 3, 4, 4, -1, -1, -1},  // Task ID 1, arrives at 3, service time 4
        {2, 10, 4, 4, -1, -1, -1}, // Task ID 2, arrives at 10, service time 4
        {3, 10, 2, 2, -1, -1, -1}  // Task ID 3, arrives at 10, service time 2
    };

    std::queue<Task> ready_queue;

    while (true) {
        bool any_task_added = false;
        for (auto &t : tasks) {
            if (t.arrival_time == current_time) {
                ready_queue.push(t);
                t.response_time = current_time - t.arrival_time;
                any_task_added = true;
            }
        }

        if (ready_queue.empty() && !any_task_added) {
            break;
        }

        std::cout << current_time;

        if (!ready_queue.empty()) {
            Task current = ready_queue.front();
            ready_queue.pop();

            std::cout << "\t" << current.task_id << " " << current.remaining_time << std::endl;

            current.remaining_time--;

            if (current.remaining_time == 0) {
                current.completion_time = current_time + 1;
                current.wait_time = current.completion_time - current.arrival_time - current.service_time;
            } else {
                ready_queue.push(current);
            }
        } else {
            std::cout << std::endl;
        }

        ++current_time;
    }

    return 0;
}
