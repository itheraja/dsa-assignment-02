#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (heap[parent] <= heap[index])
                break;

            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();

        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left] < heap[smallest])
                smallest = left;

            if (right < size && heap[right] < heap[smallest])
                smallest = right;

            if (smallest == index)
                break;

            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    MinHeap(vector<int> arr) {
        heap = arr;
    }

    void print() {
        for (int x : heap)
            cout << x << " ";
        cout << endl;
    }

    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        if (heap.empty())
            return -1;

        int minValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);

        return minValue;
    }

    void decreaseKey(int index, int newValue) {
        if (index < 0 || index >= heap.size())
            return;

        heap[index] = newValue;
        heapifyUp(index);
    }
};

int main() {
    vector<int> arr = {5,11,8,14,17,9,12,20,16,19};

    MinHeap h(arr);

    cout << "Initial Heap: ";
    h.print();

    h.insert(6);
    cout << "After Insert 6: ";
    h.print();

    h.insert(4);
    cout << "After Insert 4: ";
    h.print();

    cout << "Extracted: " << h.extractMin() << endl;
    h.print();

    cout << "Extracted: " << h.extractMin() << endl;
    h.print();

    h.decreaseKey(7, 3);
    cout << "After decreaseKey: ";
    h.print();

    return 0;
}
