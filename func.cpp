#include "structs.h"
#include "func.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

using std::cin;
using std::wcout;
using std::string;
using std::wstring;
using std::vector;
using std::wifstream;
using std::wofstream;
using std::getline;
using std::setw;


void GetFileLocations(vector<string> &file_paths)
{
	file_paths.clear();
	string dir,path;
	wcout << L"Enter a file directory name: "; cin >> dir;
	path = dir + "/*.csv";
	WIN32_FIND_DATAA findData;
	HANDLE findFile = FindFirstFileA(path.c_str(), &findData);
	if (findFile == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
			wcout << L"File not found!"; 
		else
			wcout << L"Something went wrong!";
		wcout << "Shutting down\n";
		exit(-1);
	}
	do
	{
		file_paths.push_back(dir + '/' + findData.cFileName);
	} while (FindNextFileA(findFile, &findData));

	FindClose(findFile);
}

STUD_TABLE_DATA Read_to_Table(STUD_READ_DATA &data)
{
	STUD_TABLE_DATA conv_data;
	conv_data.surname = data.surname;

	float sum = 0;
	for (int i = 0; i < NUM_OF_MARKS; i++)
			sum += data.marks[i];

	conv_data.GPA = sum / NUM_OF_MARKS;
	conv_data.is_contract = (data.is_contract == L"TRUE");
	return conv_data;
}

void ProcedeFiles(const vector<string>& file_paths, vector<STUD_TABLE_DATA>&Table)
{
	wifstream MyFile;
	for (int i = 0; i < file_paths.size(); ++i)
	{
		MyFile.open(file_paths[i]);
		int num_of_data;
		MyFile >> num_of_data;
		MyFile.ignore(1,'\n');
		STUD_READ_DATA data;
		for (int j = 0; j < num_of_data; ++j)
		{
			getline(MyFile, data.surname,L',');
			for (int k = 0; k < NUM_OF_MARKS; k++)
			{
				MyFile >> data.marks[k];
				MyFile.ignore(1, L',');
			}
			getline(MyFile, data.is_contract);
			Table.push_back(Read_to_Table(data));
		}
		MyFile.close();
	}
}

void PrintTable(const vector<STUD_TABLE_DATA>& Table)
{
	wcout << std::left << setw(20) << "Прізвище" << setw(8) << "Сер.бал" << std::right << setw(12) << "Контрактник" << std::endl << std::endl ;
	for (int i = 0; i < Table.size(); ++i)
	{
		wcout << std::left << setw(20) <<Table[i].surname 
			<< setw(8) << std::fixed <<std::setprecision(3) << Table[i].GPA
			<< std::right << setw(12) << Table[i].is_contract << L"\n";
	}
	wcout << std::endl;
}

inline void SortTable(vector<STUD_TABLE_DATA>& Table)
{
	std::sort(Table.begin(), Table.end(),
		[](STUD_TABLE_DATA first, STUD_TABLE_DATA second)
		{return first.GPA > second.GPA; });
}

void GetBudgetRating(const vector<STUD_TABLE_DATA>& Table, vector<STUD_TABLE_DATA>& BudgetTable)
{
	BudgetTable.clear();
	for (int i = 0; i < Table.size(); i++)
	{
		//???
		if (Table[i].is_contract == false)
			BudgetTable.push_back(Table[i]);
	}
	SortTable(BudgetTable);
}



void PrintTableToFile(const vector<STUD_TABLE_DATA>& Table, int persents)
{
	wofstream OutFile(OUT_FILENAME);
	for (int i = 0; i < int(Table.size()*(persents/100.0)); i++)
	{
		OutFile << Table[i].surname; OutFile << L',';
		OutFile << std::fixed << std::setprecision(3) << Table[i].GPA; OutFile << L'\n';
	}
	OutFile.close();
}

float GetMinScholarGPA(const vector<STUD_TABLE_DATA>& ScholarTable)
{
	if (ScholarTable.size() < 100.0/PESENT_OF_SCHOLARHSIP)
	{
		wcout << L"Too few students!\n"; 
		return -1;
	}
	return ScholarTable[ScholarTable.size() * (PESENT_OF_SCHOLARHSIP / 100.0)-1].GPA;
}