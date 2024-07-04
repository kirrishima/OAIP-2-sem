#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

struct LinkedList
{
	LinkedList* prev; // ���������� �� �������� ������� � ����
	LinkedList* next; // ���������� �� �������� ������� � ����

	std::string lastName; // �������� ��������
	std::string firstName; // ��� ��������
	std::string secondName; // ��� �� ������ ��������
	int bdayYear; // ��� ���������� ��������
	int course; // ����, �� ��� ������� �������
	int group; // ����� ����� ��������
	int* grades; // ���������� �� ��� ������
	// ����������� �����
	LinkedList()
	{
		prev = next = nullptr; // ����������� ����������� �� �������� � �������� ��������
		grades = new int[5]; // ��������� ������ ��� ��� ������
	}

	// ���������� �����
	~LinkedList()
	{
		delete[] grades; // ���������� ������, ���������� ��� ��� ������
	}
};
// ������� ���������� ��������� ���� �� ���������� ��������
void sortList(LinkedList*& p);

// ������� ������� �������� � ������� ���
void add(LinkedList*& p)
{
	// �������� ���� ��'��� ��������
	LinkedList* student = new LinkedList;

	// ��������� � ������������ ���������� ��� ��������
	cout << "������� ��������: "; getline(cin, student->lastName);
	cout << "������� ���: "; getline(cin, student->firstName);
	cout << "������� ��� �� ������: "; getline(cin, student->secondName);
	cout << "������� ��� ����������: "; cin >> student->bdayYear;
	cout << "������� ����: "; cin >> student->course;
	cout << "������� �����: "; cin >> student->group;
	cout << "������� 5 ������ ���� ������: "; cin >> student->grades[0] >> student->grades[1] >> student->grades[2] >> student->grades[3] >> student->grades[4];
	cout << "\n";
	cin.ignore(); // ������ ����� �����

	// ��� ��� �����, ����������� ��� ������� ��������
	if (p == nullptr)
	{
		p = student;
	}
	else
	{
		// ��� ��� �� �����, ������ �������� � ������� ����
		p->prev = student;
		student->next = p;
		student->prev = nullptr;
		p = student;
	}
}

// ������� ������ ���������� ��� �������� �� �����
void printStudent(const LinkedList* ptr)
{
	// ������� ���������� ��� ��������
	cout << "\n-------------------------------------------\n";
	cout << "��������: " << ptr->lastName << '\n';
	cout << "���: " << ptr->firstName << '\n';
	cout << "��� �� ������: " << ptr->secondName << '\n';
	cout << "��� ����������: " << ptr->bdayYear << '\n';
	cout << "����: " << ptr->course << '\n';
	cout << "�����: " << ptr->group << '\n';
	cout << "5 ������: " << ptr->grades[0] << ' ' << ptr->grades[1] << ' ' << ptr->grades[2] << ' ' << ptr->grades[3] << ' ' << ptr->grades[4] << ' ' << '\n';
	cout << "-------------------------------------------\n";
}

// ������� ������ ����� ��������� ���� �� �����
void print(LinkedList* p)
{
	LinkedList* ptr = p;
	// �������� �� ���� � ������� ���������� ��� ������� ��������
	while (ptr)
	{
		printStudent(ptr);
		ptr = ptr->next;
	}
}

// ������� ������ ��������� ���� �� ������ �����
void calculateAverage(LinkedList* p)
{
	// �������� �� ������ ����� (���������, ��� ����� ���������� �� 1 �� 4)
	for (int i = 1; i <= 4; i++)
	{
		LinkedList* ptr = p;
		int count = 0;
		int* allGrades = new int[5];

		// ���������� ��� ��� ������ ��� ������� �������� � �����
		for (size_t i = 0; i < 5; i++)
		{
			allGrades[i] = 0;
		}

		// �������� �� �������� ���� ��������
		while (ptr)
		{
			// ��� ������� �������� ������� �����, �������� ���� ������ � ���������� �������
			if (ptr->group == i)
			{
				for (int j = 0; j < 5; ++j)
				{
					allGrades[j] += ptr->grades[j];
				}
				count++;
			}
			ptr = ptr->next;
		}

		// ��� � ����� ���� ��������, ������� ������ ��� �� ������ ��������
		if (count > 0)
		{
			printf_s("����� %d: ", i);
			for (size_t j = 0; j < 5; j++)
			{
				// ��������� ������ ��� � ������� ��� � ����� ����� ����� ����
				double grade = (double)allGrades[j] / count;
				printf_s("%.1f ", grade);
			}
			cout << '\n';
		}

		// ��������� ���������� ������ ��� ��� ��� ������
		delete[] allGrades;
	}
}

// ������� ������ ��������� ���� ��� ������ ��������
double calculateAverageGrade(const LinkedList* student)
{
	double sum = 0.0;

	// �������� �� ������ ������� �������� � ������ ��
	for (int i = 0; i < 5; ++i)
	{
		sum += student->grades[i];
	}

	// ��������� ������ ��� � ������� ���
	return sum / 5.0;
}

// ������� ������ �������� � ����� ����� ����� ���������� � �������� ����
LinkedList* findOldestStudent(LinkedList* p)
{
	// ���������� ���������� �� ���������� �������� ������ ��������� ����
	LinkedList* oldestStudent = p;

	// ���������� ���������� ��� �������� �� ����, ��������� � ������� ��������
	LinkedList* ptr = p->next;

	// �������� �� ������� ��������� ����
	while (ptr)
	{
		// ���������� ���� ���������� �������� �������� � ����� ���������� ���������� ��������
		if (ptr->bdayYear < oldestStudent->bdayYear)
		{
			// ��� ������ ������� ��������, �������� ���������� �� ���������� ��������
			oldestStudent = ptr;
		}

		// ��������� �� ���������� �������� � ����
		ptr = ptr->next;
	}

	// ������� ���������� �� ���������� ��������
	return oldestStudent;
}

// ������� ������ �������� � ����� ����� ����� ���������� � �������� ����
LinkedList* findYoungestStudent(LinkedList* p)
{
	// ���������� ���������� �� ��������� �������� ������ ��������� ����
	LinkedList* youngestStudent = p;

	// ���������� ���������� ��� �������� �� ����, ��������� � ������� ��������
	LinkedList* ptr = p->next;

	// �������� �� ������� ��������� ����
	while (ptr)
	{
		// ���������� ���� ���������� �������� �������� � ����� ���������� ��������� ��������
		if (ptr->bdayYear > youngestStudent->bdayYear)
		{
			// ��� ������ ������� ����������, �������� ���������� �� ��������� ��������
			youngestStudent = ptr;
		}

		// ��������� �� ���������� �������� � ����
		ptr = ptr->next;
	}

	// ������� ���������� �� ��������� ��������
	return youngestStudent;
}

// ������� ������ ���������� ��� ������� �������� � ���������� �����
void printBestStudentInGroup(LinkedList* p, int group)
{
	// ���������� ���������� �� ������� �������� � ������� ��� ������� ��������� ����
	LinkedList* bestStudent = nullptr;
	double bestAverage = 0.0;

	// ���������� ���������� ��� �������� �� �������� ����
	LinkedList* ptr = p;

	// �������� �� ������ �������� � ����
	while (ptr)
	{
		// ���������, �� �������� ������ ������� �� ���������� �����
		if (ptr->group == group)
		{
			// ��������� ������ ��� �������� ��������
			double average = calculateAverageGrade(ptr);

			// ���������, �� �'�������� ������ ������� ������
			if (bestStudent == nullptr || average > bestAverage)
			{
				bestStudent = ptr;
				bestAverage = average;
			}
		}

		// ��������� �� ���������� �������� � ����
		ptr = ptr->next;
	}
	// ������� ���������� ��� ������� �������� � �����
	if (bestStudent != nullptr)
	{
		cout << "\n����� ������� � ����� " << group << ":\n";
		printStudent(bestStudent);
	}
	else
	{
		cout << "\n� ����� " << group << " �������� ����.\n";
	}
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	// ���������� ���������� �� ������� ���
	LinkedList* l = nullptr;

	// ������ ������� �������� � ���
	add(l);
	add(l);
	add(l);
	add(l);

	cout << "������� ���: \n";
	print(l);

	// ������� ���
	sortList(l);
	cout << "����������� ���:\n";
	// ������� ����������� ���
	print(l);

	cout << "������ ��� �� 5 ��������� ��� ������ �����:\n";
	// ��������� ������ ��� ��� ������ ����� � ������� ����
	calculateAverage(l);

	// �������� ������ ���������� � ������ ��������� �������� � ������� ���������� ��� ��
	LinkedList* oldest = findOldestStudent(l);
	LinkedList* youngest = findYoungestStudent(l);

	cout << "\n���� �������� �������:\n";
	printStudent(oldest);

	cout << "\n���� ������� �������:\n";
	printStudent(youngest);

	// �������� ������� �������� � ������ ����� � ������� ���������� ��� ��
	for (int i = 1; i <= 4; ++i)
	{
		printBestStudentInGroup(l, i);
	}
	return 0;
}
// ������� ��� ��������� ���� �������� �� ����� � �������� �� ��������� �������
bool sortingKey(const LinkedList* firstStudent, const LinkedList* secondStudent)
{
	// ���������� ����� ��������
	if (firstStudent->course == secondStudent->course)
	{
		// ��� ����� �����������, ���������� �������� �������� ��������������
		return firstStudent->lastName < secondStudent->lastName;
	}
	// ��� ����� ������, ���������� ��
	return firstStudent->course < secondStudent->course;
}

// ������� ��� ���������� ����
void sortList(LinkedList*& p)
{
	// �������� ���� ������������ ����, ��� �� ������� �������� ��������
	LinkedList* originListCopy = p;

	// ���������� ���������� �� ����������� ���
	LinkedList* sortedList = nullptr;

	// �������� �� ����������� ����
	while (p != nullptr)
	{
		// �������� �������� �������� � ����������� ���������� �� ����������
		LinkedList* currentStudent = p;
		p = p->next;

		// ��������� �������� �� ������������ ���

		// ��� ������������ ��� ����� ��� ������ ������� "����" �� ����� �� ������������� ����
		if (sortedList == nullptr || sortingKey(currentStudent, sortedList))
		{
			// �������� �������� �������� � ������� �������������� ����
			currentStudent->next = sortedList;
			currentStudent->prev = nullptr;
			if (sortedList != nullptr)
			{
				sortedList->prev = currentStudent;
			}
			sortedList = currentStudent;
		}
		else
		{
			// ������ ����� �� ������������� ���� ��� ����� �������� ��������

			// �������� ����� � ������� �������������� ����
			LinkedList* temp = sortedList;

			// ����� �� ������������� ����, ������ �� �������� �������, ������ �� �������� ��������
			while (temp->next != nullptr && !sortingKey(currentStudent, temp->next))
			{
				temp = temp->next;
			}

			// �������� �������� �������� ���� ������

			// �������� �������� �������� � ��������� ������
			currentStudent->prev = temp;

			// �������� �������� �������� � ��������� ������
			currentStudent->next = temp->next;

			// ��� �������� ����� �����, �������� ��� � ������� ���������
			if (temp->next != nullptr)
			{
				temp->next->prev = currentStudent;
			}

			// �������� �������� ����� � ������� ���������
			temp->next = currentStudent;
		}
	}

	// �������� ���������� �� ������� ������������� ����
	p = sortedList;
}