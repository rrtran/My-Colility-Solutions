class Node {
public:
    Node() : key(0), data(0), link(nullptr) {}
    Node(int key) : key(key), data(0), link(nullptr) {}
    int getData() { return data; }
    int getKey() { return key; }
    Node* getLink() { return link; }
    void setData(int data) { this->data = data; }
    void setKey(int key) { this->key = key; }
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
        capacity = 200000;
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
        }
    }

    void destroyTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                delete table[i];
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

class Node2 {
public:
    Node2() : data(0), flag(false) {}
    Node2(int data) : data(data), flag(false) {}
    Node2(int data, bool flag) : data(data), flag(flag) {}
    int getData() { return data; }
    int getFlag() { return flag; }
    void setData(int data) { this->data = data; }
    void setFlag(bool flag) { this->flag = flag; }
    ~Node2() {}
private:
    int data;
    bool flag;
};

void bubbleSort(vector<Node2*>& A) {
    if (A.size() == 0) return;
    if (A.size() == 1) return;

    for (int j = 0; j < A.size() - 1; j++) {
        for (int i = 0; i < A.size() - 1 - j; i++) {
            if (A[i]->getData() > A[i + 1]->getData()) {
                int temp = A[i]->getData();
                A[i]->setData(A[i + 1]->getData());
                A[i + 1]->setData(temp);
                bool temp2 = A[i]->getFlag();
                A[i]->setFlag(A[i + 1]->getFlag());
                A[i + 1]->setFlag(temp2);
            }
        }
    }
}

// Time complexity is O(N) or O(NlogN)
// Score is 100%
int solution(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    HashTable table;
    vector<Node2*> B;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] < 0) {

        }
        else {
            if (table.lookup(A[i]) == false) {
                table.insert(A[i]);
                B.push_back(new Node2(A[i], true));
            }
        }
    }

    if (B.size() == 0) {
        return 1;
    }

    int min = 1000000;
    int max = -1000000;
    for (int i = 0; i < A.size(); i++) {
        if (min > A[i]) {
            min = A[i];
        }
        if (max < A[i]) {
            max = A[i];
        }
    }

    int largestPositiveNumber = 0;
    for (int i = 0; i < B.size(); i++) {
        if (B[i]->getData() > 0) {
            if (largestPositiveNumber < B[i]->getData()) {
                largestPositiveNumber = B[i]->getData();
            }
        }
    }

    for (int i = 1; i < largestPositiveNumber; i++) {
        if (table.lookup(i) == false) {
            return i;
        }
    }

    return largestPositiveNumber + 1;