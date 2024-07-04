#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <chrono>

// Каб было меньш писаць, выкарыстоўваю стандратны спісак і вектар замест масіва
struct School {
	int schoolNumber;
	std::string directorLastName;
};

const int TABLE_SIZE = 10; // Памер хэш-табліцы

// Функцыя ўніверсальнага хэшавання
int universalHash(int key) {
	// Выбіраем адвольныя каэфіцыенты a і b
	const int a = 3;
	const int b = 7;
	const int p = 31; // Просты лік, большы за памер табліцы
	return ((a * key + b) % p) % TABLE_SIZE; // Вылічаем хэш з дапамогай універсальнай функцыі хэшавання
}

// Функцыя для ўстаўкі элемента ў хэш-табліцу
void insert(std::vector<std::list<School>>& table, const School& school) {
	int index = universalHash(school.schoolNumber); // Вылічаем індэкс устаўкі ў табліцу
	table[index].push_back(school); // Дадаем элемент у адпаведны спіс хэш-табліцы
}

// Функцыя для пошуку элемента па ключы
std::string search(const std::vector<std::list<School>>& table, int key) {
	int index = universalHash(key); // Вылічаем індэкс пошуку ў табліцы
	auto start = std::chrono::high_resolution_clock::now(); // Пачатак засечкі часу пошуку
	for (const auto& entry : table[index]) { // Праходзім па спісе элементаў па вылічаным індэксе
		if (entry.schoolNumber == key) { // Калі знойдзены элемент з указаным ключом
			auto end = std::chrono::high_resolution_clock::now(); // Канец засечкі часу пошуку
			std::chrono::nanoseconds  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // Вылічэнне працягласці часу пошуку ў мікрасекундах
			std::cout << "Пошук заняў: " << duration.count() << " нанасекунд\n"; // Выводзім працягласць часу пошуку
			return entry.directorLastName; // Вяртаем прозвішча дырэктара знойдзенай школы
		}
	}
	return "Школа не знойдзена"; // Калі школа не знойдзена, вяртаем паведамленне пра памылку
}

// Функцыя для вываду ўсёй хэш-табліцы
void printHashTable(const std::vector<std::list<School>>& table) {
	for (int i = 0; i < TABLE_SIZE; ++i) { // Праходзім па ўсіх элементах табліцы
		std::cout << "Хэш" << i << ": "; // Выводзім індэкс хеша
		if (!table[i].empty()) { // Калі спіс не пусты
			for (const auto& entry : table[i]) { // Праходзім па ўсіх элементах спісу
				std::cout << "[" << entry.schoolNumber << ", " << entry.directorLastName << "] "; // Выводзім дадзеныя элемента
			}
		}
		else {
			std::cout << "Пуста"; // Калі спіс пусты, выводны паведамленне аб пустэчы
		}
		std::cout << std::endl; // Пераходзім на новы радок
	}
}

int main() {
	// Ініцыялізуем хэш-табліцу
	std::vector<std::list<School>> hashTable(TABLE_SIZE);

	// Дадаем дадзеныя аб школах у табліцу
	insert(hashTable, { 8, "Янаў" });
	insert(hashTable, { 18, "Пятроў" }); // Гэты элемент будзе мець той жа хэш, што і элемент з нумарам 101
	insert(hashTable, { 25, "Сідараў" });
	insert(hashTable, { 32, "Сідараў" });

	// Выводзім усю хэш-табліцу
	std::cout << "Хэш-табліца:" << std::endl;
	printHashTable(hashTable);

	// Выконваем пошук па нумары школы
	int searchKey = 32;
	std::cout << "\nДырэктар школы з нумарам " << searchKey << ": " << search(hashTable, searchKey) << std::endl;

	return 0;
}
