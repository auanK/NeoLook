#include <iostream>

#include "../include/min_heap.h"

using namespace std;

int main() {
    int vec[] = {4, 2, 8, 7, 1, 5, 3, 6};
    int size = 8;

    min_heap<int> heap;

    for (int i = 0; i < size; i++) {
        heap.push(vec[i]);
        cout << endl;
        heap.printTree(0);
        cout << endl;
        cout << "------------------" << endl;
    }

    heap.print();

    cout << heap.value(7) << endl;
    return 0;
}
