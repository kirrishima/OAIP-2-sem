#include <Windows.h>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

void bubbleSort(int* ptr, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i + 1; j < size; j++)
		{
			if (*(ptr + i) > *(ptr + j))
			{
				int temp = *(ptr + i);
				*(ptr + i) = *(ptr + j);
				*(ptr + j) = temp;
			}
		}
	}
}
void insertionsSort(int* ptr, int size)
{
	size_t i;
	size_t j;
	for (i = 1; i < size; i++)
	{
		int temp = ptr[i];
		for (j = i - 1; j >= 0 && ptr[j] > temp; j--)
		{
			ptr[j + 1] = ptr[j];
		}
		ptr[j + 1] = temp;
	}
}
void choiceSort(int* ptr, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		int minIndex = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (ptr[minIndex] > ptr[j])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			int tmp = ptr[i];
			ptr[i] = ptr[minIndex];
			ptr[minIndex] = tmp;
		}
	}
}
void quickSort(int* array, int first, int last) {     //функция сортировки
	int mid, tmp;
	int f = first, l = last;
	mid = array[(f + l) / 2]; 				//вычисление опорного элемента
	do
	{
		while (array[f] < mid) f++;
		while (array[l] > mid) l--;
		if (f <= l) 				//перестановка элементов
		{
			tmp = array[f];
			array[f] = array[l];
			array[l] = tmp;
			f++;
			l--;
		}
	} while (f < l);
	if (first < l) quickSort(array, first, l);
	if (f < last) quickSort(array, f, last);
}

void printArray(int* ptr, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << ptr[i] << " ";
	}
	cout << "\n";
}
int main() {
	SetConsoleOutputCP(1251);

	int n;
	cout << "Введите размерность массива: ";
	cin >> n;
	int* A = new int[n];
	int* B = new int[n];
	int* C = new int[n];
	int* D = new int[n];
	int* E = new int[n];

	//#define PrintArrays
	cout << "Исходный массив А: \n";
	for (size_t i = 0; i < n; i++)
	{
		A[i] = B[i] = C[i] = D[i] = E[i] = rand() % 1000;
#ifdef PrintArrays
		cout << A[i] << " ";
#endif
	}	cout << "\n";
	cout << "\nМассив В после пузырьковой сортировки: \n";
	auto start = high_resolution_clock::now();
	bubbleSort(B, n);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
#ifdef PrintArrays
	printArray(B, n);
#endif
	cout << "Время выполнения, в микросекундах: " << duration.count() << endl << endl;

	cout << "Массив В после сортировки вставкой: \n";
	start = high_resolution_clock::now();
	insertionsSort(C, n);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
#ifdef PrintArrays
	printArray(C, n);
#endif
	cout << "Время выполнения, в микросекундах: " << duration.count() << endl << endl;

	cout << "Массив В после сортировки выбором: \n";
	start = high_resolution_clock::now();
	choiceSort(D, n);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
#ifdef PrintArrays
	printArray(D, n);
#endif
	cout << "Время выполнения, в микросекундах: " << duration.count() << endl << endl;

	cout << "Массив В после сортировки быстрой сортировкой: \n";
	start = high_resolution_clock::now();
	quickSort(E, 0, n - 1);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
#ifdef PrintArrays
	printArray(E, n);
#endif
	cout << "Время выполнения, в микросекундах: " << duration.count() << endl << endl;


	delete[] A;
	delete[] B;
	delete[] D;
	delete[] C;
	delete[] E;

	return 0;
}
