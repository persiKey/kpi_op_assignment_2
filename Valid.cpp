#include "Valid.h"
#include <Windows.h>
#include "structs.h"

void DisplayErrorLine(wifstream& file, string msg);
namespace State
{
	string cur_file;
	int cur_line;
	bool was_error = false;
	void UpdateStateFile(const string& file_name)
	{
		cur_file = file_name;
	}
	void UpdateStateLine(int line)
	{
		cur_line = line+2;
	}
	bool GetState()
	{
		return was_error;
	}
};


bool InputValid(wifstream& file)
{
	if (file.fail())
	{
		DisplayErrorLine(file, "Input error");
		return false;
	}
	return true;
}

bool LogicalValidMark(int m)
{
	if (m > 100) return false;

	return true;
}

bool LogicalValidContract(wstring& is_cont)
{
	if (is_cont == L"TRUE")
		return true;
	else if (is_cont == L"FALSE")
		return true;
	return false;
}

void LogicalValid(wifstream& file, int mark)
{
	if (!LogicalValidMark(mark))
	{
		DisplayErrorLine(file, "Grade cannot be over 100");
	}
}

void LogicalValid(wifstream& file, wstring& is_cont)
{
	if (!LogicalValidContract(is_cont))
	{
		DisplayErrorLine(file, "Misspelling");
	}
}

void LogicalValid(int num_of_scholar)
{
	if (num_of_scholar < 100.0 / PESENT_OF_SCHOLARHSIP)
	{
		std::wcerr << L"\a\tToo few students!\n";
		exit(-1);
	}
}

void procedeLastChar(wifstream& file)
{
	file.seekg(-1, std::ios_base::cur);
	if (file.get() == L'\n')
		file.seekg(-2, std::ios_base::cur);
	else
		file.seekg(-1, std::ios_base::cur);
}

int getNearCharPos(wifstream& file, char ch)
{
	int save_pos = file.tellg(),got;
	procedeLastChar(file);
	do
	{
		file.seekg(-1, std::ios_base::cur);
		got = file.get();
		file.seekg(-1, std::ios_base::cur);
	} while ((int)file.tellg() > 0 && got != ch);
	int end_pos = file.tellg();
	file.seekg(save_pos);
	return end_pos+1;
}

void PrintErrorInfo(int err_index, string &msg)
{
	using std::cerr;
	cerr << "\a\t";
	for (int i = 0; i < err_index - 1; ++i)
		cerr << '-';
	cerr << "^ ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cerr << msg;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cerr << " in file " << State::cur_file << " line: " << State::cur_line << " pos: " << err_index << std::endl;
}

void PrintFormattedError(wstring &err_line, int err_index, int start_index)
{
	using std::wcerr;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	wcerr << '\t' << err_line.substr(0, err_index);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	wcerr << err_line.substr(err_index, start_index - err_index);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	if (start_index < err_line.size())
		wcerr << err_line.substr(start_index);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	wcerr << '\n';
	
}

void DisplayErrorLine(wifstream& file, string msg)
{
	
	file.clear();
	int cur_pos = file.tellg();
	int err_pos = getNearCharPos(file, ',');
	int line_begin = getNearCharPos(file, '\n');
	int err_index = err_pos - line_begin;

	wstring str;
	file.seekg(line_begin);
	std::getline(file, str);
	file.seekg(cur_pos);

	PrintFormattedError(str, err_index, cur_pos - line_begin-1);
	PrintErrorInfo(err_index, msg);
	State::was_error = true;
}