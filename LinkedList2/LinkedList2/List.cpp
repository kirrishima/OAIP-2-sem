#include "List.h"

bool Object::Insert(void* data)
{
	bool rc = false;
	if (Head == NULL)
	{
		// Вылучаем памяць і ствараем копію дадзеных для першага элемента
		Head = new Element(NULL, new Person(*((Person*)data)), Head);
		rc = true;
	}
	else
	{
		// Вылучаем памяць і ствараем копію дадзеных для наступных элементаў
		Head = (Head->Prev = new Element(NULL, new Person(*(static_cast<Person*>(data))), Head));
		rc = true;
	}
	return rc;
}

//------------------------------------------------ -----------
Element* Object::Search(void* data) // Знайсці зададзены элемент
{
	Element* rc = Head;
	while ((rc != NULL) && (rc->Data != data))
		rc = rc->Next;
	return rc;
}

//------------------------------------------------ -----------
void Object::PrintList(void(*f)(void*)) // Выснова
{
	Element* e = Head;
	while (e != NULL)
	{
		f(e->Data); // Выклікаем функцыю для вываду дадзеных
		e = e->GetNext();
	};
}

//------------------------------------------------- ----------
void Object::PrintList(void(*f)(void*), Element* e)
{
	f(e->Data); // Выклікаем функцыю для вываду дадзеных
}

//------------------------------------------------ -----------
bool Object::Delete(Element* e) // Выдаліць па спасылцы
{
	bool rc = 0;
	if (rc = (e != NULL))
	{
		if (e->Next != NULL)
			e->Next->Prev = e->Prev;
		if (e->Prev != NULL)
			e->Prev->Next = e->Next;
		else
			Head = e->Next;
		delete e; // Вызваляем памяць, якую займае элемент, які выдаляецца.
	}
	return rc;
}

//------------------------------------------------ -----------
bool Object::Delete(void* data) // Выдаліць па значэнні
{
	return Delete(Search(data));
}

//------------------------------------------------ -----------
Element* Object::GetLast()
{
	Element* e = Head, * rc = e;
	while (e != NULL)
	{
		rc = e; // Абнаўляем паказальнік на апошні элемент
		e = e->GetNext();
	}
	return rc;
}

//------------------------------------------------ -----------
Object Create()
{
	return *(new Object());
}

bool Object::DeleteList()
{
	while (Head != nullptr)
	{
		Element* temp = Head;
		Head = Head->Next;
		delete temp; // Вызваляем памяць, якую займае элемент, які выдаляецца.
	}
	return true;
}


int Object::CountList()
{
	int count = 0;
	Element* current = Head;
	while (current != nullptr)
	{
		count++;
		current = current->Next;
	}
	return count;
}
