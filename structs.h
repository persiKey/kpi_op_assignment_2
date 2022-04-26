#pragma once
#include <string>
using std::string;

constexpr int NUM_OF_MARKS = 5;

struct STUD_READ_DATA
{
	string surname;
	int marks[NUM_OF_MARKS];
	string is_contract;
};

struct STUD_TABLE_DATA
{
	string surname;
	float GPA;
	bool is_contract;
};

struct SRUD_WRITE_DATA
{
	string surname;
	float GPA;
};