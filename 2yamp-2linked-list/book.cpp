#include "book.h"
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

book::book(book& goal) //������ ������� ����������� ��� � ������ ���������, ����� ���������� � ���� year ���������� �������
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
	cout << "�����:" << author << ", ��������:" << title << ", ���:" << year << ", ���������� �������:" << amount << ", �������:" << speciality << endl;
}

bool book::compare(book& second) // ����� compare, ������������ �� ���� year: true, ���� ����� ���� �� ����� ���� (���� second ������ - ������� true)
{
	bool res = true;
	if (year > second.year) //���� 1 > 2 �� ������� true, ���� 1 <= 2 ������� false
	{
		res = false;
	}
	return !res;
}