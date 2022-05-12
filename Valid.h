#pragma once
#include <fstream>
#include <iostream>
#include <string>

using std::wifstream;
using std::cerr;
using std::wstring;
using std::string;

bool InputValid(wifstream& file);
void LogicalValid(wifstream& file, int mark);
void LogicalValid(wifstream& file, wstring& is_cont);
void LogicalValid(int num_of_scholar);

namespace State
{
	void UpdateStateFile(const string&);

	void UpdateStateLine(int);
	bool GetState();
};
