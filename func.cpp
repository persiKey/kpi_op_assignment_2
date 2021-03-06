#include "structs.h"
#include "func.h"
#include "Valid.h"
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

int ExtractNumber(wifstream& file)
{
	wstring buf;
	getline(file, buf, L',');
	int res = _wtoi(buf.c_str());
	if (res == 0) file.setstate(std::ios_base::failbit);
	return res;
}

void ReadData(wifstream& file, STUD_READ_DATA &data)
{
	getline(file, data.surname, L','); InputValid(file);
	for (int k = 0; k < NUM_OF_MARKS; k++)
	{
		data.marks[k] = ExtractNumber(file); InputValid(file);
		LogicalValid(file, data.marks[k]);
	}
	getline(file, data.is_contract); InputValid(file);
	LogicalValid(file, data.is_contract);
}

void ProcedeFile(const string& file_path, vector<STUD_TABLE_DATA>& Table)
{
	wifstream MyFile(file_path);
	State::UpdateStateFile(file_path);
	int num_of_data;
	MyFile >> num_of_data;
	
	MyFile.ignore(1, '\n');
	STUD_READ_DATA data;
	for (int j = 0; j < num_of_data && !MyFile.eof(); ++j)
	{
		State::UpdateStateLine(j);
		ReadData(MyFile, data);
		Table.push_back(Read_to_Table(data));
	}
	MyFile.close();
}

void ProcedeFiles(const vector<string>& file_paths, vector<STUD_TABLE_DATA>&Table)
{
	for (int i = 0; i < file_paths.size(); ++i)
	{
		ProcedeFile(file_paths[i], Table);
	}
	if (State::GetState())
	{
		exit(-1);
	}
}

void PrintTable(const vector<STUD_TABLE_DATA>& Table)
{
	wcout << std::left << setw(20) << "????????" << setw(8) << "???.???" << std::right << setw(12) << "???????????" << std::endl << std::endl ;
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
	LogicalValid(ScholarTable.size());
	return ScholarTable[ScholarTable.size() * (PESENT_OF_SCHOLARHSIP / 100.0)-1].GPA;
}


