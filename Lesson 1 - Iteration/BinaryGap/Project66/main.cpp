class Node {
public:
    Node() : data(0), link(nullptr) {}
    Node(int data) : data(data), link(nullptr) {}
    int getData() { return data; }
    Node* getLink() { return link; }
    void setData(int data) { this->data = data; }
    void setLink(Node* link) { this->link = link; }
    ~Node() {}
private:
    int data;
    Node* link;
};

class SinglyLinkedList {
public:
    SinglyLinkedList() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    void insertFront(int data) {
        if (size == 0) {
            Node* node = new Node(data);
            first = node;
            last = node;
            size++;
            return;
        }
        else {
            Node* node = new Node(data);
            node->setLink(first);
            first = node;
            size++;
            return;
        }
    }

    void insertBack(int data) {
        if (size == 0) {
            Node* node = new Node(data);
            first = node;
            last = node;
            size++;
            return;
        }
        else {
            Node* node = new Node(data);
            last->setLink(node);
            last = node;
            size++;
            return;
        }
    }

    void deleteNode(int data) {
        if (size == 0) {
            return;
        }
        else if (size == 1) {
            delete first;
            first = nullptr;
            last = nullptr;
            size--;
            return;
        }
        else {
            Node* trailCurrent = nullptr;
            Node* current = first;
            while (current != nullptr) {
                if (current->getData() == data) {
                    if (current == first) {
                        first = first->getLink();
                        delete current;
                        current = nullptr;
                        size--;
                        return;
                    }
                    else if (current == last) {
                        trailCurrent->setLink(nullptr);
                        last = trailCurrent;
                        delete current;
                        current = nullptr;
                        size--;
                        return;
                    }
                    else {
                        trailCurrent->setLink(current->getLink());
                        delete current;
                        current = nullptr;
                        size--;
                        return;
                    }
                }
                trailCurrent = current;
                current = current->getLink();
            }

        }
    }

    int getFirst() {
        return first->getData();
    }

    int length() {
        return size;
    }

    void destroyList() {
        Node* current = first;
        while (current != nullptr) {
            Node* temp = current;
            current = current->getLink();
            delete temp;
            temp = nullptr;
        }
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    ~SinglyLinkedList() {
        destroyList();
    }
private:
    Node* first;
    Node* last;
    int size;
};

class Stack {
public:
    Stack() {}

    void push(int e) {
        list.insertFront(e);
    }

    void pop() {
        list.deleteNode(list.getFirst());
    }

    bool empty() {
        if (list.length() == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    int top() {
        return list.getFirst();
    }

    int size() {
        return list.length();
    }

    ~Stack() {}
private:
    SinglyLinkedList list;
};

// 100%
int solution(int N) {
    // write your code in C++14 (g++ 6.2.0)
    Stack stack;
    int mask = 0b00000000000000000000000000000001;
    for (int i = 0; i < 32; i++) {
        int shiftedN = N >> i;
        int digit = shiftedN & mask;
        stack.push(digit);
    }

    int maximalBinaryGap = 0;
    int currentBinaryGap = 0;
    bool startCounting = false;
    while (stack.empty() == false) {
        if (startCounting == false) {
            if (stack.top() == 1) {
                startCounting = true;
                stack.pop();
            }
            else {
                stack.pop();
            }
        }
        else {
            if (stack.top() == 1) {
                if (currentBinaryGap > maximalBinaryGap) {
                    maximalBinaryGap = currentBinaryGap;
                    currentBinaryGap = 0;
                    stack.pop();
                }
                else {
                    currentBinaryGap = 0;
                    stack.pop();
                }
            }
            else {
                currentBinaryGap++;
                stack.pop();
            }
        }
    }

    return maximalBinaryGap;
}