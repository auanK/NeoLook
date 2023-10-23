#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include <iostream>
#include <stdexcept>

template <typename type>
class min_heap {
   private:
    int m_size;
    int m_capacity;
    type *ptr;

    void up(int index) {
        if (index == 0) {
            return;
        }

        int daddy = (index - 1) / 2;

        if (ptr[daddy] > ptr[index]) {
            swap(&ptr[daddy], &ptr[index]);
            up(daddy);
        }
    }

    void down(int index) {
        int index_smaller = (index * 2) + 1;

        if (index_smaller >= this->m_size) {
            return;
        }

        if ((index_smaller + 1) < this->m_size) {
            if (ptr[index_smaller] > ptr[index_smaller + 1]) {
                index_smaller += 1;
            }
        }

        if (ptr[index] > ptr[index_smaller]) {
            swap(&ptr[index], &ptr[index_smaller]);
            down(index_smaller);
        }
    }

    void reserve() {
        int *aux = new int[m_capacity * 2];
        for (int i = 0; i < m_size; i++) {
            aux[i] = ptr[i];
        }

        delete[] ptr;
        ptr = aux;

        m_capacity *= 2;
    }

    void swap(type *a, type *b) {
        type aux = *a;
        *a = *b;
        *b = aux;
    }

   public:
    min_heap() {
        this->m_size = 0;
        this->m_capacity = 1;
        this->ptr = new type[m_capacity];
    }

    ~min_heap() { 
        delete[] ptr; 
    }

    int size() { 
        return this->m_size; 
    }

    int capacity() { 
        return this->m_capacity; 
    }

    type value(int index) { 
        return ptr[index]; 
    }

    void push(type value) {
        ptr[m_size] = value;
        m_size++;

        if (m_size == m_capacity) {
            reserve();
        }

        up(m_size - 1);
    }

    int pop() {
        if (m_size == 0) {
            throw std::out_of_range("Heap is empty");
        }

        type aux = ptr[0];

        swap(&ptr[0], &ptr[m_size - 1]);
        m_size--;

        down(0);

        return aux;
    }

    void print() {
        for (int i = 0; i < m_size; i++) {
            std::cout << ptr[i] << " ";
        }
        std::cout << std::endl;
    }

    void printTree(int index, int level = 0) {
        if (index >= this->m_size) {
            return;
        }

        printTree((index * 2) + 2, level + 1);

        for (int i = 0; i < level; i++) {
            std::cout << "\t";
        }

        std::cout << ptr[index] << std::endl;
       
        printTree((index * 2) + 1, level + 1);
    }
};
#endif