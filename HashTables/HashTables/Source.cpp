#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <chrono>

// ��� ���� ����� ������, ������������ ���������� ����� � ������ ������ �����
struct School {
	int schoolNumber;
	std::string directorLastName;
};

const int TABLE_SIZE = 10; // ����� ���-������

// ������� ������������� ���������
int universalHash(int key) {
	// ������� ��������� ����������� a � b
	const int a = 3;
	const int b = 7;
	const int p = 31; // ������ ��, ������ �� ����� ������
	return ((a * key + b) % p) % TABLE_SIZE; // ������� ��� � ��������� ������������ ������� ���������
}

// ������� ��� ����� �������� � ���-������
void insert(std::vector<std::list<School>>& table, const School& school) {
	int index = universalHash(school.schoolNumber); // ������� ������ ����� � ������
	table[index].push_back(school); // ������ ������� � ��������� ��� ���-������
}

// ������� ��� ������ �������� �� �����
std::string search(const std::vector<std::list<School>>& table, int key) {
	int index = universalHash(key); // ������� ������ ������ � ������
	auto start = std::chrono::high_resolution_clock::now(); // ������� ������ ���� ������
	for (const auto& entry : table[index]) { // �������� �� ���� �������� �� �������� �������
		if (entry.schoolNumber == key) { // ��� ��������� ������� � �������� ������
			auto end = std::chrono::high_resolution_clock::now(); // ����� ������ ���� ������
			std::chrono::nanoseconds  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // �������� ����������� ���� ������ � ������������
			std::cout << "����� �����: " << duration.count() << " ����������\n"; // ������� ����������� ���� ������
			return entry.directorLastName; // ������� �������� ��������� ���������� �����
		}
	}
	return "����� �� ���������"; // ��� ����� �� ���������, ������� ������������ ��� �������
}

// ������� ��� ������ ��� ���-������
void printHashTable(const std::vector<std::list<School>>& table) {
	for (int i = 0; i < TABLE_SIZE; ++i) { // �������� �� ��� ��������� ������
		std::cout << "���" << i << ": "; // ������� ������ ����
		if (!table[i].empty()) { // ��� ��� �� �����
			for (const auto& entry : table[i]) { // �������� �� ��� ��������� ����
				std::cout << "[" << entry.schoolNumber << ", " << entry.directorLastName << "] "; // ������� �������� ��������
			}
		}
		else {
			std::cout << "�����"; // ��� ��� �����, ������� ������������ �� �������
		}
		std::cout << std::endl; // ��������� �� ���� �����
	}
}

int main() {
	// ���������� ���-������
	std::vector<std::list<School>> hashTable(TABLE_SIZE);

	// ������ �������� �� ������ � ������
	insert(hashTable, { 8, "���" });
	insert(hashTable, { 18, "�����" }); // ���� ������� ����� ���� ��� �� ���, ��� � ������� � ������� 101
	insert(hashTable, { 25, "ѳ����" });
	insert(hashTable, { 32, "ѳ����" });

	// ������� ��� ���-������
	std::cout << "���-������:" << std::endl;
	printHashTable(hashTable);

	// ��������� ����� �� ������ �����
	int searchKey = 32;
	std::cout << "\n�������� ����� � ������� " << searchKey << ": " << search(hashTable, searchKey) << std::endl;

	return 0;
}
