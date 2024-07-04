#pragma once 
#include <iostream>
struct Person
{
	char name[20];
	int age;
	Person* next;
};
struct Element // Ёлемент сп≥су
{
	Element* Prev; // паказальн≥к на пап€рэдн≥ элемент
	Element* Next; // паказальн≥к на наступны элемент
	void* Data; // дадзены€
	Element(Element* prev, void* data, Element* next)
	{
		Prev = prev;
		Data = data;
		Next = next;
	}
	Element* GetNext() // атрымаць наступны
	{
		return Next;
	};
	Element* GetPrev() // атрымаць пап€рэдн≥
	{
		return Prev;
	};
};
//------------------------------------------------ -----------
struct Object // Ѕлок к≥раванн€ сп≥сам
{
	Element* Head; // паказальн≥к на пачатак сп≥су
	Object()
	{
		Head = NULL;
	};
	Element* GetFirst() // атрымаць першы элемент сп≥су
	{
		return Head;
	};
	Element* GetLast(); // атрымаць апошн≥ элемент сп≥су
	Element* Search(void* data); // знайсц≥ першы элемент па дадзеных
	bool Insert(void* data); // дадаць элемент у пачатак
	bool InsertEnd(void* data); // дадаць у канец
	bool Delete(Element* e); // выдал≥ць па адрасе элемента
	bool Delete(void* data); // выдал≥ць першы па дадзеных
	bool DeleteList(); // ачысц≥ць сп≥с
	void PrintList(void(*f)(void*)); // ¬ывесц≥ сп≥с
	void PrintList(void(*f)(void*), Element*); // ¬ывесц≥ сп≥с
	int CountList(); // ѕал≥чыць элементы Ґ сп≥се

};
Object Create();