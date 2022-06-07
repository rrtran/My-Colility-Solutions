#include <iostream>

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

	void deleteLast() {
		if (size == 0) {
			return;
		}
		else if (size == 1) {
			delete last;
			first = nullptr;
			last = nullptr;
			size--;
			return;
		}
		else {
			Node* trailCurrent = nullptr;
			Node* current = first;
			while (current != last) {
				trailCurrent = current;
				current = current->getLink();
			}
			trailCurrent->setLink(nullptr);
			last = trailCurrent;
			delete current;
			current = nullptr;
			size--;
			return;
		}
	}

	int getFirst() {
		return first->getData();
	}

	int getLast() {
		return last->getData();
	}

	int length() {
		return size;
	}

private:
	Node* first;
	Node* last;
	int size;
};

int main() {
}