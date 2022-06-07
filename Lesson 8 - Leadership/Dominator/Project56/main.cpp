#include <vector>

using namespace std;

class Record {
public:
    Record() : key(0), data(0), deleted(false) {}
    Record(long key, int data) : key(key), data(data), deleted(false) {}
    long getKey() { return key; }
    int getData() { return data; }
    bool getDeleted() { return deleted; }
    void setKey(long key) { this->key = key; }
    void setData(int data) { this->data = data; }
    void setDeleted(bool deleted) { this->deleted = deleted; }
    ~Record() {}
private:
    long key;
    int data;
    bool deleted;
};

class HashTable {
public:
    HashTable() {
        capacity = 200000;
        table = new Record * [capacity];
        used = 0;
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    void insert(long key, int data) {
        long absoluteValueOfKey;
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
            }
        }
    }

    bool lookup(long key) {
        long absoluteValueOfKey;
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
            return false;
        }
    }

    int size() {
        return used;
    }

    Record* getRecord(long key) {
        long absoluteValueOfKey;
        if (key < 0) {
            absoluteValueOfKey = key * -1;
        }
        else {
            absoluteValueOfKey = key;
        }

        int hashValue = absoluteValueOfKey % capacity;
        if (table[hashValue] == nullptr) {
            return nullptr;
        }
        else if (table[hashValue]->getKey() == key) {
            return table[hashValue];
        }
        else {
            for (int j = 0; j < capacity; j++) {
                int hashValuePrime = 7 - absoluteValueOfKey % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    return nullptr;
                }
                else if (table[hashValue]->getKey() == key) {
                    return table[hashValue];
                }
            }
        }
    }

    void increment(long key) {
        long absoluteValueOfKey;
        if (key < 0) {
            absoluteValueOfKey = key * -1;
        }
        else {
            absoluteValueOfKey = key;
        }

        int hashValue = absoluteValueOfKey % capacity;
        if (table[hashValue] == nullptr) {
            return;
        }
        else if (table[hashValue]->getKey() == key) {
            table[hashValue]->setData(table[hashValue]->getData() + 1);
            return;
        }
        else {
            for (int j = 0; j < capacity; j++) {
                int hashValuePrime = 7 - absoluteValueOfKey % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    return;
                }
                else if (table[hashValue]->getKey() == key) {
                    table[hashValue]->setData(table[hashValue]->getData() + 1);
                    return;
                }
            }
        }
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
        if (table.lookup(A[i]) == false) {
            table.insert(A[i], 1);
        }
        else {
            table.increment(A[i]);
        }
    }

    for (int i = 0; i < A.size(); i++) {
        if (table.lookup(A[i]) == false) {

        }
        else {
            if (table.getRecord(A[i])->getData() > A.size() / 2) {
                return i;
            }
        }
    }
    return -1;
}