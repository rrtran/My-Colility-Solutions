#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    Node() : key(0), data(0), link(nullptr) {}
    Node(int key) : key(key), data(0), link(nullptr) {}
    int getKey() { return key; }
    int getData() { return data; }
    Node* getLink() { return link; }
    void setKey(int key) { this->key = key; }
    void setData(int data) { this->data = data; }
    void setLink(Node* link) { this->link = link; }
    ~Node() { link = nullptr; }
private:
    int key;
    int data;
    Node* link;
};

class HashTable {
public:
    HashTable() {
        capacity = 100000;
        table = new Node * [capacity];
        used = 0;
    }

    void insert(int key) {
        int hashValue = key % capacity;
        if (table[hashValue] == nullptr) {
            Node* node = new Node(key);
            table[hashValue] = node;
            used++;
            return;
        }
        else {
            for (int j = 0; j < capacity; j++) {
                int hashValuePrime = 7 - key % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    Node* node = new Node(key);
                    table[hashValue] = node;
                    used++;
                    return;
                }
            }
            return;
        }
    }

    bool lookup(int key) {
        int hashValue = key % capacity;
        if (table[hashValue] == nullptr) {
            return false;
        }
        else if (table[hashValue]->getKey() == key) {
            return true;
        }
        else {
            for (int j = 0; j < capacity; j++) {
                int hashValuePrime = 7 - key % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    return false;
                }
                else if (table[hashValue]->getKey() == key) {
                    return true;
                }
            }

            return false;
        }
    }

    int size() {
        return used;
    }
private:
    Node** table;
    int capacity;
    int used;
};

int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)

    int maxElement = 0;
    for (int i = 0; i < A.size(); i++) {
        if (maxElement < A[i]) {
            maxElement = A[i];
        }
    }

    HashTable table;
    for (int i = 0; i < A.size(); i++) {
        if (table.lookup(A[i]) == false) {
            table.insert(A[i]);
        }
        else {
            return 0;
        }
    }

    if (table.size() == maxElement) {
        return 1;
    }

    return 0;
}