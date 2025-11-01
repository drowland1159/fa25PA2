//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        if (size < 64) {
            data[size] = weightArr[size];
            size++;
            upheap(0, weightArr);
            return;
        }
        cout << idx << " cannot be entered as Heap is full." << endl;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) {
            // cout << "Heap is empty." << endl;
            return -1;
        }
        int num = data[--size];
        size--;
        downheap(0, weightArr);
        return num; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        if (pos == size)
            return;
        if (weightArr[pos] > weightArr[size]) {
            swap(pos, size);
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        if (size == pos) {
            return;
        }
        if (weightArr[pos] > weightArr[size]) {
            swap(pos, size);
        }
    }
};

#endif