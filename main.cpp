#include <iostream>


using namespace std;
typedef unsigned int UINT; 

class Heap {
private:
	UINT  max_size;
public:
	UINT* T;
	UINT nElements;
	Heap() : T(new UINT[2]), max_size(200000), nElements(0) {
		memset(T, 0, 2 * sizeof(UINT));
	}
	Heap(UINT s) : T(new UINT[s + 2]), max_size(200000), nElements(s) {
		memset(T, -1, (s + 2) * sizeof(UINT));
	}
	~Heap() {
		delete[] T;
	}
	bool resize(unsigned new_size);
	void swap(UINT index_a, UINT index_b);
	bool compare(UINT index_a, UINT index_b);
	void print_heap();
	bool insert(UINT value);
	void heap_push(int v);
	UINT heap_pop();
	UINT heap_returnTopValue();
};

void Heap::print_heap() {
	for (UINT i = 0; i < nElements; ++i)
		std::cout << T[i] << " ";
	std::cout << "\n";
}

bool Heap::resize(unsigned new_size) {
	if (new_size < nElements) {
		return false;
	}
	nElements = new_size;
	unsigned *tmp = new unsigned[new_size + 2];
	memset(tmp, 0, (new_size + 2) * sizeof(UINT));
	memcpy(tmp, T, (nElements + 2) * sizeof(UINT));
	delete T;
	T = tmp;
	return true;
}

void Heap::swap(UINT index_a, UINT index_b) {
	UINT x = T[index_a];
	T[index_a] = T[index_b];
	T[index_b] = x;
}

bool Heap::compare(UINT a, UINT b) {
	if (T[a] < T[b]) {
		return true;
	}
	return false;
}

UINT Heap::heap_returnTopValue() {
	return T[0];
}

bool Heap::insert(UINT value) {
	if (nElements == max_size) {
		return false;
	}
	T[nElements - 1] = value;
	for (UINT i = nElements; i != 1; i /= 2) {
		if (compare((i / 2) - 1, i - 1)) {
			swap((i / 2) - 1, i - 1);
		}
		else {
			break;
		}
	}
	return true;
}
void Heap::heap_push(int v)
{
	nElements++;
	resize(nElements);
	insert(v);
}
UINT Heap::heap_pop()
{
	UINT value = T[0];
	if (nElements != 0) {
		T[0] = T[--nElements];
		unsigned i = 1;
		while (i * 2 <= nElements) {
			register unsigned tmp = compare((i * 2) - 1, i * 2) ? (i * 2) : (i * 2) - 1;
			if (compare(i - 1, tmp)) {
				swap(i - 1, tmp);
				i = tmp + 1;
			}
			else {
				break;
			}
		}
		return value;
	}
	return 0;

}


int main()
{
	Heap heaps[1000];

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		char character;
		cin >> character;
		if (character == 'a') {
			int group;
			int value;
			cin >> group >> value;
			heaps[group].heap_push(value);
		}
		else if (character == 'e') {
			int group;
			cin >> group;
			if (heaps[group].nElements == 0)
				cout << "na" << endl;
			else
				cout << heaps[group].heap_pop() << endl;
		}
		else if (character == 'p') {
			int group;
			cin >> group;
			UINT el = heaps[group].nElements;
			Heap h = Heap(heaps[group].nElements);
			memcpy(h.T, heaps[group].T, heaps[group].nElements * sizeof(UINT)+1);
			for (UINT j = 0; j < el; ++j) {
				cout << h.heap_pop() << endl;
			}
		}
		else if (character == 'm') {
			int group1, group2;
			cin >> group1 >> group2;
			int el = heaps[group2].nElements;
			int pom = 0;
			for (int j = 0; j < el; ++j)
			{
				pom = heaps[group2].heap_returnTopValue();
				heaps[group2].heap_pop();
				heaps[group1].heap_push(pom);
			}
		}
		else if (character == 'i') {
			int group, value1, value2;
			cin >> group >> value1 >> value2;
			UINT val = 0;

			if (heaps[group].nElements == 0) {
				cout << "na" << endl;
			}
			else {
				bool haveIfound = 0;
				UINT el = heaps[group].nElements;
				Heap pomHeap = Heap();
				for (UINT x = 0; x < el;++x) {
					val = heaps[group].heap_pop();
					if (val == value1) {
						val = value2;
						haveIfound = 1;
					}
					if(val!=0)
						pomHeap.heap_push(val);
				}
				if (haveIfound == 0) {
					cout << "na" << endl;
				}
				heaps[group].nElements = pomHeap.nElements;
				memcpy(heaps[group].T, pomHeap.T, heaps[group].nElements * sizeof(UINT) + 1);
			}
		}

	}

	return 0;
}



