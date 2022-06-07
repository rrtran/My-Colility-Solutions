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

	int computeAbsoluteDifference(int p) {
		Node* current = first;
		int firstPart = 0;
		int secondPart = 0;
		int i = 0;
		while (current != nullptr) {
			if (i < p) {
				firstPart += current->getData();
			}
			else {
				secondPart += current->getData();
			}
			i++;
			current = current->getLink();
		}

		int difference = firstPart - secondPart;
		int absoluteDifference;
		if (difference < 0) {
			absoluteDifference = difference * -1;
		}
		else {
			absoluteDifference = difference;
		}
		return absoluteDifference;
	}

	void print() {
		Node* current = first;
		while (current != nullptr) {
			cout << current->getData() << " ";
			current = current->getLink();
		}
		cout << endl;
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

class Node2 {
public:
	Node2() : data(0), previousLink(nullptr), nextLink(nullptr) {}
	Node2(int data) : data(data), previousLink(nullptr), nextLink(nullptr) {}
	int getData() { return data; }
	Node2* getPreviousLink() { return previousLink; }
	Node2* getNextLink() { return nextLink; }
	void setData(int data) { this->data = data; }
	void setPreviousLink(Node2* link) { previousLink = link; }
	void setNextLink(Node2* link) { nextLink = link; }
	~Node2() {
		previousLink = nullptr;
		nextLink = nullptr;
	}
private:
	int data;
	Node2* previousLink;
	Node2* nextLink;
};

class DoublyLinkedList {
public:
	DoublyLinkedList() {
		first = nullptr;
		last = nullptr;
		size = 0;
	}

	void insertFront(int data) {
		if (size == 0) {
			Node2* node = new Node2(data);
			first = node;
			last = node;
			size++;
		}
		else {
			Node2* node = new Node2(data);
			node->setNextLink(first);
			first->setPreviousLink(node);
			first = node;
			size++;
		}
	}

	void insertBack(int data) {
		if (size == 0) {
			Node2* node = new Node2(data);
			first = node;
			last = node;
			size++;
		}
		else {
			Node2* node = new Node2(data);
			last->setNextLink(node);
			node->setPreviousLink(last);
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
			Node2* trailCurrent = nullptr;
			Node2* current = first;
			while (current != nullptr) {
				if (data == current->getData()) {
					if (current == first) {
						first = first->getNextLink();
						first->setPreviousLink(nullptr);
						delete current;
						current = nullptr;
						size--;
						return;
					}
					else if (current == last) {
						trailCurrent->setNextLink(nullptr);
						last = trailCurrent;
						delete current;
						current = nullptr;
						size;;
						return;
					}
					else {
						trailCurrent->setNextLink(current->getNextLink());
						current->getNextLink()->setPreviousLink(trailCurrent);
						delete current;
						current = nullptr;
						size--;
						return;
					}
				}
				trailCurrent = current;
				current = current->getNextLink();
			}
		}
	}

	void deleteLast() {
		if (size == 0) {
			return;
		}
		else if (size == 1) {
			delete last;
			last = nullptr;
			first = nullptr;
			size--;
			return;
		}
		else {
			Node2* temp = last;
			last = last->getPreviousLink();
			last->setNextLink(nullptr);
			delete temp;
			temp = nullptr;
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
	Node2* first;
	Node2* last;
	int size;
};

// Time complexity is O(N)
// Score is 100%
int solution(vector<int>& A) {
	// write your code in C++14 (g++ 6.2.0)
	DoublyLinkedList list1;
	int sum = 0;
	for (int i = 0; i < A.size() - 1; i++) {
		sum += A[i];
		list1.insertBack(sum);
	}

	DoublyLinkedList list2;
	sum = 0;
	for (int i = A.size() - 1; i > 0; i--) {
		sum += A[i];
		list2.insertFront(sum);
	}

	vector<int> D;
	int minimalDifference = 0x7FFFFFFF;
	while (list1.length() != 0 && list2.length() != 0) {
		int difference = list1.getFirst() - list2.getFirst();
		list1.deleteNode(list1.getFirst());
		list2.deleteNode(list2.getFirst());
		int absoluteDifference;
		if (difference < 0) {
			absoluteDifference = difference * -1;
		}
		else {
			absoluteDifference = difference;
		}

		if (absoluteDifference < minimalDifference) {
			minimalDifference = absoluteDifference;
		}
	}

	return minimalDifference;
}