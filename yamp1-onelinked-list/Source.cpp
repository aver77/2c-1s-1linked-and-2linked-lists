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

struct Node // 0 - представление узла ОЛС в виде структуры и определение в typedef
{
	int info; //поле данных
	Node *next; //указатель на следующий элкмент
};
typedef Node* TList;

void Init(TList &list); // - 1 инициализация
bool Empty(TList list); // 2 - проверка на пустоту
void Add_to_head(TList &list, int new_elem); // 3 - алг добавление элемента в список
void Add_after_Node(TList& list, int elem);
int Delete_from_head(TList &list); // 4 - удал элемента из начала списка
void Sort(TList& list);
void Create_as_Stack(TList &list, ifstream &fin); //5 - созд списка (эл-ты добавл в голову списка)
void Clear(TList &list); // 6 - уничтожение списка
void Print(TList list);
void Print_to_file(TList list, ofstream& fout); // 7 - печать списка
void Sort(TList &list); //алг сортировки методом пузырька
void task1(TList& list); //добавление 0 после первой последовательности из нечетных чисел

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

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
		Create_as_Stack(list, fin); //созд отсортированного по возр списка
		//контрольная печать
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

void Init(TList &list) // - 1 инициализация
{
	list = nullptr;
}

bool Empty(TList list) // 2 - проверка на пустоту
{
	return list == nullptr;
}

void Add_to_head(TList &list, int new_elem) // 3 - алг добавление элемента в список
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

int Delete_from_head(TList &list) // 4 - удал элемента из начала списка
{
	TList p = list;
	list = p->next;
	int elem = p->info;
	p->next = nullptr;
	delete p;
	return elem;
}

void Create_as_Stack(TList &list, ifstream &fin) //5 - созд списка (эл-ты добавл в голову списка)
{
	Init(list);
	int x;
	while (fin >> x)
	{
		Add_to_head(list, x);
	}
	Sort(list);
}

void Clear(TList &list) // 6 - уничтожение списка
{
	while (!Empty(list))
	{
		Delete_from_head(list);
	}
}

void Print_to_file(TList list, ofstream& fout) // 7 - печать списка
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

void Sort(TList &list) //алг сортировки методом пузырька
{
	int changes;
	TList temp;
	do {
		changes = 0; //обнуляем количество перестановок
		temp = list; //элемент списка
		while (temp->next != nullptr) { //пока не дошли до последнего элемента (его указатель указывает на nullptr)
			if (temp->info > temp->next->info) // если предыдуш эл - т больше след
			{
				int tempInfo = temp->info;
				temp->info = temp->next->info;
				temp->next->info = tempInfo; //то меняем их местами
				changes++; //у нас уже есть 1 изменение
			}
			temp = temp->next; //переходим к следующему эл-ту
		}
	} while (changes); //в самом конце, когда дойдем до последнего эл-та  changes не увеличится и while не выполнится - следовательно выходим
}

//  8 5 7 0 4 3 26 7
/*void task1(TList& list)
{
	bool sqnceFound = false; //показывает, найдена ли последовательность
	TList temp = list; //копия эл-та
	TList prev = nullptr; //предыдущ эл-т
	while (temp != nullptr) 
	{
		if (abs(temp->info % 2) != 0) //если эл-т нечетный, то
		{
			sqnceFound = true; //послед или ее начало найдено
			prev = temp;
			temp = temp->next; //переходим к следующему эл-ту
		}
		else if (sqnceFound) //данный if выполнится, если последовательность найдена, но следующий элемент после нее четный => переходим к функции add_after_node()
		{
			temp = nullptr;
		}
		else //переход к следующему эл-ту (но без найденой последовательности)
		{
			temp = temp->next;
		}
	}
	Add_after_Node(prev, 0); //после предыдущ (за temp - первый четный эл-т после последовательности) ставим 0
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
