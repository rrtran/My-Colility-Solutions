#include <vector>

using namespace std;    

class Record {
public:
    Record() : key(0), data(0) {}
    Record(int key, int data) : key(key), data(data) {}
    int getKey() { return key; }
    int getData() { return data; }
    bool getDeleted() { return deleted; }
    void setKey(int key) { this->key = key; }
    void setData(int data) { this->data = data; }
    void setDeleted(bool deleted) { this->deleted = deleted; }
    ~Record() {}
private:
    int key;
    int data;
    bool deleted;
};

class HashTable {
public:
    HashTable() {
        capacity = 200000;
        table = new Record * [capacity];
        used = 0;
    }

    void insert(int key, int data) {
        int absoluteValueOfKey;
        if (key < 0) {
            absoluteValueOfKey = key * -1;
        }
        else {
            absoluteValueOfKey = key;
        }
        int hashValue = absoluteValueOfKey % capacity;
        if (table[hashValue] == nullptr) {
            Record* record = new Record(key, data);
            table[hashValue] = record;
            used++;
            return;
        }
        else if (table[hashValue]->getKey() == key) {
            if (table[hashValue]->getDeleted() == true) {
                Record* record = new Record(key, data);
                delete table[hashValue];
                table[hashValue] = record;
                used++;
                return;
            }
            else {
                return;
            }
        }
        else {
            for (int j = 0; j < capacity; j++) {
                int hashValuePrime = 7 - absoluteValueOfKey % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    Record* record = new Record(key, data);
                    table[hashValue] = record;
                    used++;
                    return;
                }
                else if (table[hashValue]->getKey() == key) {
                    if (table[hashValue]->getDeleted() == true) {
                        delete table[hashValue];
                        Record* record = new Record(key, data);
                        table[hashValue] = record;
                        used++;
                        return;
                    }
                    else {
                        return;
                    }
                }
            }
        }
    }

    bool lookup(int key) {
        int absoluteValueOfKey;
        if (key < 0) {
            absoluteValueOfKey = key * -1;
        }
        else {
            absoluteValueOfKey = key;
        }
        int hashValue = absoluteValueOfKey % capacity;
        if (table[hashValue] == nullptr) {
            return false;
        }
        else if (table[hashValue]->getKey() == key) {
            if (table[hashValue]->getDeleted() == true) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            for (int j = 0; j < capacity; j++) {
                int hashValuePrime = 7 - absoluteValueOfKey % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    return false;
                }
                else if (table[hashValue]->getKey() == key) {
                    if (table[hashValue]->getDeleted() == true) {
                        return false;
                    }
                    else {
                        return true;
                    }
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

            }
            else {
                delete table[i];
                table[i] = nullptr;
            }
        }
        delete[] table;
        table = nullptr;
        used = 0;
    }

    ~HashTable() {
        destroyTable();
    }
private:
    Record** table;
    int capacity;
    int used;
};

// Time complexity is O(N) or O(Nlog(N)) - 100%
int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    HashTable table;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] <= 0) {

        }
        else {
            if (table.lookup(A[i]) == false) {
                table.insert(A[i], A[i]);
            }
        }
    }

    for (int i = 1; i < 1000000; i++) {
        if (table.lookup(i) == false) {
            return i;
        }
    }

    return 1;
}

int main() {
}