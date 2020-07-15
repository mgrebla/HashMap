#include <iostream>
#include <string>

using namespace std;

static const int TABLE_SIZE = 10;

template<typename K, typename V>
class HashEntry {
	K key;
	V value;
	HashEntry* next;

public:
	HashEntry(const K& key, const V& value) {
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
	K getKey() const {
		return key;
	}
	V getValue() const {
		return value;
	}
	HashEntry* getNext() const {
		return next;
	}
	void setKey(K key) {
		HashEntry::key = key;
	}
	void setValue(V value) {
		HashEntry::value = value;
	}
	void setNext(HashEntry* next) {
		HashEntry::next = next;
	}
};

template<typename K, typename V>
struct HashMapTable {
	HashMapTable() {
		table = new HashEntry<K, V> * [TABLE_SIZE];
		for (unsigned int i = 0; i < TABLE_SIZE; ++i) {
			table[i] = NULL;
		}
	}

	//Destructor for cleanup hashtable required
	~HashMapTable(){}

	K hashFunction(const K key) {
		return key % TABLE_SIZE;
	}

	void insert(const K& key, const V& value) {
		int index = hashFunction(key);
		HashEntry<K, V>* entry = new HashEntry<K, V>(key, value);
		
		if (table[index] != NULL) {
			HashEntry<K, V>* temp = table[index];
			while (temp->getNext() != NULL) {
				temp = temp->getNext();
			}
			temp->setNext(entry);
		}
		else {
			table[index] = entry;
		}
	}

	void remove(const K& key, const V& value) {
		int index = hashFunction(key);
		HashEntry<K, V>* temp = table[index];
		HashEntry<K, V>* prev = NULL;

		if (temp == NULL) {
			cout << "This bucket is empty\n";
			return;
		}

		while (temp != NULL && !(temp->getKey() == key && temp->getValue() == value)) {
			prev = temp;
			temp = temp->getNext();
		}

		if (temp == NULL) {
			cout << "No entry found\n";
		}
		else {
			if (prev == NULL) {
				table[index] = temp->getNext();
			}
			else {
				prev->setNext(temp->getNext());
			}
			delete temp;
		}
	}

	void print(const K& key) {
		int index = hashFunction(key);
		HashEntry<K, V>* temp = table[index];

		while (temp != NULL) {
			cout << "Key: " << temp->getKey() << " " << "Value: " << temp->getValue() << endl;
			temp = temp->getNext();
		}
	}

private:
	HashEntry<K, V>** table;
};

int main(int argc, char** argv) {

	HashMapTable<int,string> hmap;

	hmap.insert(1, "string1");
	hmap.insert(1, "string2");
	hmap.insert(1, "string3");
	hmap.insert(2, "string1");
	hmap.insert(3, "string1");
	hmap.insert(2, "string2");

	hmap.print(1);

	cout << endl << "Removing entry" << endl << endl;
	hmap.remove(1, "string2");

	hmap.print(1);

	return 0;
}