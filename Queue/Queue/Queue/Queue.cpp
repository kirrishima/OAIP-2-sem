#include <iostream>
#include <climits>
using namespace std;

// Структура для узла очереди
struct QueueNode {
	// Данные элемента очереди
	int data;

	// Указатель на следующий элемент в очереди
	QueueNode* next;

	// Конструктор для создания узла с заданными данными
	QueueNode(int data) {
		this->data = data;
		this->next = nullptr;
	}
};

// Класс для очереди
class Queue {
public:
	Queue(); // Конструктор по умолчанию
	~Queue(); // Деструктор по умолчанию

	// Добавление элемента в конец очереди
	bool enqueue(int data);

	// Удаление элемента из начала очереди
	bool pop();

	// Получение значения первого элемента очереди
	int front() const;

	// Очистка очереди
	void clear();

	// Вывод всей очереди
	void display() const;

private:
	QueueNode* Tail; // Указатель на конец очереди
	QueueNode* Front; // Указатель на начало очереди
};

// Реализация методов класса Queue

// Конструктор по умолчанию
Queue::Queue() {
	this->Tail = nullptr;
	this->Front = nullptr;
}

// Деструктор по умолчанию
Queue::~Queue() {
	this->clear(); // Вызов метода clear() для очистки памяти
}

// Добавление элемента в конец очереди
bool Queue::enqueue(int data) {
	// Создание нового узла для добавляемого элемента
	QueueNode* newNode = new QueueNode(data);
	if (newNode == nullptr) {
		// Не удалось выделить память для нового узла
		return false;
	}

	// Если очередь пустая, устанавливаем Front и Tail на новый узел
	if (Tail == nullptr && Front == nullptr) {
		Front = Tail = newNode;
	}
	else {
		// Иначе, добавляем новый узел в конец очереди
		Tail->next = newNode;
		Tail = newNode;
	}
	return true;
}

// Удаление элемента из начала очереди
bool Queue::pop() {
	if (Front == nullptr) {
		// Очередь пустая, невозможно удалить элемент
		return false;
	}
	QueueNode* temp = Front;
	Front = Front->next; // Переход к следующему узлу
	delete temp; // Удаление узла из памяти
	return true;
}

// Получение значения первого элемента очереди
int Queue::front() const {
	if (Front == nullptr) {
		// Очередь пуста, нет значения для возврата
		throw std::runtime_error("Queue is empty");
	}
	return Front->data;
}

// Очистка очереди
void Queue::clear() {
	while (this->pop());
}

// Вывод всей очереди
void Queue::display() const {
	QueueNode* current = Front;
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}

// Основная функция программы с пользовательским меню
int main() {
	Queue queue;
	int choice;
	int value;

	do {
		cout << "Menu:" << endl;
		cout << "1. Enqueue" << endl;
		cout << "2. Pop" << endl;
		cout << "3. Front" << endl;
		cout << "4. Clear" << endl;
		cout << "5. Display" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter value to enqueue: ";
			cin >> value;
			if (queue.enqueue(value)) {
				cout << "Value enqueued successfully." << endl;
			}
			else {
				cout << "Failed to enqueue value." << endl;
			}
			break;
		case 2:
			if (queue.pop()) {
				cout << "Value popped successfully." << endl;
			}
			else {
				cout << "Failed to pop value. Queue is empty." << endl;
			}
			break;
		case 3:
			try {
				cout << "Front value: " << queue.front() << endl;
			}
			catch (const std::runtime_error& e) {
				cout << "Error: " << e.what() << endl;
			}
			break;
		case 4:
			queue.clear();
			cout << "Queue cleared." << endl;
			break;
		case 5:
			cout << "Queue contents: ";
			queue.display();
			break;
		case 6:
			cout << "Exiting program." << endl;
			break;
		default:
			cout << "Invalid choice. Please enter a valid option." << endl;
			break;
		}

	} while (choice != 6);

	return 0;
}
