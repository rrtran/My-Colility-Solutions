class Record {
public:
    Record() : key(0), data(0), deleted(false) {}
    Record(long key, int data) : key(key), data(data), deleted(false) {}
    long getKey() const { return key; }
    int getData() const { return data; }
    bool getDeleted() const { return deleted; }
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
    HashTable()
    {
        capacity = 2000000;
        used = 0;
        table = new Record * [capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    void insert(long key, int data)
    {
        long absoluteValueOfKey = calculateAbsoluteValue(key);
        int hashValue = absoluteValueOfKey % capacity;
        if (table[hashValue] == nullptr) {
            Record* record = new Record(key, data);
            table[hashValue] = record;
            used++;
            return;
        }
        else if (table[hashValue]->getKey() == key) {
            if (table[hashValue]->getDeleted() == true) {
                table[hashValue]->setKey(key);
                table[hashValue]->setData(data);
                table[hashValue]->setDeleted(false);
                used++;
                return;
            }
            else {
                return;
            }
        }
        else {
            for (int j = 1; j < capacity; j++) {
                int hashValuePrime = 7 - absoluteValueOfKey % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    Record* record = new Record(key, data);
                    table[hashValue] = record;
                    used++;
                    return;
                }
                if (table[hashValue]->getKey() == key) {
                    if (table[hashValue]->getDeleted() == true) {
                        table[hashValue]->setKey(key);
                        table[hashValue]->setData(data);
                        table[hashValue]->setDeleted(false);
                        used++;
                        return;
                    }
                    else {
                        return;
                    }
                }
            }
            return;
        }
    }

    void remove(long key)
    {
        long absoluteValueOfKey = calculateAbsoluteValue(key);
        int hashValue = absoluteValueOfKey % capacity;
        if (table[hashValue] == nullptr) {
            return;
        }
        else if (table[hashValue]->getKey() == key) {
            if (table[hashValue]->getDeleted() == true) {
                return;
            }
            else {
                table[hashValue]->setDeleted(true);
                used--;
                return;
            }
        }
        else {
            for (int j = 1; j < capacity; j++) {
                int hashValuePrime = 7 - absoluteValueOfKey % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    return;
                }
                else if (table[hashValue]->getKey() == key) {
                    if (table[hashValue]->getDeleted() == true) {
                        return;
                    }
                    else {
                        table[hashValue]->setDeleted(true);
                        used--;
                        return;
                    }
                }
            }
            return;
        }
    }

    bool lookup(long key) {
        long absoluteValueOfKey = calculateAbsoluteValue(key);
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
            for (int j = 1; j < capacity; j++) {
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
            return false;
        }
    }

    int search(long key)
    {
        long absoluteValueOfKey = calculateAbsoluteValue(key);
        int hashValue = absoluteValueOfKey % capacity;
        if (table[hashValue] == nullptr) {
            return -2147483647;
        }
        else if (table[hashValue]->getKey() == key) {
            if (table[hashValue]->getDeleted() == true) {
                return -2147483647;
            }
            else {
                return table[hashValue]->getData();
            }
        }
        else {
            for (int j = 1; j < capacity; j++) {
                int hashValuePrime = 7 - absoluteValueOfKey % 7;
                hashValue = (hashValue + j * hashValuePrime) % capacity;
                if (table[hashValue] == nullptr) {
                    return -2147483647;
                }
                else if (table[hashValue]->getKey() == key) {
                    if (table[hashValue]->getDeleted() == true) {
                        return -2147483647;
                    }
                    else {
                        return table[hashValue]->getData();
                    }
                }
            }
            return -2147483647;
        }
    }

    void destroyTable()
    {
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

    ~HashTable()
    {
        destroyTable();
    }

private:
    Record** table;
    int capacity;
    int used;

    long calculateAbsoluteValue(long n)
    {
        if (n < 0) {
            return n * -1;
        }
        else {
            return n;
        }
    }
};

// Time complexity is either O(N) or O(N * log(N))
// Score is 100%
int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    HashTable table;

    for (int i = 0; i < A.size(); i++) {
        if (table.lookup(A[i]) == false) {
            table.insert(A[i], A[i]);
        }
        else {
            table.remove(A[i]);
        }
    }

    for (int i = 0; i < A.size(); i++) {
        if (table.lookup(A[i]) == false) {

        }
        else {
            return A[i];
        }
    }

    return 0;
}