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
	if (list == nullptr) cout << "������ ����" << endl;
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
	book tmp; //��� ���� ������ book

	tmp.Read_from_file(fin); //�������� ����� �� ������ ���� �� ��� ���� �� ����� ������ ����� ��� �������
	fin.ignore(255, '\n'); //���������� ������� ����������� ������

	Insert_to_head(list, tmp);

	while (!fin.eof())
	{
		tmp.Read_from_file(fin); //����� ���������� �������� ��-��
		fin.ignore(255, '\n');

		TList tmpNode = Find_place(list, tmp);

		if (tmpNode == nullptr) //��-� ������ ������� => ��������� � ������
			Insert_to_head(list, tmp);
		else //����� ��������� ������������� ������������� ������
			Insert_after_Node(tmpNode, tmp);
	}
}

TList Find_place(TList list, book &Book) //�-�� ����� ����� �������
{
	TList p = list;
	if (!(p->next != nullptr && Book.compare(p->info)))	//���� � �������� ��������� ������� nullptr �� ������ ������ �� �����, ������ ���� 
		p = nullptr;				//� ��� �� ���������� ��-� ��� ������� � ������ ��-���. ���� ��-� ������ 1-��, 
									//�� �� �� ����� ������� ��������� �� ��-� ����� ������ (�� ������ ��� ���������� �����) => ����� nullptr			
	else
	{
		while (p->next != nullptr && Book.compare(p->next->info)) //����� ���� �������� ������ ���� � ������� ��������
			p = p->next;
	}

	return p;
}
