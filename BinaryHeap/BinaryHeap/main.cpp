#include "Heap.h"
#include <iostream>
#include <Windows.h>
using namespace std;

// Функцыя для параўнання двух аб'ектаў тыпу AAA у кучы.
heap::CMP cmpAAA(void* a1, void* a2)
{
	// Прывядзенне паказальнікаў да тыпу AAA.
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)

// Ініцыялізацыя выніку параўнання як EQUAL (роўнасць).
	heap::CMP rc = heap::EQUAL;

	// Параўнанне значэнняў 'x' аб'ектаў AAA.
	if (A1->x > A2->x)
		rc = heap::GREAT; // Калі A1.x > A2.x, вынік GREAT (больш).
	else if (A2->x > A1->x)
		rc = heap::LESS; // Калі A2.x > A1.x, вынік LESS (менш).

	// Зварот выніку параўнання.
	return rc;

	// Выдаленне макрасаў для прадухілення магчымых канфліктаў.
#undef A2
#undef A1
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	// Аб'ява зменных.
	int k, choice, index;

	// Стварэнне асобніка кучы h1 з ёмістасцю 30 і выкарыстаннем функцыі параўнання cmpAAA.
	heap::Heap h1 = heap::create(30, cmpAAA);

	// Бясконцы цыкл для ўзаемадзеяння з карыстальнікам.
	for (;;)
	{
		// Адлюстраванне варыянтаў меню.
		cout << "1 - вывад кучы на экран" << endl;
		cout << "2 - дадаць элемент" << endl;
		cout << "3 - выдаліць максімальны элемент" << endl;
		cout << "4 - выдаліць мінімальны элемент" << endl;
		cout << "5 - выдаліць элемент па індэксу" << endl;
		cout << "6 - аб'яднаць дзве кучы" << endl;
		cout << "7 - знайсці элемент, які роўны суме максімальнага і мінімальнага элементаў" << endl; // Новы пункт мяню
		cout << "8 - атрымаць максімальны элемент" << endl; // Новы пункт мяню
		cout << "9 - атрымаць мінімальны элемент" << endl; // Новы пункт мяню
		cout << "0 - выхад" << endl;
		cout << "зрабіце выбар" << endl;

		// Чытанне выбару карыстальніка.
		cin >> choice;

		// Інструкцыі switch у залежнасці ад выбару карыстальніка.
		switch (choice)
		{
		case 0: // Выхад з праграмы.
			exit(0);
		case 1: // Адлюстраваць змесціва кучы.
			h1.scan(0);
			break;
		case 2: // Дадаць элемент у кучу.
		{
			// Дынамічнае вылучэнне памяці для аб'екта AAA.
			AAA* a = new AAA;
			cout << "увядзіце ключ" << endl;
			cin >> k;
			a->x = k;
			// Уставіць элемент у кучу.
			h1.insert(a);
		}
		break;
		case 3: // Выдаліць максімальны элемент з кучы.
			h1.extractMax();
			break;
		case 4: // Выдаліць мінімальны элемент з кучы.
			h1.extractMin();
			break;
		case 5: // Выдаліць элемент па індэксе з кучы.
			cout << "увядзіце індэкс элемента для выдалення" << endl;
			cin >> index;
			h1.extractI(index);
			break;
		case 6: // Аб'яднаць дзве кучы.
		{
			cout << "Стварэнне другой кучы для аб'яднання..." << endl;
			heap::Heap h2 = heap::create(2, cmpAAA);
			for (size_t i = 0; i < 2; i++)
			{
				// Дынамічнае вылучэнне памяці для аб'екта AAA.
				AAA* a = new AAA;
				cout << "увядзіце ключ" << endl;
				cin >> k;
				a->x = k;
				// Уставіць элемент у кучу.
				h2.insert(a);
			}
			// Можна дадаць элементы ў h2 па меры неабходнасці.
			cout << "Аб'яднанне двух куч" << endl;
			h1.unionHeap(h2);
		}
		break;
		case 7: // Пошук элемента, роўнага суме максімальнага і мінімальнага элементаў
		{
			void* sumElement = h1.findSumElement();
			if (sumElement != nullptr)
			{
				cout << "Знойдзены элемент, які роўны суме максімальнага і мінімальнага: ";
				((AAA*)sumElement)->print();
				cout << endl;
			}
			else
			{
				cout << "Не атрымалася знайсці элемент, які роўны суме максімальнага і мінімальнага." << endl;
			}
		}
		break;
		case 8: // Атрыманне максімальнага элемента з кучы
		{
			void* maxElement = h1.getMax();
			if (maxElement != nullptr)
			{
				cout << "Максімальны элемент: ";
				((AAA*)maxElement)->print();
				cout << endl;
			}
			else
			{
				cout << "Куча пустая." << endl;
			}
		}
		break;
		case 9: // Атрыманне мінімальнага элемента з кучы
		{
			void* minElement = h1.getMin();
			if (minElement != nullptr)
			{
				cout << "Мінімальны элемент: ";
				((AAA*)minElement)->print();
				cout << endl;
			}
			else
			{
				cout << "Куча пустая." << endl;
			}
		}
		break;
		default: // Вывесці паведамленне аб няслушнай камандзе.
			cout << endl << "Уведзена няслушная каманда!" << endl;
		}
	}
	return 0;
}
