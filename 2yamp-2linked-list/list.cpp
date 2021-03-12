#include "list.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

void Init(TList &list)
{
	list = nullptr;
}

void Insert_to_head(TList &list, book &new_elem)
{
	TList temp = new Node;
	temp->next = list;
	temp->prev = nullptr;
	temp->info = new_elem;
	if (list != nullptr && list->prev != nullptr)
	{
		list->prev = temp;
	}
	list = temp;
}

void Insert_after_Node(TList& list, book &new_elem)
{
	TList temp = new Node;
	temp->info = new_elem;
	temp->prev = list;
	temp->next = list->next;
	list->next = temp;
	if (temp->next != nullptr)
		temp->next->prev = temp;
}

void Delete(TList &list)
{
	if (list->next != nullptr)
		list->next->prev = list->prev;
	if (list->prev != nullptr)
		list->prev->next = list->next;
	TList temp = list;
	list = list->next;
	book tempInfo = temp->info;
	delete temp;
}

void Clear(TList &list)
{
	while (list != nullptr)
	{
		Delete(list);
	}
}

void Print_list(TList list)
{
	TList &temp = list;
	if (list == nullptr) cout << "Список пуск" << endl;
	else
		while (temp != nullptr)
		{
			temp->info.Print();
			temp = temp->next;
		}
	cout << endl;
}

void Create_from_file(TList &list, ifstream &fin)
{
	Init(list);
	book tmp; //все поля класса book

	tmp.Read_from_file(fin); //передаем сразу же первый файл тк для него не нужно искать место для вставки
	fin.ignore(255, '\n'); //игнорируем символы разделяющие записи

	Insert_to_head(list, tmp);

	while (!fin.eof())
	{
		tmp.Read_from_file(fin); //далее поочередно передаем эл-ты
		fin.ignore(255, '\n');

		TList tmpNode = Find_place(list, tmp);

		if (tmpNode == nullptr) //эл-т меньше первого => вставляем в голову
			Insert_to_head(list, tmp);
		else //иначе вставляем возвращенного определенного адреса
			Insert_after_Node(tmpNode, tmp);
	}
}

TList Find_place(TList list, book &Book) //ф-ия поиск места вставки
{
	TList p = list;
	if (!(p->next != nullptr && Book.compare(p->info)))	//если в качестве указателя передан nullptr то искать ничего не можем, список пуст 
		p = nullptr;				//а так же сравниваем эл-т для вставки с первым эл-том. если эл-т меньше 1-го, 
									//то мы не можем вернуть указатель на эл-т перед первым (тк список без заглавного звена) => возвр nullptr			
	else
	{
		while (p->next != nullptr && Book.compare(p->next->info)) //выход если предыдущ больше след и возврат предыдущ
			p = p->next;
	}

	return p;
}
