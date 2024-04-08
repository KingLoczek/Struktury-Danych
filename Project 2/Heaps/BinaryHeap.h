#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H
#include <iostream>
#include <cstdlib>
#include <utility>
#include <cassert>

#include "PriorityQueue.h"

template<typename T>
class BinaryHeap:public PriorityQueue<T>{
private:
    T* heapArray; // Array to store heap elements
    int capacity; // Maximum capacity of the heap
    int length;     // Current size of the heap

    void heapifyUp(int index){
        int parent = (index - 1) / 2;
        while (index > 0 && heapArray[parent].priority < heapArray[index].priority)
        {
            std::swap(heapArray[index], heapArray[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    };

    void heapifyDown(int index){
        while (true){    
            int leftChild = 2*index+1;
            int rightChild = 2*index+2;
            int largest = index;

            if (leftChild < length && heapArray[leftChild].priority > heapArray[largest].priority){
                largest = leftChild;
            }
            if (rightChild < length && heapArray[rightChild].priority > heapArray[largest].priority){
                largest = rightChild;
            }
            if(largest != index){
                std::swap(heapArray[index], heapArray[largest]);
                index = largest;
            }else{
                break;
            }
        }
    };
public:
    BinaryHeap(int capacity){
        this->capacity = capacity;
        length = 0;
        heapArray = new T[capacity];
    };

    ~BinaryHeap(){
        delete[] heapArray;
    };

    void insert(T element) override{
        if(length == capacity){
            capacity *=2;
            T* newArray = new T[capacity];
            for (size_t i = 0; i < length; i++)
                newArray[i] = heapArray[i];
            delete[] heapArray;
            heapArray = newArray;
        }
        heapArray[length] = element; // Add data to the end of queue
        heapifyUp(length); // Repair heap
        length++; // Increase size of queue
    };

    T extractMax() override{
        if (length == 0) {
            std::cout << "Heap is empty, cannot extract max.\n";
            return T();
        }

        T maxNode = heapArray[0];
        heapArray[0] = heapArray[length - 1];
        length--;
        heapifyDown(0);
        return maxNode;
    };

    T findMax() override{
        if (length == 0) {
            std::cout << "Heap is empty, cannot find max.\n";
            return T();
        }

        return heapArray[0];
    };

    void modifyKey(int data, int newPriority) override {
        for (int i = 0; i < length; ++i) {
            if (heapArray[i].data == data) {
                if (newPriority > heapArray[i].priority) {
                    heapArray[i].priority = newPriority;
                    heapifyUp(i);
                } else {
                    heapArray[i].priority = newPriority;
                    heapifyDown(i);
                }
                return;
            }
        }
        std::cout << "Element not found in the heap.\n";
    };

    int size() override{
        return length;
    };
};

#endif