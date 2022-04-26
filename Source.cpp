#include "func.h"
#include <vector>
#include <string>
#include <locale>

using std::string;
using std::vector;


int main()
{
	vector<string> File_paths;
	vector<STUD_TABLE_DATA> Table;

	GetFileLocations(File_paths);
	ProcedeFiles(File_paths, Table);
	//PrintTable(Table);
	vector<STUD_TABLE_DATA> ScholarTable;
	GetScholarRating(Table, ScholarTable);
	PrintTableToFile(ScholarTable);
	
	printf("Мінімальний середній бал серед стипендіатів: %f", GetMinGPA(ScholarTable));

	return 0;
}