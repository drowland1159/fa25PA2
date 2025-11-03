//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    cout << "after build leaf" << endl;
    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    cout << "after build encoding tree" << endl;
    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    cout << "after generate codes" << endl;
    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);
    cout << "after encode message" << endl;

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)

    MinHeap heap = MinHeap();
    // I replaced the while with a for
    // nextFree is the next INDEX that can be used. (I don't know why it took me that long to understand that)
    for (int i = 0; i < nextFree; i++) { // 0 -> nextFree - 1 as those are used indexs
        heap.push(i,weightArr);
    }
    while (heap.size > 1) {
        int heapNumOne = heap.pop(weightArr);
        int heapNumTwo = heap.pop(weightArr);
        leftArr[nextFree] = heapNumOne; // nextFree == parent nodes index
        rightArr[nextFree] = heapNumTwo;
        weightArr[nextFree] = weightArr[heapNumOne] + weightArr[heapNumTwo];
        heap.push(nextFree, weightArr);
        nextFree++;
    }
    return heap.pop(weightArr); // root index
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    string binaryCode = "";
    stack<pair<int, string>> stack;
    stack.push(make_pair(root, ""));
    while (!stack.empty()) {
        pair<int, string> current = stack.top();
        int index = current.first;
        string str = current.second;
        stack.pop();
        if (leftArr[index] == -1) { // looking at createLeafNodes, -1 should be it
            codes[index] = binaryCode;
            continue;
        } else {

        }

    }

    // do {
    //     pair<int, string> parent = stack.top();
    //     int index = parent.first;
    //     string str = parent.second;
    //
    //     if (!str.empty()) {
    //         codes[index] = binaryCode;
    //         continue;
    //     }
    //     binaryCode.append("0"); // adds a 0
    //     stack.push(make_pair(leftArr[index], (charArr[leftArr[index]] + "")));
    //     binaryCode[binaryCode.size() - 1] = '1'; // adds a 1
    //     stack.push(make_pair(leftArr[index], (charArr[leftArr[index]] + "")));
    // } while (!stack.empty());
}


// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}