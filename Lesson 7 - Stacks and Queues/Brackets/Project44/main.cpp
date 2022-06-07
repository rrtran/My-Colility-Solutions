class Node {
public:
    Node() : data(0), link(nullptr) {}
    Node(char data) : data(data), link(nullptr) {}
    char getData() { return data; }
    Node* getLink() { return link; }
    void setData(char data) { this->data = data; }
    void setLink(Node* link) { this->link = link; }
    ~Node() { link = nullptr; }
private:
    char data;
    Node* link;
};

class SinglyLinkedList {
public:
    SinglyLinkedList() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    void insertFront(char data) {
        if (size == 0) {
            Node* node = new Node(data);
            first = node;
            last = node;
            size++;
        }
        else {
            Node* node = new Node(data);
            node->setLink(first);
            first = node;
            size++;
        }
    }

    void insertBack(char data) {
        if (size == 0) {
            Node* node = new Node(data);
            first = node;
            last = node;
            size++;
        }
        else {
            Node* node = new Node(data);
            last->setLink(node);
            last = node;
            size++;
        }
    }

    void deleteNode(char data) {
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
                if (data == current->getData()) {
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

    char getFirst() {
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
        size = 0;
        first = nullptr;
        last = nullptr;
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

    void push(char e) {
        list.insertFront(e);
    }

    void pop() {
        list.deleteNode(list.getFirst());
    }

    bool isEmpty() {
        if (list.length() == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    char top() {
        return list.getFirst();
    }

    int size() {
        return list.length();
    }
private:
    SinglyLinkedList list;
};

class Queue {
public:
    Queue() {}
    void enqueue(char e) {
        list.insertBack(e);
    }

    void dequeue() {
        list.deleteNode(list.getFirst());
    }

    bool isEmpty() {
        if (list.length() == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    char front() {
        return list.getFirst();
    }

    int size() {
        return list.length();
    }
private:
    SinglyLinkedList list;
};

// Time complexity is O(N)
// Score is 100%
int solution(string& S) {
    // write your code in C++14 (g++ 6.2.0)
    Queue queue;
    Stack stack;
    for (int i = 0; i < S.length(); i++) {
        queue.enqueue(S[i]);
    }

    while (queue.isEmpty() == false) {
        if (queue.front() == '{') {
            stack.push(queue.front());
            queue.dequeue();
        }
        else if (queue.front() == '}') {
            if (stack.isEmpty() == true) {
                return 0;
            }
            else if (stack.top() == '{') {
                stack.pop();
                queue.dequeue();
            }
            else {
                return 0;
            }
        }
        else if (queue.front() == '[') {
            stack.push(queue.front());
            queue.dequeue();
        }
        else if (queue.front() == ']') {
            if (stack.isEmpty() == true) {
                return 0;
            }
            else if (stack.top() == '[') {
                stack.pop();
                queue.dequeue();
            }
            else {
                return 0;
            }
        }
        else if (queue.front() == '(') {
            stack.push(queue.front());
            queue.dequeue();
        }
        else if (queue.front() == ')') {
            if (stack.isEmpty() == true) {
                return 0;
            }
            else if (stack.top() == '(') {
                stack.pop();
                queue.dequeue();
            }
            else {
                return 0;
            }
        }
    }

    if (stack.isEmpty() == true) {
        return 1;
    }
    else {
        return 0;
    }
}