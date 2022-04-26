#include "func.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "structs.h"
#include <fstream>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::ifstream;
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
	conv_data.is_contract = (data.is_contract == "TRUE");
	return conv_data;
}

void ProcedeFiles(vector<string>& names, vector<STUD_TABLE_DATA>&Table)
{
	ifstream MyFile;
	for (int i = 0; i < names.size(); ++i)
	{
		MyFile.open(names[i]);
		int num_of_data;
		MyFile >> num_of_data;
		STUD_READ_DATA data;
		for (int j = 0; j < num_of_data; ++j)
		{
			getline(MyFile, data.surname,',');
			for (int k = 0; k < NUM_OF_MARKS; k++)
			{
				MyFile >> data.marks[k];
				MyFile.ignore(1, ',');
			}
			getline(MyFile, data.is_contract);
			Table.push_back(Read_to_Table(data));
		}
		MyFile.close();
	}
}