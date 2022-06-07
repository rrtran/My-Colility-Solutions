class Fish {
public:
    Fish() : size(0), direction(0) {}
    Fish(int size, int direction) : size(size), direction(direction) {}
    int getSize() { return size; }
    int getDirection() { return direction; }
    void setSize(int size) { this->size = size; }
    void setDirection(int direction) { this->direction = direction; }
    ~Fish() {}
private:
    int size;
    int direction;
};

class Node {
public:
    Node() : data(nullptr), link(nullptr) {}
    Node(Fish* data) : data(data), link(nullptr) {}
    Fish* getData() { return data; }
    Node* getLink() { return link; }
    void setData(Fish* data) { this->data = data; }
    void setLink(Node* link) { this->link = link; }
    ~Node() {
        data = nullptr;
        link = nullptr;
    }
private:
    Fish* data;
    Node* link;
};

class SinglyLinkedList {
public:
    SinglyLinkedList() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    void insertFront(Fish* data) {
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

    void insertBack(Fish* data) {
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

    void deleteNode(Fish* data) {
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

    Fish* getFirst() {
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

    void push(Fish* e) {
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

    Fish* top() {
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
    void enqueue(Fish* e) {
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

    Fish* front() {
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
int solution(vector<int>& A, vector<int>& B) {
    // write your code in C++14 (g++ 6.2.0)
    Stack stack;
    Queue queue;
    for (int i = 0; i < A.size(); i++) {
        Fish* fish = new Fish(A[i], B[i]);
        queue.enqueue(fish);
    }

    while (queue.isEmpty() == false) {
        if (stack.isEmpty() == false) {
            if (queue.front()->getDirection() == 0) {
                if (stack.top()->getDirection() == 0) {
                    stack.push(queue.front());
                    queue.dequeue();
                }
                else {
                    if (stack.top()->getSize() > queue.front()->getSize()) {
                        queue.dequeue();
                    }
                    else {
                        stack.pop();
                    }
                }
            }
            else {
                stack.push(queue.front());
                queue.dequeue();
            }
        }
        else {
            stack.push(queue.front());
            queue.dequeue();
        }
    }

    return stack.size();
}