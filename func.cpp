#include "func.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;


void GetFileNames(vector<string> &names)
{
	string path;
	cout << "Enter a file directory name: "; cin >> path; path += "/*.csv";
	WIN32_FIND_DATAA findData;
	HANDLE findFile = FindFirstFileA(path.c_str(), &findData);
	if (findFile == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			cout << "File not found\n";
		}
	}
	do
	{
		names.push_back(findData.cFileName);
	} while (FindNextFileA(findFile, &findData));

	FindClose(findFile);
}