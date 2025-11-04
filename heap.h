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
        if (size == 0) { // if index is empty then return -1
            return -1;
        }
        int root = data[0];
        data[0] = data[size-1]; // puts last number as root.
        size--; // decrements size as root was removed
        downheap(0, weightArr); // calls downheap to fix the heap
        return root; // returns the old root
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        if (pos == 0) return; // base ase
        // REMINDER :: this is starting at the bottom-most index and is going upwards
        int parentNode = (pos - 1) / 2; // locates the parent node of the curr pos
        // REMINDER :: weightArr is the weights, data is the heap.
        if (weightArr[data[parentNode]] > weightArr[data[pos]]) { // instead of weightArr[parentNode] we do weightArr[data[parentNode]]
            int tmp = data[parentNode]; // if current node is smaller than parent then parent and pos swap places
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
        if (rightChild > size && leftChild > size) { // if right and left child are out of bounds then return
            return;
        } else if (rightChild >= size) { // rightChild >= size cause if size = 64 then it contains 0 - 63. Needs to be inclusive
            smallestChild = leftChild; // if rightChild is out of bounds but leftChild isn't then smallest child is left child
        } else {
            if (weightArr[data[leftChild]] > weightArr[data[rightChild]]) { // if leftchild > rightchild
                smallestChild = rightChild; // NOTE :: This works as smallestChild is assigned to leftChild initally
            }
        }
        if (weightArr[data[pos]] > weightArr[data[smallestChild]]) { // if pos > smallestChild then swap
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