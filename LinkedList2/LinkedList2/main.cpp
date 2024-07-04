#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

struct LinkedList
{
	LinkedList* prev; // Паказальнік на папярэдні элемент у спісе
	LinkedList* next; // Паказальнік на наступны элемент у спісе

	std::string lastName; // Прозвішча студэнта
	std::string firstName; // Імя студэнта
	std::string secondName; // Імя па бацьку студэнта
	int bdayYear; // Год нараджэння студэнта
	int course; // Курс, на якім вучыцца студэнт
	int group; // Нумар групы студэнта
	int* grades; // Паказальнік на масіў адзнак
	// Канструктар класа
	LinkedList()
	{
		prev = next = nullptr; // Ініцыялізацыя паказальнікаў на папярэдні і наступны элементы
		grades = new int[5]; // Вылучэнне памяці пад масіў адзнак
	}

	// Дэструктар класа
	~LinkedList()
	{
		delete[] grades; // Вызваленне памяці, выдзеленай пад масіў адзнак
	}
};
// Функцыя сартавання звязанага спісу па зададзеным крытэрыі
void sortList(LinkedList*& p);

// Функцыя дадання студэнта ў звязаны спіс
void add(LinkedList*& p)
{
	// Ствараем новы аб'ект студэнта
	LinkedList* student = new LinkedList;

	// Запытваем у карыстальніка інфармацыю пра студэнта
	cout << "Увядзіце прозвішча: "; getline(cin, student->lastName);
	cout << "Увядзіце імя: "; getline(cin, student->firstName);
	cout << "Увядзіце імя па бацьку: "; getline(cin, student->secondName);
	cout << "Увядзіце год нараджэння: "; cin >> student->bdayYear;
	cout << "Увядзіце курс: "; cin >> student->course;
	cout << "Увядзіце групу: "; cin >> student->group;
	cout << "Увядзіце 5 адзнак праз прабел: "; cin >> student->grades[0] >> student->grades[1] >> student->grades[2] >> student->grades[3] >> student->grades[4];
	cout << "\n";
	cin.ignore(); // Чысцім буфер уводу

	// Калі спіс пусты, прысвойваем яму першага студэнта
	if (p == nullptr)
	{
		p = student;
	}
	else
	{
		// Калі спіс не пусты, дадаем студэнта ў пачатак спісу
		p->prev = student;
		student->next = p;
		student->prev = nullptr;
		p = student;
	}
}

// Функцыя вываду інфармацыі пра студэнта на экран
void printStudent(const LinkedList* ptr)
{
	// Выводзім інфармацыю пра студэнта
	cout << "\n-------------------------------------------\n";
	cout << "Прозвішча: " << ptr->lastName << '\n';
	cout << "Імя: " << ptr->firstName << '\n';
	cout << "Імя па бацьку: " << ptr->secondName << '\n';
	cout << "Год нараджэння: " << ptr->bdayYear << '\n';
	cout << "Курс: " << ptr->course << '\n';
	cout << "Група: " << ptr->group << '\n';
	cout << "5 адзнак: " << ptr->grades[0] << ' ' << ptr->grades[1] << ' ' << ptr->grades[2] << ' ' << ptr->grades[3] << ' ' << ptr->grades[4] << ' ' << '\n';
	cout << "-------------------------------------------\n";
}

// Функцыя вываду ўсяго звязанага спісу на экран
void print(LinkedList* p)
{
	LinkedList* ptr = p;
	// Праходзім па спісе і выводзім інфармацыю пра кожнага студэнта
	while (ptr)
	{
		printStudent(ptr);
		ptr = ptr->next;
	}
}

// Функцыя разліку сярэдняга бала па кожнай групе
void calculateAverage(LinkedList* p)
{
	// Праходзім па кожнай групе (мяркуецца, што групы нумаруюцца ад 1 да 4)
	for (int i = 1; i <= 4; i++)
	{
		LinkedList* ptr = p;
		int count = 0;
		int* allGrades = new int[5];

		// Ініцыялізуем масіў сум адзнак для кожнага студэнта ў групе
		for (size_t i = 0; i < 5; i++)
		{
			allGrades[i] = 0;
		}

		// Праходзім па звязаным спісе студэнтаў
		while (ptr)
		{
			// Калі студэнт належыць бягучай групе, абнаўляем сумы адзнак і павялічваем лічыльнік
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

		// Калі ў групе ёсць студэнты, выводзім сярэдні бал па кожным прадмеце
		if (count > 0)
		{
			printf_s("Група %d: ", i);
			for (size_t j = 0; j < 5; j++)
			{
				// Разлічваем сярэдні бал і выводзім яго з адной лічбай пасля коскі
				double grade = (double)allGrades[j] / count;
				printf_s("%.1f ", grade);
			}
			cout << '\n';
		}

		// Вызваляем выдзеленую памяць пад масіў сум адзнак
		delete[] allGrades;
	}
}

// Функцыя разліку сярэдняга бала для аднаго студэнта
double calculateAverageGrade(const LinkedList* student)
{
	double sum = 0.0;

	// Праходзім па кожнай адзнацы студэнта і сумуем іх
	for (int i = 0; i < 5; ++i)
	{
		sum += student->grades[i];
	}

	// Разлічваем сярэдні бал і вяртаем яго
	return sum / 5.0;
}

// Функцыя пошуку студэнта з самым раннім годам нараджэння ў звязаным спісе
LinkedList* findOldestStudent(LinkedList* p)
{
	// Ініцыялізуем паказальнік на старэйшага студэнта першым элементам спісу
	LinkedList* oldestStudent = p;

	// Ініцыялізуем паказальнік для ітэрацыі па спісе, пачынаючы з другога элемента
	LinkedList* ptr = p->next;

	// Праходзім па астатніх элементах спісу
	while (ptr)
	{
		// Параўноўваем гады нараджэння бягучага студэнта з годам нараджэння старэйшага студэнта
		if (ptr->bdayYear < oldestStudent->bdayYear)
		{
			// Калі бягучы студэнт старэйшы, абнаўляем паказальнік на старэйшага студэнта
			oldestStudent = ptr;
		}

		// Пераходзім да наступнага студэнту ў спісе
		ptr = ptr->next;
	}

	// Вяртаем паказальнік на старэйшага студэнта
	return oldestStudent;
}

// Функцыя пошуку студэнта з самым познім годам нараджэння ў звязаным спісе
LinkedList* findYoungestStudent(LinkedList* p)
{
	// Ініцыялізуем паказальнік на малодшага студэнта першым элементам спісу
	LinkedList* youngestStudent = p;

	// Ініцыялізуем паказальнік для ітэрацыі па спісе, пачынаючы з другога элемента
	LinkedList* ptr = p->next;

	// Праходзім па астатніх элементах спісу
	while (ptr)
	{
		// Параўноўваем гады нараджэння бягучага студэнта з годам нараджэння малодшага студэнта
		if (ptr->bdayYear > youngestStudent->bdayYear)
		{
			// Калі бягучы студэнт маладзейшы, абнаўляем паказальнік на малодшага студэнта
			youngestStudent = ptr;
		}

		// Пераходзім да наступнага студэнту ў спісе
		ptr = ptr->next;
	}

	// Вяртаем паказальнік на малодшага студэнта
	return youngestStudent;
}

// Функцыя вываду інфармацыі пра лепшага студэнта ў зададзенай групе
void printBestStudentInGroup(LinkedList* p, int group)
{
	// Ініцыялізуем паказальнік на лепшага студэнта і зменную для лепшага сярэдняга бала
	LinkedList* bestStudent = nullptr;
	double bestAverage = 0.0;

	// Ініцыялізуем паказальнік для ітэрацыі па звязаным спісе
	LinkedList* ptr = p;

	// Праходзім па кожным студэнту ў спісе
	while (ptr)
	{
		// Правяраем, ці належыць бягучы студэнт да зададзенай групы
		if (ptr->group == group)
		{
			// Разлічваем сярэдні бал бягучага студэнта
			double average = calculateAverageGrade(ptr);

			// Правяраем, ці з'яўляецца бягучы студэнт лепшым
			if (bestStudent == nullptr || average > bestAverage)
			{
				bestStudent = ptr;
				bestAverage = average;
			}
		}

		// Пераходзім да наступнага студэнту ў спісе
		ptr = ptr->next;
	}
	// Выводзім інфармацыю пра лепшага студэнта ў групе
	if (bestStudent != nullptr)
	{
		cout << "\nЛепшы студэнт у групе " << group << ":\n";
		printStudent(bestStudent);
	}
	else
	{
		cout << "\nУ групе " << group << " студэнтаў няма.\n";
	}
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	// Ініцыялізуем паказальнік на звязаны спіс
	LinkedList* l = nullptr;

	// Дадаем некалькі студэнтаў у спіс
	add(l);
	add(l);
	add(l);
	add(l);

	cout << "Зыходны спіс: \n";
	print(l);

	// Сартуем спіс
	sortList(l);
	cout << "Адсартаваны спіс:\n";
	// Выводзім адсартаваны спіс
	print(l);

	cout << "Сярэдні бал па 5 прадметах для кожнай групы:\n";
	// Разлічваем сярэдні бал для кожнай групы і выводзім вынік
	calculateAverage(l);

	// Знаходзім самага старэйшага і самага малодшага студэнта і выводзім інфармацыю пра іх
	LinkedList* oldest = findOldestStudent(l);
	LinkedList* youngest = findYoungestStudent(l);

	cout << "\nСамы старэйшы студэнт:\n";
	printStudent(oldest);

	cout << "\nСамы малодшы студэнт:\n";
	printStudent(youngest);

	// Знаходзім лепшага студэнта ў кожнай групе і выводзім інфармацыю пра іх
	for (int i = 1; i <= 4; ++i)
	{
		printBestStudentInGroup(l, i);
	}
	return 0;
}
// Функцыя для параўнання двух студэнтаў па курсе і прозвішчы па алфавітным парадку
bool sortingKey(const LinkedList* firstStudent, const LinkedList* secondStudent)
{
	// Параўноўваем курсы студэнтаў
	if (firstStudent->course == secondStudent->course)
	{
		// Калі курсы аднолькавыя, параўноўваем прозвішчы студэнтаў лексікаграфічна
		return firstStudent->lastName < secondStudent->lastName;
	}
	// Калі курсы розныя, параўноўваем іх
	return firstStudent->course < secondStudent->course;
}

// Функцыя для сартавання спісу
void sortList(LinkedList*& p)
{
	// Ствараем копію арыгінальнага спісу, каб не змяняць зыходныя дадзеныя
	LinkedList* originListCopy = p;

	// Ініцыялізуем паказальнік на адсартаваны спіс
	LinkedList* sortedList = nullptr;

	// Праходзім па арыгінальным спісе
	while (p != nullptr)
	{
		// Захоўваем бягучага студэнта і перамяшчаем паказальнік на наступнага
		LinkedList* currentStudent = p;
		p = p->next;

		// Устаўляемы студэнта ва ўпарадкаваны спіс

		// Калі спарадкаваны спіс пусты або бягучы студэнт "менш" за першы ва ўпарадкаваным спісе
		if (sortedList == nullptr || sortingKey(currentStudent, sortedList))
		{
			// Устаўляем бягучага студэнта ў пачатак спарадкаванага спісу
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
			// Шукаем месца ва ўпарадкаваным спісе для ўстаўкі бягучага студэнта

			// Пачынаем пошук з пачатку спарадкаванага спісу
			LinkedList* temp = sortedList;

			// Ідзем па спарадкаваным спісе, пакуль не знойдзем элемент, большы за бягучага студэнта
			while (temp->next != nullptr && !sortingKey(currentStudent, temp->next))
			{
				temp = temp->next;
			}

			// Устаўляем бягучага студэнта паміж вузламі

			// Звязваем бягучага студэнта з папярэднім вузлом
			currentStudent->prev = temp;

			// Звязваем бягучага студэнта з наступным вузлом
			currentStudent->next = temp->next;

			// Калі наступны вузел існуе, звязваем яго з бягучым студэнтам
			if (temp->next != nullptr)
			{
				temp->next->prev = currentStudent;
			}

			// Звязваем папярэдні вузел з бягучым студэнтам
			temp->next = currentStudent;
		}
	}

	// Абнаўляем паказальнік на пачатак адсартаванага спісу
	p = sortedList;
}