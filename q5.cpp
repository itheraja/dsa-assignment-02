#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Job {
    string name;
    int priority;
    int arrival;

    bool operator<(const Job &other) const {

        if (priority == other.priority)
            return arrival > other.arrival;

        return priority > other.priority;
    }
};

class PriorityQueue {

private:
    priority_queue<Job> pq;
    int arrivalCounter = 0;

public:

    void push(string job, int priority) {

        arrivalCounter++;

        pq.push({job, priority, arrivalCounter});
    }

    void pop() {

        if (pq.empty()) {
            cout << "Queue Empty\n";
            return;
        }

        cout << pq.top().name << endl;
        pq.pop();
    }

    void peek() {

        if (pq.empty()) {
            cout << "Queue Empty\n";
            return;
        }

        cout << pq.top().name << endl;
    }
};

int main() {

    PriorityQueue q;

    q.push("J1",3);
    q.push("J2",1);
    q.push("J3",2);

    q.pop();

    q.push("J4",1);
    q.push("J5",3);

    q.pop();
    q.pop();

    q.push("J6",2);

    q.pop();
    q.pop();
    q.pop();

    return 0;
}
