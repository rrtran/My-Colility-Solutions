#include <iostream>

using namespace std;

class Node {
public:
	Node() : key(0), data(1), link(nullptr) {}
	Node(int key) : key(key), data(1), link(nullptr) {}
	Node(int key, int data) : key(key), data(data), link(nullptr) {}
	int getKey() { return key; }
	int getData() { return data; }
	Node* getLink() { return link; }
	void setKey(int key) { this->key = key; }
	void setData(int data) { this->data = data; }
	void setLink(Node* link) { this->link = link; }
	~Node() { link = nullptr; }
private:
	int key;
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

	void insertFront(int key) {
		if (size == 0) {
			Node* node = new Node(key);
			first = node;
			last = node;
			size++;
		}
		else {
			Node* node = new Node(key);
			node->setLink(first);
			first = node;
			size++;
		}
	}

	void insertBack(int key) {
		if (size == 0) {
			Node* node = new Node(key);
			first = node;
			last = node;
			size++;
		}
		else {
			Node* node = new Node(key);
			last->setLink(node);
			last = node;
			size++;
		}
	}

	void deleteNode(int key) {
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
				if (key == current->getData()) {
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

	int getData(int index) {
		Node* current = first;
		for (int i = 0; i < index; i++) {
			if (current == nullptr) {
				return -1;
			}
			current = current->getLink();
		}

		return current->getData();
	}

	int getFirst() {
		return first->getData();
	}

	int getLast() {
		return last->getData();
	}

	bool search(int key) {
		Node* current = first;
		while (current != nullptr) {
			if (key == current->getData()) {
				return true;
			}
			current = current->getLink();
		}

		return false;
	}

	int length() {
		return size;
	}

	void print() {
		Node* current = first;
		cout << "Keys: ";
		while (current != nullptr) {
			cout << current->getData() << " ";
			current = current->getLink();
		}
		cout << endl;
	}

	void destoryList() {
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
		destoryList();
	}
private:
	Node* first;
	Node* last;
	int size;
};

class HashTable {
public:
	HashTable() {
		capacity = 3000000;
		table = new Node * [capacity];
		for (int i = 0; i < capacity; i++) {
			table[i] = nullptr;
		}
		used = 0;
	}

	void insert(int key) {
		int hashValue = key % capacity;
		for (int i = 0; i < capacity; i++) {
			int probeForwardIndex = (hashValue + i) % capacity; // ProbeForwardIndex starts at the hashed key index
			if (table[probeForwardIndex] == nullptr) {
				Node* node = new Node(key);
				table[probeForwardIndex] = node;
				return;
			}
		}
	}

	bool lookup(int key) {
		int index = key % capacity;
		if (table[index] == nullptr) {
			return false;
		}
		else {
			for (int i = 0; i < capacity; i++) {
				int probeForwardIndex = (index + i) % capacity;
				if (table[probeForwardIndex] == nullptr) {
					return false;
				}
				else if (table[probeForwardIndex]->getData() == key) {
					return true;
				}
			}
		}
	}

	int getData(int key) {
		int index = key % capacity;
		if (table[index] == nullptr) {
			return -1;
		}
		else {
			for (int i = 0; i < capacity; i++) {
				int probeForwardIndex = (index + i) % capacity;
				if (table[probeForwardIndex] == nullptr) {
					return -1;
				}
				else if (table[probeForwardIndex]->getData() == key) {
					return table[probeForwardIndex]->getData();
				}
			}
		}
	}

	void increment(int key) {
		int index = key % capacity;
		if (table[index] == nullptr) {
			return;
		}
		else {
			for (int i = 0; i < capacity; i++) {
				int probeForwardIndex = (index + i) % capacity;
				if (table[probeForwardIndex] == nullptr) {
					return;
				}
				else if (table[probeForwardIndex]->getData() == key) {
					table[probeForwardIndex]->setData(table[probeForwardIndex]->getData() + 1);
				}
			}
		}
	}

	void print() {
		for (int i = 0; i < capacity; i++) {
			if (table[i] != nullptr) {
				cout << "Index " << i << ": ";
				cout << "Key: " << table[i]->getData() << ", ";
				cout << "Data: " << table[i]->getData() << endl;
			}
		}
		cout << endl;
	}

	void destroyTable() {
		for (int i = 0; i < capacity; i++) {
			if (table[i] != nullptr) {
				delete table[i];
				table[i] = nullptr;
			}
		}
		delete[] table;
	}

	~HashTable() {
		destroyTable();
	}
private:
	Node** table;
	int capacity;
	int used;
};

class HashTable2 {
public:
	HashTable2() {
		capacity = 1000000;
		table = new SinglyLinkedList[capacity];
	}

	void insert(int key) {
		int hashValue = key % capacity;
		table[hashValue].insertBack(key);
		filledListIndices.insertBack(hashValue);
	}

	void remove(int key) {
		int hashValue = key % capacity;
		if (table[hashValue].length() == 0) {
			return;
		}
		else if (table[hashValue].search(key) == true) {
			table[hashValue].deleteNode(key);
			if (table[hashValue].length() == 0) {
				filledListIndices.deleteNode(hashValue);
			}
			return;
		}
		else {
			return;
		}
	}

	bool lookup(int key) {
		for (int i = 0; i < filledListIndices.length(); i++) {
			int filledListIndex = filledListIndices.getData(i);
			if (filledListIndex == -1) return false;
			if (table[filledListIndex].search(key) == true) {
				return true;
			}
		}

		return false;
	}

	void print() {
		for (int i = 0; i < capacity; i++) {
			if (table[i].length() > 0) {
				table[i].print();
			}
		}
	}

private:
	SinglyLinkedList* table;
	SinglyLinkedList filledListIndices;
	int capacity;
};

class HashTable3 {
public:
	HashTable3() {
		capacity = 3000000;
		table = new Node*[capacity];
		used = 0;
		for (int i = 0; i < capacity; i++) {
			table[i] = nullptr;
		}
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
				int hashValuePrime = 7 - (key % 7);
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
				int hashValuePrime = 7 - (key % 7);
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

	void increment(int key) {
		int hashValue = key % capacity;
		if (table[hashValue] == nullptr) {
			return;
		}
		else if (table[hashValue]->getKey() == key) {
			table[hashValue]->setData(table[hashValue]->getData() + 1);
		}
		else {
			for (int j = 0; j < capacity; j++) {
				int hashValuePrime = 7 - (key % 7);
				hashValue = (hashValue + j * hashValuePrime) % capacity;
				if (table[hashValue] == nullptr) {
					return;
				}
				else if (table[hashValue]->getKey() == key) {
					table[hashValue]->setData(table[hashValue]->getData() + 1);
				}
			}
		}
	}

	int getData(int key) {
		int hashValue = key % capacity;
		if (table[hashValue] == nullptr) {
			return -1;
		}
		else if (table[hashValue]->getKey() == key) {
			return table[hashValue]->getData();
		}
		else {
			for (int j = 0; j < capacity; j++) {
				int hashValuePrime = 7 - (key % 7);
				hashValue = (hashValue + j * hashValuePrime) % capacity;
				if (table[hashValue] == nullptr) {
					return -1;
				}
				else if (table[hashValue]->getKey() == key) {
					table[hashValue]->getData();
				}
			}
		}
	}

	void print() {
		for (int i = 0; i < capacity; i++) {
			if (table[i] != nullptr) {
				cout << "Key: " << table[i]->getKey() << endl;
			}
		}
	}

	void destroyTable() {
		for (int i = 0; i < capacity; i++) {
			if (table[i] != nullptr)
				delete table[i];
		}
		delete[] table;
	}

	~HashTable3() {
		destroyTable();
	}

private:
	Node** table;
	int capacity;
	int used;
};

int main() {
	HashTable2 table;
	table.insert(1000000);
	table.insert(2000000);
	table.insert(3000000);
	table.insert(1);
	table.insert(1000001);

	table.print();

	system("cls");

	HashTable3 table2;
	table2.insert(9);
	table2.insert(3);
	table2.insert(9);
	table2.insert(3);
	table2.insert(9);
	table2.insert(7);
	table2.insert(9);

	table2.print();
}