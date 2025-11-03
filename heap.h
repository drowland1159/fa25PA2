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
            upheap(size = 1, weightArr);
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
        if (pos == 0) return;

        int parentNode = (pos - 1) / 2;
        if (weightArr[parentNode] > weightArr[pos]) {
            int tmp = weightArr[parentNode];
            weightArr[parentNode] = weightArr[pos];
            weightArr[pos] = tmp;
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
        if (rightChild > size && leftChild > size) {
            return;
        } else if (rightChild > size) {
            smallestChild = leftChild;
        } else {
            if (weightArr[leftChild] > weightArr[rightChild]) {
                smallestChild = rightChild;
            }
        }
        if (weightArr[pos] > weightArr[smallestChild]) {
            int tmp = weightArr[smallestChild];
            weightArr[smallestChild] = weightArr[pos];
            weightArr[pos] = tmp;
        } else {
            return;
        }
        downheap(smallestChild, weightArr);
    }
};

#endif