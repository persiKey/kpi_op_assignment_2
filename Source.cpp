#include "func.h"
#include <vector>
#include <string>

using std::string;
using std::vector;


int main()
{
	vector<string> File_paths;
	vector<STUD_TABLE_DATA> Table;

	GetFileLocations(File_paths);
	ProcedeFiles(File_paths, Table);
	
	
	
	return 0;
}