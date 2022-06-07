#include <vector>

using namespace std;

class Fish {
public:
    Fish() : size(0), downstream(false) {}
    Fish(int size, bool downstream) : size(size), downstream(downstream) {}
    Fish(Fish& data) {
        size = data.getSize();
        downstream = data.getDownstream();
    }
    int getSize() { return size; }
    int getDownstream() { return downstream; }
    void setSize(int size) { this->size = size; }
    void setDownstream(int downstream) { this->downstream = downstream; }
    bool equals(Fish& fish) {
        if (fish.getSize() == size) {
            if (fish.getDownstream() == downstream) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    ~Fish() {}
private:
    int size;
    int downstream;
};

class Node {
public:
    Node() : data(0, 0), link(nullptr) {}
    Node(Fish& data) : data(data), link(nullptr) {}
    Fish& getData() { return data; }
    Node* getLink() { return link; }
    void setData(Fish& data) {
        this->data.setSize(data.getSize());
        this->data.setDownstream(data.getDownstream());
    }
    void setLink(Node* link) { this->link = link; }
    ~Node() { link = nullptr; }
private:
    Fish data;
    Node* link;
};

class SinglyLinkedList {
public:
    SinglyLinkedList() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    void insertFront(Fish& data) {
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

    void insertBack(Fish& data) {
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

    void deleteNode(Fish& data) {
        if (size == 0) {
            return;
        }
        else if (size == 0) {
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
                if (current->getData().equals(data)) {
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

    Fish& getFirst() {
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

    void push(Fish& e) {
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

    Fish& top() {
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

    void enqueue(Fish& e) {
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

    Fish& front() {
        return list.getFirst();
    }

    int size() {
        return list.length();
    }

    ~Queue() {}
private:
    SinglyLinkedList list;
};

// Time complexity is O(N) - 100%
int solution(vector<int>& A, vector<int>& B) {
    // write your code in C++14 (g++ 6.2.0)
    const int DOWN_STREAM = 1;
    Stack stack;
    Queue queue;
    for (int i = 0; i < A.size(); i++) {
        Fish fish(A[i], B[i]);
        queue.enqueue(fish);
    }

    while (queue.empty() == false) {
        if (stack.empty() == true) {
            stack.push(queue.front());
            queue.dequeue();
        }
        else if (queue.front().getDownstream() == DOWN_STREAM) {
            stack.push(queue.front());
            queue.dequeue();
        }
        else {
            if (stack.top().getDownstream() == DOWN_STREAM) {
                if (stack.top().getSize() > queue.front().getSize()) {
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
    }

    return stack.size();
}

int main() {

}