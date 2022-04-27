#pragma once
#include <string>
using std::wstring;

constexpr int NUM_OF_MARKS = 5;
constexpr int PESENT_OF_SCHOLARHSIP = 40;
constexpr char OUT_FILENAME[] = "rating.csv";

struct STUD_READ_DATA
{
	wstring surname;
	int marks[NUM_OF_MARKS];
	wstring is_contract;
};

struct STUD_TABLE_DATA
{
	wstring surname;
	float GPA;
	bool is_contract;
};
