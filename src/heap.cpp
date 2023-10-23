#include "../include/min_heap.h"

int main (void) {

    int vec[] = {4, 2, 8, 7, 1, 5, 3, 6};
    int size = 8;

    min_heap heap;
    for(int i = 0; i < size; i++){
        heap.push(vec[i]);
    }
    heap.print();

    cout << endl;

    for(int i = 0; i < size; i++){
        vec[i] = heap.pop();
    }

    cout << endl;

    for(int i = 0; i < size; i++){
        cout << vec[i] << " ";
    }

    cout << endl;

    heap.print();
}