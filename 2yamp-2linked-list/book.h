#pragma once
#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::ifstream;

class book
{
	string author;
	string title;
	int year;
	int amount;
	string speciality;
public:
	int get_year();
	book();
	book(book&);
	void Read_from_file(ifstream&);
	void Print();
	bool compare(book&);
};