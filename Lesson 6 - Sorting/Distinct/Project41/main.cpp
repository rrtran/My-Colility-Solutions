#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    Node() : key(0), data(0) {}
    Node(int key) : key(key), data(0) {}
    int getKey() { return key; }
    int getData() { return data; }
    void setKey(int key) { this->key = key; }
    void setData(int data) { this->data = data; }
    ~Node() { }
private:
    long key;
    int data;
};

class HashTable {
public:
    HashTable() {
        capacity = 200000;
        table = new Node * [capacity];
        used = 0;
    }

    void insert(int key) {
        int absoluteValueOfKey;
        if (key < 0) absoluteValueOfKey = key * -1;
        else absoluteValueOfKey = key;
        int hashValue = absoluteValueOfKey % capacity;
        if (table[hashValue] == nullptr) {
            Node* node = new Node(key);
            table[hashValue] = node;
            used++;
            return;
        }
        else {
            for (int j = 0; j < capacity; j++) {
                int hashValuePrime = 7 - absoluteValueOfKey % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    Node* node = new Node(key);
                    table[hashValue] = node;
                    used++;
                    return;
                }
            }
        }
    }

    bool lookup(int key) {
        int absoluteValueOfKey;
        if (key < 0) absoluteValueOfKey = key * -1;
        else absoluteValueOfKey = key;
        int hashValue = absoluteValueOfKey % capacity;
        if (table[hashValue] == nullptr) {
            return false;
        }
        else if (table[hashValue]->getKey() == key) {
            return true;
        }
        else {
            for (int j = 0; j < capacity; j++) {
                int hashValuePrime = 7 - absoluteValueOfKey % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    return false;
                }
                else if (table[hashValue]->getKey() == key) {
                    return true;
                }
            }
        }
    }

    int size() {
        return used;
    }

    void destroyTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == nullptr) {
                // skip
            }
            else {
                delete table[i];
                table[i] = nullptr;
            }
        }
        delete[] table;
        used = 0;
        capacity = 0;
    }

    ~HashTable() {
        destroyTable();
    }
private:
    Node** table;
    int capacity;
    int used;
};

int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    HashTable table;
    int count = 0;
    for (int i = 0; i < A.size(); i++) {
        if (table.lookup(A[i]) == false) {
            table.insert(A[i]);
            count++;
        }
    }
    return count;
}

int main() {
}