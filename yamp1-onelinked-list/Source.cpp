#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <exception>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

struct Node // 0 - ������������� ���� ��� � ���� ��������� � ����������� � typedef
{
	int info; //���� ������
	Node *next; //��������� �� ��������� �������
};
typedef Node* TList;

void Init(TList &list); // - 1 �������������
bool Empty(TList list); // 2 - �������� �� �������
void Add_to_head(TList &list, int new_elem); // 3 - ��� ���������� �������� � ������
void Add_after_Node(TList& list, int elem);
int Delete_from_head(TList &list); // 4 - ���� �������� �� ������ ������
void Sort(TList& list);
void Create_as_Stack(TList &list, ifstream &fin); //5 - ���� ������ (��-�� ������ � ������ ������)
void Clear(TList &list); // 6 - ����������� ������
void Print(TList list);
void Print_to_file(TList list, ofstream& fout); // 7 - ������ ������
void Sort(TList &list); //��� ���������� ������� ��������
void task1(TList& list); //���������� 0 ����� ������ ������������������ �� �������� �����

int main()
{
	SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������

	cout << "Enter name input.txt of input file" << endl;
	string path;
	cin >> path;
	ifstream fin(path);
	cout << "Enter name of output file" << endl;
	cin >> path;
	ofstream fout(path);
	if (fin.is_open())
	{
		cout << "File successfully opened" << endl;
		TList list;
		Create_as_Stack(list, fin); //���� ���������������� �� ���� ������
		//����������� ������
		Print(list);
		task1(list);
		Print(list);
		Print_to_file(list, fout);
		Clear(list);
		fin.close();
		fout.close();
	}
	else
	{
		cout << "Opening file error" << endl;
	}
	cin.ignore(cin.rdbuf()->in_avail()).get();
	return 0;
}

void Init(TList &list) // - 1 �������������
{
	list = nullptr;
}

bool Empty(TList list) // 2 - �������� �� �������
{
	return list == nullptr;
}

void Add_to_head(TList &list, int new_elem) // 3 - ��� ���������� �������� � ������
{
	TList p = new Node;
	p->info = new_elem;
	p->next = list;
	list = p;
}

void Add_after_Node(TList& list, int elem) {
	TList newNode = new Node;
	newNode->info = elem;
	newNode->next = list->next;
	list->next = newNode;
}

int Delete_from_head(TList &list) // 4 - ���� �������� �� ������ ������
{
	TList p = list;
	list = p->next;
	int elem = p->info;
	p->next = nullptr;
	delete p;
	return elem;
}

void Create_as_Stack(TList &list, ifstream &fin) //5 - ���� ������ (��-�� ������ � ������ ������)
{
	Init(list);
	int x;
	while (fin >> x)
	{
		Add_to_head(list, x);
	}
	Sort(list);
}

void Clear(TList &list) // 6 - ����������� ������
{
	while (!Empty(list))
	{
		Delete_from_head(list);
	}
}

void Print_to_file(TList list, ofstream& fout) // 7 - ������ ������
{
	TList p = list;
	while (p != nullptr)
	{
		fout << p->info << " ";
		p = p->next;
	}
}

void Print(TList list)
{
	TList p = list;
	while (p != nullptr)
	{
		cout << p->info << " ";
		p = p->next;
	}
	cout << endl;
}

void Sort(TList &list) //��� ���������� ������� ��������
{
	int changes;
	TList temp;
	do {
		changes = 0; //�������� ���������� ������������
		temp = list; //������� ������
		while (temp->next != nullptr) { //���� �� ����� �� ���������� �������� (��� ��������� ��������� �� nullptr)
			if (temp->info > temp->next->info) // ���� �������� �� - � ������ ����
			{
				int tempInfo = temp->info;
				temp->info = temp->next->info;
				temp->next->info = tempInfo; //�� ������ �� �������
				changes++; //� ��� ��� ���� 1 ���������
			}
			temp = temp->next; //��������� � ���������� ��-��
		}
	} while (changes); //� ����� �����, ����� ������ �� ���������� ��-��  changes �� ���������� � while �� ���������� - ������������� �������
}

//  8 5 7 0 4 3 26 7
/*void task1(TList& list)
{
	bool sqnceFound = false; //����������, ������� �� ������������������
	TList temp = list; //����� ��-��
	TList prev = nullptr; //�������� ��-�
	while (temp != nullptr) 
	{
		if (abs(temp->info % 2) != 0) //���� ��-� ��������, ��
		{
			sqnceFound = true; //������ ��� �� ������ �������
			prev = temp;
			temp = temp->next; //��������� � ���������� ��-��
		}
		else if (sqnceFound) //������ if ����������, ���� ������������������ �������, �� ��������� ������� ����� ��� ������ => ��������� � ������� add_after_node()
		{
			temp = nullptr;
		}
		else //������� � ���������� ��-�� (�� ��� �������� ������������������)
		{
			temp = temp->next;
		}
	}
	Add_after_Node(prev, 0); //����� �������� (�� temp - ������ ������ ��-� ����� ������������������) ������ 0
}*/

void task1(TList &list)
{
	TList temp = list;
	bool pair = false;
	while (temp->next != nullptr && !pair)
	{
		if ((temp->info % 2) != 0 && (temp->next->info % 2) != 0)
		{
			pair = true;
		}
		else
		{
			temp = temp->next;
		}
	}
	if (!pair) cout << "There are no sqnce" << endl;
	else
	{
		bool sqnce = false;
		while (temp->next != nullptr && !sqnce)
		{
			if ((temp->next->info % 2) == 0)
			{
				sqnce = true;
			}
			else
			{
				temp = temp->next;
			}
		}
		Add_after_Node(temp, 0);
	}
}