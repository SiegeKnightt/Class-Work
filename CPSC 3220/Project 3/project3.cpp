/*
Name: Reeves Farrell
Class: CPSC 3220
Assignment: Project 3
Due Date: Thu Nov 9, 2023 11:59pm
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

struct Task {
    
    char task_id;
    int arrival_time;
    int service_time;
    int remaining_time;
    int completion_time;
    int response_time;
    int wait_time;
    int start;

    bool operator<(const Task& temp) const {
        
        return remaining_time > temp.remaining_time;
    }

    Task(char tid, int arrival, int service)
        : task_id(tid), arrival_time(arrival), service_time(service), remaining_time(service), completion_time(0), response_time(0), wait_time(0) {}
};

void fifo(vector<Task>& tasks);
void sjf(vector<Task>& tasks);
void rr(vector<Task>& tasks, int time_slice);

int main(int argc, char *argv[]) {

    if (argc == 1) {

        cout << "Error: No scheduling policy listed" << endl;

        return 1;
    }

    // Gets file input for tasks
    ifstream s(argv[2]);

    vector<Task> tasks;
    
    string policy;
    char tid = 'A';
    int arrival = 0;
    int service = 0;
    int time_slice = 1;

    // Determines scheduling policy
    if (strcmp(argv[1], "-fifo") == 0) {

        policy = "fifo";
    }
    else if (strcmp(argv[1], "-sjf") == 0) {
        
        policy = "sjf";
    }
    else if (strcmp(argv[1], "-rr") == 0) {

        policy = "rr";
    }

    Task t(tid, arrival, service);
    
    // Gets input from cmd line argument file
    while (cin >> arrival >> service && !s.eof()) {

        t.task_id = tid;
        t.arrival_time = arrival;
        t.service_time = service;
        t.remaining_time = service;
        tasks.push_back(t);

        if (tid == 'Z') {

            break;
        }

        tid++;
    }

    // Prints the policy title
    if (policy == "fifo") {

       fifo(tasks);
    }
    else if (policy == "sjf") {
                
        sjf(tasks);
    }
    else if (policy == "rr") {

       rr(tasks, time_slice);
    }

    return 0;
}

void fifo(vector<Task>& tasks) {
    
    int current_time = 0;

    queue<Task*> task_queue;
    vector<Task>::iterator it = tasks.begin();

    Task* current = nullptr; 
    int start_time;

    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        
        return a.arrival_time < b.arrival_time;
    });

    cout << "FIFO scheduling results" << endl << endl;
    cout << "time   cpu   ready queue (tid/rst)" << endl;
    cout << "----   ---   ---------------------" << endl;

    for (auto& task : tasks) {
        
        task.wait_time = 0;
        task.response_time = -1;
    }

    while(it != tasks.end() || !task_queue.empty() || current != nullptr) {
        
        while(it != tasks.end() && it->arrival_time <= current_time) {
            
            task_queue.push(&(*it));
            it++;
        }

        if (!current && !task_queue.empty()) {
            
            current = task_queue.front();
            task_queue.pop();

            start_time = current_time; 

            if (current->response_time == -1) { 
                
                current->response_time = ( current_time - current->arrival_time) + (current->wait_time + current->service_time);
            }
        }

        cout << setw(3) << current_time;
        
        if (current) {
            
            cout << setw(5) << current->task_id << current->remaining_time << setw(5);
        } 
        else {
            
            cout << setw(6) << " ";
        }

        queue<Task*> temp = task_queue;

        if (!temp.empty()) {

            while (!temp.empty()) {
                
                Task* temp2 = temp.front();
                temp.pop();

                if (temp.size() >= 1) {
                    
                    cout  << setw(5) << temp2->task_id << temp2->remaining_time << ", ";
                }
                else {
                    
                    cout << temp2->task_id << temp2->remaining_time << " ";
                }
            }
        }
        else {
            
            cout << setw(6) << "--";
        }
        
        cout << endl;

        if (current) {

            current->remaining_time--;
            
            if (current->remaining_time == 0) { 
                
                current->completion_time = current_time + 1;
                current->wait_time = start_time - current->arrival_time;
                current = nullptr;
            }
            
        }

        current_time++;
    }

    cout << endl << "     arrival service completion response wait";
    cout << endl << "tid   time    time      time      time   time";
    cout << endl << "---  ------- ------- ---------- -------- ----" << endl;
    
    for (const Task& task : tasks) {
       
        cout << " " << task.task_id << setw(7) << task.arrival_time << setw(8) << task.service_time << setw(10)
        << task.completion_time << setw(10) << task.response_time << setw(7) << task.wait_time << endl;
    }

    cout << endl << "service wait";
    cout << endl << " time   time" << endl;
    cout << "------- ----" << endl;
    
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        
        if (a.service_time == b.service_time)  {
            
            return a.arrival_time < b.arrival_time;
        }
        return a.service_time < b.service_time;
    });

    for (const Task& task : tasks) {
        
        cout << setw(4) << task.service_time;
        cout << setw(7) << task.wait_time << endl;
    }
}

void sjf(vector<Task>& tasks) {

    int current_time = 0;

    priority_queue<Task> ready_queue;
    vector<Task> list_tasks;
    vector<Task> completed;

    for (auto& task : tasks) {
            
        task.wait_time = 0;
        task.response_time = -1;
    }

    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        
        return a.arrival_time < b.arrival_time;
    });

    list_tasks = tasks;

    cout << "SJF(preemptive) scheduling results" << endl << endl;
    cout << "time   cpu   ready queue (tid/rst)" << endl;
    cout << "----   ---   ---------------------" << endl;

    while (!ready_queue.empty() || !tasks.empty()) {
        
        while (!tasks.empty() && tasks.front().arrival_time <= current_time) {
            
            ready_queue.push(tasks.front());
            tasks.erase(tasks.begin());
        }

        if (!ready_queue.empty()) {
            
            Task current = ready_queue.top();

            cout << setw(3) << current_time << "    " << current.task_id << current.remaining_time << setw(5);
            ready_queue.pop();

            priority_queue<Task> temp = ready_queue;

            while (!temp.empty()) {
                
                const Task& q_task = temp.top();
                
                if(temp.size() > 1) {

                    cout << q_task.task_id << q_task.remaining_time << ", ";
                }
                else {

                    cout << q_task.task_id << q_task.remaining_time << " ";
                }

                temp.pop();
            }
            
            if (ready_queue.empty()) {
                
                cout << setw(6) << "--";
            }

            cout << endl;

            current.remaining_time--;

            if (current.remaining_time == 0) {
                
                current.completion_time = current_time + 1;
                completed.push_back(current);
            } 
            else {
                
                ready_queue.push(current);
            }
        } 
        else {

            cout << setw(3) << current_time << setw(12) <<"--" << std::endl;
        }

        current_time++;
    }

    cout << endl << "     arrival service completion response wait" << endl;
    cout << "tid   time    time      time      time   time" << endl;
    cout << "---  ------- ------- ---------- -------- ----" << endl;
    
    for (const Task& t : list_tasks) {

        auto it = find_if(completed.begin(), completed.end(), [&t](const Task& ct) {
            
            return ct.task_id == t.task_id;
        });

        if (it != completed.end()) {
            
            cout << " " << it->task_id << setw(7) << it->arrival_time << setw(8) << it->service_time << setw(10) 
            << it->completion_time << setw(10) << it->completion_time - it->arrival_time << setw(7)
            << it->completion_time - it->arrival_time - it->service_time << endl;
        }
    }

    cout << endl << "service wait";
    cout << endl << " time   time" << endl;
    cout << "------- ----" << endl;

    sort(completed.begin(), completed.end(), [](const Task& a, const Task& b) {
        
        if (a.service_time == b.service_time) {
            
            return a.arrival_time < b.arrival_time;
        }

        return a.service_time < b.service_time;
    });

    for (const Task& t : completed) {
        
        auto it = find_if(completed.begin(), completed.end(), [&t](const Task& t2) {
            
            return t2.task_id == t.task_id;
        });

        cout << setw(4) << it->service_time;
        cout << setw(7) << it->completion_time - it->arrival_time - it->service_time << endl;
    }
}

void rr(vector<Task>& tasks, int time_slice) {
    
    int current_time = 0;

    queue<Task*> task_queue;
    vector<Task*> list_tasks;
    size_t it = 0;

    Task* current = nullptr;

    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        
        return a.arrival_time < b.arrival_time;
    });

    cout << "RR scheduling results (time slice is " << time_slice << ")" << endl << endl;
    cout << "time   cpu   ready queue (tid/rst)" << endl;
    cout << "----   ---   ---------------------" << endl;

    while (it < tasks.size() || !task_queue.empty() || current != nullptr) {
        
        while (it < tasks.size() && tasks[it].arrival_time <= current_time) {
            
            list_tasks.push_back(&tasks[it]);
            task_queue.push(&tasks[it]);
            it++;
        }

        if (current == nullptr || current_time % time_slice == 0 || current->remaining_time == 0) {

            if (current != nullptr && current->remaining_time > 0) {

                task_queue.push(current);
            }

            if (!task_queue.empty()) {

                current = task_queue.front();
                task_queue.pop();

                if (current->start == -1) {

                    current->start = current_time;
                }
            }
            else {

                current = nullptr;
            }
        }
    
        if (current == nullptr && task_queue.empty() && it >= tasks.size()) {
            
            break;
        }

        cout << setw(3) << current_time;

        if (current != nullptr) {
            
            cout << setw(5) << current->task_id << current->remaining_time << setw(5);
        } 
        else {
            
            cout << setw(6) << " ";
        }

        queue<Task*> temp = task_queue;

        if (!temp.empty()) {
            
            while (!temp.empty()) {
                
                Task* temp2 = temp.front();
                temp.pop();

                if (temp.size() >= 1) {
                    
                    cout << setw(5) << temp2->task_id << temp2->remaining_time << ", ";
                } 
                else {
                    
                    cout << temp2->task_id << temp2->remaining_time << " ";
                }
            }
        } 
        else {
            
            cout << setw(6) << "--";
        }

        cout << endl;

        if (current) {
            
            current->remaining_time = current->remaining_time - 1;

            if (current->remaining_time == 0) {
                
                current->completion_time = current_time + 1;
                current->wait_time = current->completion_time - current->arrival_time - current->service_time;
                current = nullptr;
            } 
        }

        current_time++;
    }

    cout << endl << "     arrival service completion response wait";
    cout << endl << "tid   time    time      time      time   time";
    cout << endl << "---  ------- ------- ---------- -------- ----" << endl;

    for (const Task& task : tasks) {
        
        cout << " " << task.task_id << setw(7) << task.arrival_time << setw(8) << task.service_time << setw(10) 
            << task.completion_time << setw(10) << task.completion_time - task.arrival_time << setw(7)
            << task.completion_time - task.arrival_time - task.service_time << endl;
    }

    cout << endl << "service wait";
    cout << endl << " time   time" << endl;
    cout << "------- ----" << endl;

    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        
        if (a.service_time == b.service_time) {
            
            return a.arrival_time < b.arrival_time;
        }

        return a.service_time < b.service_time;
    });

    for (const Task& task : tasks) {
        
        cout << setw(4) << task.service_time;
        cout << setw(7) << task.wait_time << endl;
    }
}