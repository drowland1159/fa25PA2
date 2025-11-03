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
            data[size] = idx; // We are saving the idx from weightArr to the bottom of the heap
            size++;
            upheap(size - 1, weightArr); // calls upheap on idx to place it properly in the heap.
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
        int root = data[0];
        data[0] = data[size-1];
        size--;
        downheap(0, weightArr);
        return root; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        if (pos == 0) return;

        int parentNode = (pos - 1) / 2;
        // REMINDER :: weightArr is the weights, data is the heap.
        if (weightArr[data[parentNode]] > weightArr[data[pos]]) { // instead of weightArr[parentNode] we do weightArr[data[parentNode]]
            int tmp = data[parentNode];
            data[parentNode] = data[pos];
            data[pos] = tmp;
            upheap(parentNode, weightArr);
        } else {
            return;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        int leftChild = 2 * pos + 1;
        int rightChild = 2 * pos + 2;
        int smallestChild = leftChild;
        // REMINDER :: weightArr is the weights, data is the heap.
        if (rightChild > size && leftChild > size) {
            return;
        } else if (rightChild >= size) { // rightChild >= size cause if size = 64 then it contains 0 - 63. Needs to be inclusive
            smallestChild = leftChild;
        } else {
            if (weightArr[data[leftChild]] > weightArr[data[rightChild]]) {
                smallestChild = rightChild;
            }
        }
        if (weightArr[data[pos]] > weightArr[data[smallestChild]]) {
            int tmp = data[smallestChild];
            data[smallestChild] = data[pos];
            data[pos] = tmp;
        } else {
            return;
        }
        downheap(smallestChild, weightArr);
    }
};

#endif