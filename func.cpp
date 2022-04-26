#include "func.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "structs.h"
#include <fstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::wcout;
using std::string;
using std::wstring;
using std::vector;
using std::wifstream;
using std::wofstream;
using std::getline;


void GetFileLocations(vector<string> &file_paths)
{
	file_paths.clear();
	string dir,path;
	cout << "Enter a file directory name: "; cin >> dir;
	path = dir + "/*.csv";
	WIN32_FIND_DATAA findData;
	HANDLE findFile = FindFirstFileA(path.c_str(), &findData);
	if (findFile == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			cout << "File not found\n"; return;
		}
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
		STUD_READ_DATA data;
		for (int j = 0; j < num_of_data; ++j)
		{
			MyFile.ignore(1,'\n');
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
	for (int i = 0; i < Table.size(); ++i)
	{
		wcout << Table[i].surname << '\t' << Table[i].GPA << '\t' << Table[i].is_contract << '\n';
	}
}

void GetScholarRating(const vector<STUD_TABLE_DATA>& Table, vector<STUD_TABLE_DATA>& ScholarshipTable)
{
	ScholarshipTable.clear();
	for (int i = 0; i < Table.size(); i++)
	{
		//???
		if (Table[i].is_contract == false)
			ScholarshipTable.push_back(Table[i]);
	}
	std::sort(ScholarshipTable.begin(), ScholarshipTable.end(),
		[](STUD_TABLE_DATA first, STUD_TABLE_DATA second)
		{return first.GPA > second.GPA; });
}

void PrintTableToFile(const vector<STUD_TABLE_DATA>& Table)
{
	wofstream OutFile(OUT_FILENAME);
	for (int i = 0; i < Table.size()*(PESENT_OF_SCHOLARHSIP/100.0); i++)
	{
		OutFile << Table[i].surname; OutFile << L',';
		OutFile << Table[i].GPA; OutFile << L'\n';
	}

	OutFile.close();
}

float GetMinGPA(const vector<STUD_TABLE_DATA>& Table)
{
	return Table[Table.size() * (PESENT_OF_SCHOLARHSIP / 100.0)-1].GPA;
}