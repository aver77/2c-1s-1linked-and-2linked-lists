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

void Init(TList&); //�������������
void Insert_to_head(TList&, book&); //������� � ������
void Insert_after_Node(TList&, book&); //������� ����� ��-��
void Delete(TList&); //������� ��-�� ���������� � ������ ������
void Clear(TList&); //������� ������
void Print_list(TList); //������ ������
void Create_from_file(TList &list, ifstream&); //������� ������ ������������� �� �����
TList Find_place(TList, book&); //����� ����� ������� - ���������� ����� � ������� ����� �������� ��-�