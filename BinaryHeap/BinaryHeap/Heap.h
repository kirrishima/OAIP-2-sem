#pragma once
struct AAA
{
	int x;
	void print();
};
namespace heap
{
	enum CMP
	{
		LESS = -1, EQUAL = 0, GREAT = 1
	};
	struct Heap
	{
		int size; // ������ ����� ����
		int maxSize; // ���������� ����� ����
		void** storage; // ��� ����������� �� ��������
		CMP(*compare)(void*, void*); // ���������� �� ������� ���������
		Heap(int maxsize, CMP(*f)(void*, void*))
		{
			size = 0;
			storage = new void* [maxSize = maxsize]; // ��������� ������ ��� ��� ��������� ��������
			compare = f; // ����������� ����������� �� ������� ���������
		};
		int left(int ix); // ������ ������� ������ �������� ��� �������� � ��������� ix.
		int right(int ix); // ������ ������� ������� �������� ��� �������� � ��������� ix.
		int parent(int ix); // ������ ������� ����������� �������� ��� �������� � ��������� ix.

		bool isFull() const
		{
			return (size >= maxSize); // ��������, �� ��������� ����
		};
		bool isEmpty() const
		{
			return (size <= 0); // ��������, �� ������ ����
		};
		bool isLess(void* x1, void* x2) const
		{
			return compare(x1, x2) == LESS; // ��������, �� �'�������� x1 ������ �� x2
		};
		bool isGreat(void* x1, void* x2) const
		{
			return compare(x1, x2) == GREAT; // ��������, �� �'�������� x1 ������� �� x2
		};
		bool isEqual(void* x1, void* x2) const
		{
			return compare(x1, x2) == EQUAL; // ��������, �� ����� x1 � x2
		};

		void swap(int i, int j); // ������ ������ �������� � �������� i � j
		void heapify(int ix); // ����������� ����������� ����, ��������� � �������� � �������� ix
		void insert(void* x); // ������� ���� ������� � ����
		void* extractMax(); // �������� � ������ ���������� ������� ����
		void scan(int i) const; // ������ ������� � �������� i
		void* extractMin(); // �������� � ������ �������� ������� ����
		void extractI(int i); // ������ ������� � �������� i
		void unionHeap(Heap& h2); // ��'������� ���� ����
		void* getMax();
		void* getMin();
		void* findSumElement();
	};
	Heap create(int maxsize, CMP(*f)(void*, void*)); // ��������� ����

};