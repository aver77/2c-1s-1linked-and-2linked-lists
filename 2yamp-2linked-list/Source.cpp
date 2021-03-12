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
		cout << "Файл открыт" << endl;

		TList list;
		Create_from_file(list, fin);

		cout << "Данные в списке:" << endl;
		Print_list(list);

		cout << "Введите дату, до которой будет происходить удаление книг" << endl;
		int date;
		cin >> date;
		Delete_by_date(list, date);

		Print_list(list);

		Clear(list);
	}
	else
	{
		cout << "Ошибка открытия файла" << endl;
	}

	system("pause");
	return 0;
}

void Delete_by_date(TList &list, int date) //функция, которая будет удалять номера до тех пор, пока не дойдет до нашей даты (+будет проверять, есть ли вообще такая дата) и выведет список на экран
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
	if (flag) cout << "Введена слишком большая дата, весь список удалился:" << endl;
	else if (!flag && !print) cout << "Данные изменены:" << endl;
	if (print) cout << "Введена слишком маленькая дата, вывелся весь список:" << endl;
}