#include <iostream>
#include <fstream>
#include "list.h"
#include "book.h"
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

void Delete_by_date(TList &list, int date);

int main()
{
	setlocale(LC_ALL, "Rus");

	string path = "inp.txt";
	ifstream fin(path);

	if (fin.is_open())
	{
		cout << "���� ������" << endl;

		TList list;
		Create_from_file(list, fin);

		cout << "������ � ������:" << endl;
		Print_list(list);

		cout << "������� ����, �� ������� ����� ����������� �������� ����" << endl;
		int date;
		cin >> date;
		Delete_by_date(list, date);

		Print_list(list);

		Clear(list);
	}
	else
	{
		cout << "������ �������� �����" << endl;
	}

	system("pause");
	return 0;
}

void Delete_by_date(TList &list, int date) //�������, ������� ����� ������� ������ �� ��� ���, ���� �� ������ �� ����� ���� (+����� ���������, ���� �� ������ ����� ����) � ������� ������ �� �����
{
	bool flag = true, print = true;
	if (list != nullptr)
	{
		while (list!= nullptr && flag)
		{
			if (list->info.get_year() < date)
			{
				Delete(list);
				print = false;
			}
			else
			{
				flag = false;
			}
		}
	}
	if (flag) cout << "������� ������� ������� ����, ���� ������ ��������:" << endl;
	else if (!flag && !print) cout << "������ ��������:" << endl;
	if (print) cout << "������� ������� ��������� ����, ������� ���� ������:" << endl;
}