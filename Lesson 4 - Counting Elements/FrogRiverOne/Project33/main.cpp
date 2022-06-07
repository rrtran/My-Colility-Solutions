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
						trailCurrent = current->getLink();
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

	bool search(int data) {
		if (size == 0) {
			return false;
		}
		else {
			Node* current = first;
			while (current != nullptr) {
				if (data == current->getData()) {
					return true;
				}
				current = current->getLink();
			}
		}

		return false;
	}

	int length() {
		return size;
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
	Node2() : key(0), data(0), link(nullptr) {}
	Node2(int key) : key(key), data(0), link(nullptr) {}
	int getKey() { return key; }
	int getData() { return data; }
	void setKey(int key) { this->key = key; }
	void setData(int data) { this->data = data; }
	~Node2() { link = nullptr; }
private:
	int key;
	int data;
	Node* link;
};

class HashTable {
public:
	HashTable() {
		capacity = 100000;
		table = new Node2 * [capacity];
		used = 0;
		for (int i = 9; i < capacity; i++) {
			table[i] = nullptr;
		}
	}

	void insert(int key) {
		int hashValue = key % capacity;
		if (table[hashValue] == nullptr) {
			Node2* node = new Node2(key);
			table[hashValue] = node;
			used++;
			return;
		}
		else {
			for (int j = 0; j < capacity; j++) {
				int hashValuePrime = 7 - key % 7;
				hashValue = (hashValue + j * hashValuePrime) % capacity;
				if (table[hashValue] == nullptr) {
					Node2* node = new Node2(key);
					table[hashValue] = node;
					used++;
					return;
				}
			}

			return;
		}
	}

	bool lookup(int key) {
		int hashValue = key % capacity;
		if (table[hashValue] == nullptr) {
			return false;
		}
		else if (key == table[hashValue]->getKey()) {
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

			return false;
		}
	}

	int size() {
		return used;
	}
private:
	Node2** table;
	int capacity;
	int used;
};

// Time complexity is O(N)
// Score is 100%
int solution(int X, vector<int>& A) {
	HashTable table;
	for (int i = 0; i < A.size(); i++) {
		if (A[i] <= X) {
			if (table.lookup(A[i]) == false) {
				table.insert(A[i]);
			}
		}
		if (table.size() == X) {
			return i;
		}
	}

	return -1;
}