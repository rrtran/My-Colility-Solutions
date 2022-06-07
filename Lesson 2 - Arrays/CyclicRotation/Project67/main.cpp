class Node {
public:
    Node() : data(0), link(nullptr) {}
    Node(int data) : data(data), link(nullptr) {}
    int getData() { return data; }
    Node* getLink() { return link; }
    void setData(int data) { this->data = data; }
    void setLink(Node* link) { this->link = link; }
    ~Node() { link = nullptr; }
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

class Queue {
public:
    Queue() {}

    void enqueue(int e) {
        list.insertBack(e);
    }

    void dequeue() {
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

    int front() {
        return list.getFirst();
    }

    int size() {
        return list.length();
    }

    ~Queue() {}
private:
    SinglyLinkedList list;
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
vector<int> solution(vector<int>& A, int K) {
    // write your code in C++14 (g++ 6.2.0)

    if (A.size() == 0) {
        return A;
    }
    else {
        Queue queue;
        Stack stack;
        for (int i = A.size() - 1; i >= 0; i--) {
            queue.enqueue(A[i]);
        }

        for (int i = 0; i < K; i++) {
            int temp = queue.front();
            queue.dequeue();
            queue.enqueue(temp);
        }

        while (queue.empty() == false) {
            stack.push(queue.front());
            queue.dequeue();
        }

        while (A.empty() == false) {
            A.pop_back();
        }

        while (stack.empty() == false) {
            A.push_back(stack.top());
            stack.pop();
        }

        return A;
    }
}