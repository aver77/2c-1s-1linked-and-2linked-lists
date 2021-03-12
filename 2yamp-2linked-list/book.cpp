include "book.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int book::get_year()
{
	return year;
}

book::book() {}

book::book(book& goal) //данная функция понадобится нам в методе сравнения, чтобы обратиться к полю year следующего обьекта
{
	author = goal.author;
	title = goal.title;
	year = goal.year;
	amount = goal.amount;
	speciality = goal.speciality;
}


void book::Read_from_file(ifstream& fin)
{
	getline(fin, author);
	getline(fin, title);
	fin >> year >> amount;
	fin.ignore(1);
	getline(fin, speciality);
}

void book::Print()
{
	cout << "Автор:" << author << ", Название:" << title << ", Год:" << year << ", Количество страниц:" << amount << ", Предмет:" << speciality << endl;
}

bool book::compare(book& second) // метод compare, сравнивающий по полю year: true, если нужно идти на некст ноду (если second меньше - возврат true)
{
	bool res = true;
	if (year > second.year) //если 1 > 2 то возврат true, если 1 <= 2 возврат false
	{
		res = false;
	}
	return !res;
}
