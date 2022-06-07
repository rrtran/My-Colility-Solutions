#include <vector>

using namespace std;

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
        }
        else {
            Node* node = new Node(data);
            node->setLink(first);
            first = node;
            size++;
        }
    }

    void insertBack(int data) {
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
    void push(int e) {
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

class Queue {
public:
    Queue() {}
    void enqueue(int e) {
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

int solution(vector<int>& H) {
    // write your code in C++14 (g++ 6.2.0)
    Stack stack;
    Queue queue;
    for (int i = 0; i < H.size(); i++) {
        queue.enqueue(H[i]);
    }

    int blockCount = 0;
    while (queue.isEmpty() == false) {
        if (stack.isEmpty() == true) {
            blockCount++;
            stack.push(queue.front());
            queue.dequeue();
        }
        else if (queue.front() > stack.top()) {
            blockCount++;
            stack.push(queue.front());
            queue.dequeue();
        }
        else if (queue.front() < stack.top()) {
            if (stack.isEmpty() == true) {
                blockCount++;
                stack.push(queue.front());
                queue.dequeue();
            }
            else {
                stack.pop();
            }
        }
        else {
            stack.push(queue.front());
            queue.dequeue();
        }
    }

    return blockCount;
}

int main() {

}