// HomeworkOrder2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

class Heap {
private:
	
	unsigned  max_size;
public:
	unsigned int* T;
	unsigned int nElements;
	bool initialized;
	Heap() : T(new unsigned int[2]), max_size(200000), nElements(0), initialized(true) {
		memset(T, 0, 2 * sizeof(unsigned int));
	}
	Heap(unsigned int s) : T(new unsigned int[s+2]), max_size(200000), nElements(s), initialized(true) {
		memset(T, 0, (s+2) * sizeof(unsigned int));
	}
	~Heap() {
		delete T;
	}
	bool resize(unsigned new_size);
	void swap(unsigned int index_a, unsigned int index_b);
	bool cmp(unsigned int index_a, unsigned int index_b);
	void printHeap();
	bool insert(unsigned int value);
	void heap_push(int v);
	void heap_pop(bool printValue);
	unsigned int heap_returnTopValue();

	void printTab(int* tab, int size) {
		for (auto i = 0; i < size; ++i)
			std::cout << tab[i] << " ";
		std::cout << "\n";
	}
};

void Heap::printHeap() {
	for (auto i = 0; i < nElements; ++i)
		std::cout << T[i] << " ";
	std::cout << "\n";
}

bool Heap::resize(unsigned new_size) {
	if (new_size < nElements) {
		return false;
	}
	nElements = new_size;
	unsigned *tmp = new unsigned[new_size+2];
	memset(tmp, 0, (new_size+2) * sizeof(unsigned int));
	memcpy(tmp, T, (nElements+2) * sizeof(unsigned int));
	delete T;
	T = tmp;
	return true;
}

void Heap::swap(unsigned int index_a, unsigned int index_b) {
	unsigned int x = T[index_a];
	T[index_a] = T[index_b];
	T[index_b] = x;
}

bool Heap::cmp(unsigned int index_a, unsigned int index_b) {
	return  (T[index_a] < T[index_b] ? true : false);
}

unsigned int Heap::heap_returnTopValue() {
	return T[0];
}

bool Heap::insert(unsigned int value) {
	if (nElements == max_size) {
		return false;
	}
	T[nElements - 1] = value;
	for (unsigned int i = nElements; i != 1; i /= 2) {
		if (cmp((i / 2) - 1, i - 1)) {
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
void Heap::heap_pop(bool printValue)
{
	if (nElements != 0) {
		if(printValue)
			cout << T[0] << endl;
		unsigned value = T[0];
		T[0] = T[--nElements];
		unsigned i = 1;
		while (i * 2 <= nElements) {
			register unsigned tmp = cmp((i * 2) - 1, i * 2) ? (i * 2) : (i * 2) - 1;
			if (cmp(i - 1, tmp)) {
				swap(i - 1, tmp);
				i = tmp + 1;
			}
			else {
				break;
			}
		}
	}
	else {
		if(printValue)
			cout << "na" << endl;
	}
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
			heaps[group].heap_pop(true);
		}
		else if (character == 'p') {
			int group;
			cin >> group;
			unsigned int el = heaps[group].nElements;
			Heap h = Heap(heaps[group].nElements);
			memcpy(h.T, heaps[group].T, heaps[group].nElements * sizeof(unsigned int));
			for (unsigned int j = 0; j < el; ++j) {
				h.heap_pop(true);
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
				heaps[group2].heap_pop(false);
				heaps[group1].heap_push(pom);
			}
		}
		else if (character == 'i') {
			int group, value1, value2;
			cin >> group >> value1 >> value2;
			unsigned int pom = 0;
			
			if (heaps[group].nElements == 0) {
				cout << "na" << endl;
			}
			else {
				unsigned int el = heaps[group].nElements;
				unsigned int* pomT = new unsigned int[el];
				unsigned int q = 0;
				pom = heaps[group].T[0];
				heaps[group].heap_pop(false);
				q++;
				pomT[0] = pom;
				bool foundValue = 0;
				if (pom == value1) {
					pomT[0] = value2;
					foundValue = 1;
				}
				else {
					while (pom != value1) {
						if (q >= el) {
							foundValue = 0;
							break;
						}
						pom = heaps[group].T[q];
						heaps[group].heap_pop(false);
						
						pomT[q] = pom;
						if (pom == value1) {
							pomT[q] = value2;
							foundValue = 1;
						}
						q++;
					}
				}
				for (unsigned int j = 0; j < q; ++j) {
					heaps[group].heap_push(pomT[j]);
				}
				if (foundValue == 0)
					cout << "na" << endl;
			}
		}

	}

	return 0;
}



