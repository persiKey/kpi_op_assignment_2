#include "func.h"
#include <vector>
#include <string>
#include <locale>

using std::string;
using std::vector;

#define ASCII

int main()
{
#ifdef ASCII
	system("chcp 1251 > nul"); 
#elif defined(UTF_8)
	system("chcp 65001 > nul");
#endif
	vector<string> File_paths;
	vector<STUD_TABLE_DATA> Table;
	vector<STUD_TABLE_DATA> ScholarTable;

	GetFileLocations(File_paths);
	ProcedeFiles(File_paths, Table);

	PrintTable(Table);
	GetBudgetRating(Table, ScholarTable);
	PrintTableToFile(ScholarTable);

	setlocale(LC_ALL, "Ukrainian");
	wprintf(L"Мінімальний середній бал серед стипендіатів: %.3f", GetMinScholarGPA(ScholarTable));

	return 0;
}