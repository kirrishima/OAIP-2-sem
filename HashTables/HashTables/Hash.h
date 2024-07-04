#pragma once

// Макрас для абазначэння выдаленага элемента ў хэш-табліцы.
#define HASHDEL (void*) -1

// Структура для прадстаўлення хэш-табліцы.
struct Object
{
	void** data; // Масіў паказальнікаў на элементы хэш-табліцы.
	int size; // Памер хэш-табліцы.
	int N; // Колькасць элементаў у хэш-табліцы.
	int(*getKey)(void*); // Паказальнік на функцыю для атрымання ключа элемента.

	// Канструктар з параметрамі.
	Object(int, int(*)(void*));

	// Метады для працы з хэш-табліцай.
	bool insert(void*);
	int searchInd(int key);
	void* search(int key);
	void* deleteByKey(int key);
	bool deleteByValue(void*);
	void scan(void(*f)(void*));
};

// Паказальнік на выдалены элемент.
static void* DEL = (void*)HASHDEL;

// Функцыя для стварэння аб'екта хэш-табліцы.
Object create(int size, int(*getkey)(void*));

// Адмена вызначэння макраса HASHDEL.
#undef HASHDEL