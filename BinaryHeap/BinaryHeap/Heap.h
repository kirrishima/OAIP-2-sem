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
		int size; // Бягучы памер кучы
		int maxSize; // Максімальны памер кучы
		void** storage; // Масіў паказальнікаў на дадзеныя
		CMP(*compare)(void*, void*); // Паказальнік на функцыю параўнання
		Heap(int maxsize, CMP(*f)(void*, void*))
		{
			size = 0;
			storage = new void* [maxSize = maxsize]; // Вылучэнне памяці пад масіў захоўвання дадзеных
			compare = f; // Ініцыялізацыя паказальніка на функцыю параўнання
		};
		int left(int ix); // Вяртае азначнік левага нашчадка для элемента з азначнікам ix.
		int right(int ix); // Вяртае азначнік правага нашчадка для элемента з азначнікам ix.
		int parent(int ix); // Вяртае азначнік бацькоўскага элемента для элемента з азначнікам ix.

		bool isFull() const
		{
			return (size >= maxSize); // Праверка, ці запоўненая куча
		};
		bool isEmpty() const
		{
			return (size <= 0); // Праверка, ці пустая куча
		};
		bool isLess(void* x1, void* x2) const
		{
			return compare(x1, x2) == LESS; // Праверка, ці з'яўляецца x1 меншым за x2
		};
		bool isGreat(void* x1, void* x2) const
		{
			return compare(x1, x2) == GREAT; // Праверка, ці з'яўляецца x1 большым за x2
		};
		bool isEqual(void* x1, void* x2) const
		{
			return compare(x1, x2) == EQUAL; // Праверка, ці роўныя x1 і x2
		};

		void swap(int i, int j); // Змяняе месцамі элементы з індэксамі i і j
		void heapify(int ix); // Падтрымлівае ўласцівасць кучы, пачынаючы з элемента з індэксам ix
		void insert(void* x); // Устаўляе новы элемент у кучу
		void* extractMax(); // Здабывае і вяртае максімальны элемент кучы
		void scan(int i) const; // Скануе элемент з індэксам i
		void* extractMin(); // Здабывае і вяртае мінімальны элемент кучы
		void extractI(int i); // Дастае элемент з індэксам i
		void unionHeap(Heap& h2); // Аб'ядноўвае дзве кучы
		void* getMax();
		void* getMin();
		void* findSumElement();
	};
	Heap create(int maxsize, CMP(*f)(void*, void*)); // Стварэнне кучы

};