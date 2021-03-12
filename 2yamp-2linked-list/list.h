#pragma once
#include <iostream>
#include "book.h"
#include <fstream>
#include <string>

using std::ifstream;

struct Node
{
	Node *prev;
	Node *next;
	book info;
};
typedef Node* TList;

void Init(TList&); //инициализация
void Insert_to_head(TList&, book&); //вставка в голову
void Insert_after_Node(TList&, book&); //вставка после эл-та
void Delete(TList&); //уничтож эл-та поочередно с начала списка
void Clear(TList&); //уничтож списка
void Print_list(TList); //печать списка
void Create_from_file(TList &list, ifstream&); //создаем список упорядоченный по годам
TList Find_place(TList, book&); //поиск места вставки - возвращает адрес в который нужно вставить эл-т
